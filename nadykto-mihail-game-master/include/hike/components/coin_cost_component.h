#ifndef INCLUDE_HIKE_COMPONENTS_COIN_COST_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_COIN_COST_COMPONENT_H_

#include <lib/ecs/component.h>

class CoinCostComponent : public IComponent {
 public:
  int cost_;
  explicit CoinCostComponent(int cost) : cost_(cost) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_COIN_COST_COMPONENT_H_
