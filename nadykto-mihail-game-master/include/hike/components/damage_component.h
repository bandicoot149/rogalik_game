#ifndef INCLUDE_HIKE_COMPONENTS_DAMAGE_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_DAMAGE_COMPONENT_H_

#include <lib/ecs/component.h>

class DamageComponent : public IComponent {
 public:
  int damage_;
  explicit DamageComponent(int damage) : damage_(damage) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_DAMAGE_COMPONENT_H_
