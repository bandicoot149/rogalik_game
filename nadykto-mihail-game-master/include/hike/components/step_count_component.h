#ifndef INCLUDE_HIKE_COMPONENTS_STEP_COUNT_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_STEP_COUNT_COMPONENT_H_
#include <lib/ecs/component.h>

class StepCountComponent : public IComponent {
 public:
  int step_count_;
  int balance_;
  StepCountComponent(int step_count, int balance) : step_count_(step_count), balance_(balance) {}
};
#endif  // INCLUDE_HIKE_COMPONENTS_STEP_COUNT_COMPONENT_H_
