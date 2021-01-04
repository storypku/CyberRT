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
#include "cyber/class_loader/utility/class_factory.h"

#include "cyber/class_loader/class_loader.h"

namespace apollo {
namespace cyber {
namespace class_loader {
namespace utility {

void AbstractClassFactoryBase::SetLibraryPath(const std::string& library_path) {
  library_path_ = library_path;
}

void AbstractClassFactoryBase::AddOwnedClassLoader(ClassLoader* loader) {
  auto iter = std::find(relative_class_loaders_.begin(),
                        relative_class_loaders_.end(), loader);
  if (iter == relative_class_loaders_.end()) {
    relative_class_loaders_.emplace_back(loader);
    if (loader) {
      library_path_ = loader->GetLibraryPath();
    }
  }
}

void AbstractClassFactoryBase::RemoveOwnedClassLoader(
    const ClassLoader* loader) {
  std::vector<ClassLoader*>::iterator itr = std::find(
      relative_class_loaders_.begin(), relative_class_loaders_.end(), loader);
  if (itr != relative_class_loaders_.end()) {
    relative_class_loaders_.erase(itr);
  }
}

bool AbstractClassFactoryBase::IsOwnedBy(const ClassLoader* loader) {
  std::vector<ClassLoader*>::iterator itr = std::find(
      relative_class_loaders_.begin(), relative_class_loaders_.end(), loader);
  return itr != relative_class_loaders_.end();
}

bool AbstractClassFactoryBase::IsOwnedByAnybody() {
  return !relative_class_loaders_.empty();
}

}  // namespace utility
}  // namespace class_loader
}  // namespace cyber
}  // namespace apollo
