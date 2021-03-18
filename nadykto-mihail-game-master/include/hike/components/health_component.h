#ifndef INCLUDE_HIKE_COMPONENTS_HEALTH_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_HEALTH_COMPONENT_H_

#include <lib/ecs/component.h>

class HealthComponent : public IComponent {
 public:
  int health_;
  explicit HealthComponent(int health) : health_(health) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_HEALTH_COMPONENT_H_
