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

/*****************************************************************************************************************
 *
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/

#pragma once

#include <optional>
#include <smacc2/smacc_client.hpp>

namespace smacc2
{
namespace client_bases
{
class SmaccPublisherClient : public smacc2::ISmaccClient
{
public:
  std::optional<std::string> topicName;
  std::optional<int> queueSize;

  SmaccPublisherClient();
  virtual ~SmaccPublisherClient();

  template <typename MessageType>
  void configure(std::string topicName)
  {
    this->topicName = topicName;
    if (!initialized_)
    {
      if (!this->topicName)
      {
        RCLCPP_ERROR(
          getNode()->get_logger(), "topic publisher with no topic name set. Skipping advertising.");
        return;
      }

      if (!queueSize) queueSize = 1;
      rclcpp::SensorDataQoS qos;
      qos.keep_last(*queueSize);

      RCLCPP_INFO_STREAM(
        getNode()->get_logger(),
        "[" << this->getName() << "] Client Publisher to topic: " << topicName);
      pub_ = getNode()->create_publisher<MessageType>(*(this->topicName), qos);

      this->initialized_ = true;
    }
  }

  template <typename MessageType>
  void publish(const MessageType & msg)
  {
    //pub_->publish(msg);
    std::dynamic_pointer_cast<rclcpp::Publisher<MessageType>>(pub_)->publish(msg);
  }

  rclcpp::PublisherBase::SharedPtr pub_;

private:
  bool initialized_;
};
}  // namespace client_bases
}  // namespace smacc2
