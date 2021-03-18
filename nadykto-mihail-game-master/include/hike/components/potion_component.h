#ifndef INCLUDE_HIKE_COMPONENTS_POTION_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_POTION_COMPONENT_H_

#include <lib/ecs/component.h>

class PotionComponent : public IComponent {
 public:
  int health_;
  explicit PotionComponent(int health) : health_(health) {}
};


#endif  // INCLUDE_HIKE_COMPONENTS_POTION_COMPONENT_H_
