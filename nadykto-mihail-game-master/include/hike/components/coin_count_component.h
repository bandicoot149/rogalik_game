#ifndef INCLUDE_HIKE_COMPONENTS_COIN_COUNT_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_COIN_COUNT_COMPONENT_H_
#include <lib/ecs/component.h>

class CoinCountComponent : public IComponent {
 public:
  int count_;
  explicit CoinCountComponent(int count) : count_(count) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_COIN_COUNT_COMPONENT_H_
