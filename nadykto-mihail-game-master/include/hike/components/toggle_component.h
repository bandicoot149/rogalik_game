#ifndef INCLUDE_HIKE_COMPONENTS_TOGGLE_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_TOGGLE_COMPONENT_H_

#include <lib/ecs/component.h>

class ToggleComponent : public IComponent {
 public:
  bool status_;
  explicit ToggleComponent(bool status) : status_(status) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_TOGGLE_COMPONENT_H_
