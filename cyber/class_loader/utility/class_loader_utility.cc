/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "cyber/class_loader/utility/class_loader_utility.h"

#include <unordered_map>

#include "cyber/class_loader/class_loader.h"

namespace apollo {
namespace cyber {
namespace class_loader {

using SharedLibraryPtr = std::shared_ptr<SharedLibrary>;

namespace {
std::unordered_map<std::string, SharedLibraryPtr> open_libraries;
std::mutex open_libraries_mutex;
}  // namespace

namespace utility {

using ClassFactoryVector = std::vector<AbstractClassFactoryBase*>;

namespace {
BaseToClassFactoryMapMap base_to_factory_map_map;
std::recursive_mutex base_to_factory_map_mutex;
ClassLoader* curr_active_loader = nullptr;

void SetCurActiveClassLoader(ClassLoader* loader) {
  curr_active_loader = loader;
}

}  // namespace

std::recursive_mutex& GetClassFactoryMapMapMutex() {
  return base_to_factory_map_mutex;
}

ClassClassFactoryMap& GetClassFactoryMapByBaseClass(
    const std::string& base_typeid) {
  auto iter = base_to_factory_map_map.find(base_typeid);
  if (iter != base_to_factory_map_map.end()) {
    return iter->second;
  }

  base_to_factory_map_map.emplace(base_typeid, ClassClassFactoryMap());
  return base_to_factory_map_map[base_typeid];
}

ClassLoader* GetCurActiveClassLoader() { return curr_active_loader; }

ClassFactoryVector GetAllClassFactoryObjectsOfLibrary(
    const std::string& library_path) {
  std::lock_guard<std::recursive_mutex> lock(base_to_factory_map_mutex);

  ClassFactoryVector result;
  for (auto& kv : base_to_factory_map_map) {
    for (auto& class_to_factory : kv.second) {
      auto class_factory_obj = class_to_factory.second;
      if (class_factory_obj->GetLibraryPath() == library_path) {
        result.emplace_back(class_factory_obj);
      }
    }
  }
  return result;
}

void DestroyClassFactoryObjectsOfLibrary(
    const std::string& library_path, const ClassLoader* class_loader,
    ClassClassFactoryMap* class_factory_map) {
  for (ClassClassFactoryMap::iterator itr = class_factory_map->begin();
       itr != class_factory_map->end();) {
    AbstractClassFactoryBase* class_factory_object = itr->second;
    if (class_factory_object->GetLibraryPath() == library_path &&
        class_factory_object->IsOwnedBy(class_loader)) {
      class_factory_object->RemoveOwnedClassLoader(class_loader);
      // when no anybody owner, delete && erase
      if (!class_factory_object->IsOwnedByAnybody()) {
        itr = class_factory_map->erase(itr);
        delete class_factory_object;
      } else {
        ++itr;
      }
    } else {
      ++itr;
    }
  }
}

void DestroyClassFactoryObjectsOfLibrary(const std::string& library_path,
                                         const ClassLoader* loader) {
  std::lock_guard<std::recursive_mutex> lock(base_to_factory_map_mutex);

  for (auto& baseclass_map : base_to_factory_map_map) {
    DestroyClassFactoryObjectsOfLibrary(library_path, loader,
                                        &baseclass_map.second);
  }
}

bool IsLibraryLoaded(const std::string& library_path) {
  std::lock_guard<std::mutex> lock(open_libraries_mutex);
  auto iter = open_libraries.find(library_path);
  return iter != open_libraries.end();
}

bool LoadLibrary(const std::string& library_path, ClassLoader* loader) {
  if (IsLibraryLoaded(library_path)) {
    AINFO << "Lib " << library_path
          << " has already been loaded, only attach to class factory obj."
          << library_path;
    ClassFactoryVector lib_class_factory_objs =
        GetAllClassFactoryObjectsOfLibrary(library_path);
    for (auto& class_factory_obj : lib_class_factory_objs) {
      class_factory_obj->AddOwnedClassLoader(loader);
    }
    return true;
  }

  SharedLibraryPtr shared_library = nullptr;
  static std::recursive_mutex loader_mutex;
  {
    std::lock_guard<std::recursive_mutex> lck(loader_mutex);

    try {
      SetCurActiveClassLoader(loader);
      shared_library = std::make_shared<SharedLibrary>(library_path);
    } catch (const LibraryLoadException& e) {
      AERROR << "LibraryLoadException: " << e.what();
    } catch (const LibraryAlreadyLoadedException& e) {
      AERROR << "LibraryAlreadyLoadedException: " << e.what();
    } catch (const SymbolNotFoundException& e) {
      AERROR << "SymbolNotFoundException: " << e.what();
    }

    SetCurActiveClassLoader(nullptr);
  }

  if (shared_library == nullptr) {
    AERROR << "shared library failed: " << library_path;
    return false;
  }

  auto num_lib_objs = GetAllClassFactoryObjectsOfLibrary(library_path).size();
  if (num_lib_objs == 0) {
    AWARN << "Class factory objs counts is 0, maybe registerclass failed.";
  }

  std::lock_guard<std::mutex> lock(open_libraries_mutex);
  open_libraries.emplace(library_path, shared_library);
  return true;
}

void UnloadLibrary(const std::string& library_path, ClassLoader* loader) {
  std::lock_guard<std::mutex> lock(open_libraries_mutex);
  auto itr = open_libraries.find(library_path);
  if (itr == open_libraries.end()) {
    AERROR << "Failed to unload non-open library: " << library_path;
    return;
  }
  try {
    DestroyClassFactoryObjectsOfLibrary(library_path, loader);

    if (GetAllClassFactoryObjectsOfLibrary(library_path).empty()) {
      itr->second->Unload();
      open_libraries.erase(itr);
    } else {
      AWARN << "ClassFactory objects still remain in memory, meaning other"
               "class loaders are still using library:"
            << library_path;
    }
  } catch (const std::runtime_error& e) {
    AERROR << "Library unload error: " << e.what();
  }
}

}  // End namespace utility
}  // End namespace class_loader
}  // namespace cyber
}  // namespace apollo
