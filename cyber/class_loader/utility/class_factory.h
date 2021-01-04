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
#ifndef CYBER_CLASS_LOADER_UTILITY_CLASS_FACTORY_H_
#define CYBER_CLASS_LOADER_UTILITY_CLASS_FACTORY_H_

#include <string>
#include <typeinfo>
#include <vector>

namespace apollo {
namespace cyber {
namespace class_loader {

class ClassLoader;

namespace utility {

class AbstractClassFactoryBase {
 public:
  AbstractClassFactoryBase(const std::string& class_name,
                           const std::string& base_class_name)
      : class_name_(class_name), base_class_name_(base_class_name) {}
  virtual ~AbstractClassFactoryBase() = default;

  void SetLibraryPath(const std::string& library_path);

  void AddOwnedClassLoader(ClassLoader* loader);
  void RemoveOwnedClassLoader(const ClassLoader* loader);
  bool IsOwnedBy(const ClassLoader* loader);
  bool IsOwnedByAnybody();

  const std::string& GetLibraryPath() const { return library_path_; }
  const std::string& GetBaseClassName() const { return base_class_name_; }
  const std::string& GetClassName() const { return class_name_; }

 protected:
  std::vector<ClassLoader*> relative_class_loaders_;
  std::string library_path_;
  std::string class_name_;
  std::string base_class_name_;
};

template <typename Base>
class AbstractClassFactory : public AbstractClassFactoryBase {
 public:
  AbstractClassFactory(const std::string& class_name,
                       const std::string& base_class_name)
      : AbstractClassFactoryBase(class_name, base_class_name) {}

  virtual Base* CreateObj() const = 0;

 public:
  AbstractClassFactory(const AbstractClassFactory&) = delete;
  AbstractClassFactory& operator=(const AbstractClassFactory&) = delete;
};

template <typename ClassObject, typename Base>
class ClassFactory : public AbstractClassFactory<Base> {
 public:
  ClassFactory(const std::string& class_name,
               const std::string& base_class_name)
      : AbstractClassFactory<Base>(class_name, base_class_name) {}

  Base* CreateObj() const { return new ClassObject; }
};

}  // namespace utility
}  // namespace class_loader
}  // namespace cyber
}  // namespace apollo

#endif  // CYBER_CLASS_LOADER_UTILITY_CLASS_FACTORY_H_
