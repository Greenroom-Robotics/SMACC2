// Copyright 2021 RobosoftAI Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <sm_dance_bot_lite/clients/cl_lidar/cl_lidar.hpp>
#include <smacc2/smacc_orthogonal.hpp>

namespace sm_dance_bot_lite
{
class OrObstaclePerception : public smacc2::Orthogonal<OrObstaclePerception>
{
public:
  void onInitialize() override
  {
    auto lidarClient = this->createClient<ClLidarSensor>();

    lidarClient->topicName = "/scan";
    lidarClient->timeout_ = rclcpp::Duration(std::chrono::seconds(10));
  }
};
}  // namespace sm_dance_bot_lite
