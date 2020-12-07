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

#include "examples/proto/driver.pb.h"

#include "cyber/cyber.h"
#include "cyber/time/time.h"

using apollo::cyber::Time;
using examples::proto::Driver;

int main(int argc, char* argv[]) {
  apollo::cyber::Init(argv[0]);

  std::shared_ptr<apollo::cyber::Node> node =
      apollo::cyber::CreateNode("service_example_node");

  auto server = node->CreateService<Driver, Driver>(
      "test_server", [](const std::shared_ptr<Driver>& request,
                        std::shared_ptr<Driver>& response) {
        auto seq = request->header().seq();
        response->mutable_header()->set_seq(seq + 1);
        response->mutable_header()->set_timestamp(Time::Now().ToNanosecond());
        AINFO << "Received request seq " << seq
              << " from client, sending resp seq: " << (seq + 1);
      });

  auto client = node->CreateClient<Driver, Driver>("test_server");

  uint64_t id = 1;

  while (apollo::cyber::OK()) {
    auto driver_msg = std::make_shared<Driver>();
    auto header = driver_msg->mutable_header();
    header->set_timestamp(Time::Now().ToNanosecond());
    header->set_seq(id);
    auto res = client->SendRequest(driver_msg);
    if (res != nullptr) {
      AINFO << "Client received responese: " << res->ShortDebugString();
    } else {
      AINFO << "Client: service may not ready.";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    id += 2;
  }

  apollo::cyber::WaitForShutdown();
  return 0;
}
