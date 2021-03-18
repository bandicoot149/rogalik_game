#ifndef INCLUDE_HIKE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_

#include <lib/ecs/component.h>

#include <utility>
#include <map>

class PlayerControlComponent : public IComponent {
 public:
  std::map<std::pair<int, int>, char> floor_;
  explicit PlayerControlComponent(std::map<std::pair<int, int>, char> floor) : floor_(std::move(floor)) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_
