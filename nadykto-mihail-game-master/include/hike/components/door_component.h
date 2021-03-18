#ifndef INCLUDE_HIKE_COMPONENTS_DOOR_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_DOOR_COMPONENT_H_

#include <lib/ecs/component.h>

class DoorComponent : public IComponent {
 public:
  bool vector_;  // true - следующий уровень, false - предищдущий
  explicit DoorComponent(bool vector) : vector_(vector) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_DOOR_COMPONENT_H_
