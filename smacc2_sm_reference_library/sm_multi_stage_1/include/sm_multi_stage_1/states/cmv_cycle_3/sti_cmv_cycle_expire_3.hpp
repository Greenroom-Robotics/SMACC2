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

namespace sm_multi_stage_1
{
namespace cmv_cycle_3
{
// STATE DECLARATION
struct StiCMVCycleExpire3 : smacc2::SmaccState<StiCMVCycleExpire3, SsCMVCycle3>
{
  using SmaccState::SmaccState;

  // DECLARE CUSTOM OBJECT TAGS
  struct TIMEOUT : ABORT{};
  struct NEXT : SUCCESS{};
  struct PREVIOUS : ABORT{};
  struct RETURN : CANCEL{};

  // TRANSITION TABLE
  typedef mpl::list<

    Transition<EvKeyPressP<CbDefaultKeyboardBehavior, OrKeyboard>, StiCMVCycleDwell3, SUCCESS>,
    Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, StiCMVCyclePulse3, SUCCESS>,
    Transition<EvKeyPressN<CbDefaultKeyboardBehavior, OrKeyboard>, StiCMVCycleTitrate3, SUCCESS>

    //Transition<EvKeyPressZ<CbDefaultKeyboardBehavior, OrKeyboard>, StObserve2, RETURN>,
    //Transition<EvKeyPressX<CbDefaultKeyboardBehavior, OrKeyboard>, MsRecovery2, ABORT>

    >reactions;

  // STATE FUNCTIONS
  static void staticConfigure()
  {
    configure_orthogonal<OrTimer, CbTimerCountdownOnce>(20);
    configure_orthogonal<OrSubscriber, CbWatchdogSubscriberBehavior>();
    configure_orthogonal<OrUpdatablePublisher, CbDefaultPublishLoop>();
    configure_orthogonal<OrKeyboard, CbDefaultKeyboardBehavior>();
  }

  void runtimeConfigure() {}

  void onEntry() { RCLCPP_INFO(getLogger(), "On Entry!"); }

  void onExit() { RCLCPP_INFO(getLogger(), "On Exit!"); }
};
}  // namespace cmv_cycle_1
}  // namespace sm_multi_stage_1
