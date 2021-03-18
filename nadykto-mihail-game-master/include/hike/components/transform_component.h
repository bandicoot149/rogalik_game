#ifndef INCLUDE_HIKE_COMPONENTS_TRANSFORM_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_TRANSFORM_COMPONENT_H_

class TransformComponent : public IComponent {
 public:
  int x_;
  int y_;
  TransformComponent(int x, int y) : x_(x), y_(y) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_TRANSFORM_COMPONENT_H_
