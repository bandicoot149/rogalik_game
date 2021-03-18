#ifndef INCLUDE_HIKE_COMPONENTS_SWORD_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_SWORD_COMPONENT_H_

#include <lib/ecs/component.h>

class SwordComponent : public IComponent {
 public:
  int damage_;
  explicit SwordComponent(int damage) : damage_(damage) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_SWORD_COMPONENT_H_
