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
#include "cyber/time/rate.h"
#include "cyber/time/time.h"

using apollo::cyber::Rate;
using apollo::cyber::Time;
using examples::proto::Driver;

int main(int argc, char *argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);
  // create talker node
  auto talker_node = apollo::cyber::CreateNode("prediction_writer");
  // create talker
  auto talker = talker_node->CreateWriter<Driver>("/apollo/prediction");
  Rate rate(3.0);

  std::string content("apollo_prediction");
  static uint64_t seq = 0;

  while (apollo::cyber::OK()) {
    seq++;
    auto msg = std::make_shared<Driver>();
    auto header = msg->mutable_header();
    header->set_timestamp(Time::Now().ToNanosecond());
    header->set_seq(seq);
    msg->set_content(content + std::to_string(seq));
    talker->Write(msg);
    AINFO << "/apollo/prediction sent message, seq=" << seq;
    rate.Sleep();
  }
  return 0;
}
