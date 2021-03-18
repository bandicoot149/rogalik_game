#ifndef INCLUDE_HIKE_COMPONENTS_ARMOR_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_ARMOR_COMPONENT_H_

#include <lib/ecs/component.h>

class ArmorComponent : public IComponent {
 public:
  int protection_;
  explicit ArmorComponent(int protection) : protection_(protection) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_ARMOR_COMPONENT_H_
