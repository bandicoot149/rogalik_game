#ifndef INCLUDE_HIKE_COMPONENTS_OFFSET_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_OFFSET_COMPONENT_H_

#include <lib/ecs/component.h>

class OffsetComponent : public IComponent {
 public:
  int x_;
  int y_;
  int dx_;
  int dy_;
  OffsetComponent(int x, int y, int dx, int dy) : x_(x), y_(y), dx_(dx), dy_(dy) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_OFFSET_COMPONENT_H_
