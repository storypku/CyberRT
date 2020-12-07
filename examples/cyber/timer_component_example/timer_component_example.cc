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

#include "examples/cyber/timer_component_example/timer_component_example.h"

#include "cyber/class_loader/class_loader.h"
#include "cyber/component/component.h"

bool TimerComponentSample::Init() {
  driver_writer_ = node_->CreateWriter<Driver>("/examples/driver");
  return true;
}

bool TimerComponentSample::Proc() {
  static int i = 0;
  auto out_msg = std::make_shared<Driver>();
  out_msg->mutable_header()->set_seq(i++);
  driver_writer_->Write(out_msg);
  AINFO << "Driver msg writen: " << out_msg->ShortDebugString();
  return true;
}
