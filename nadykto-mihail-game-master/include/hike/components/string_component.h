#ifndef INCLUDE_HIKE_COMPONENTS_STRING_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_STRING_COMPONENT_H_

#include <lib/ecs/component.h>

#include <string>

class StringComponent : public IComponent {
 public:
  std::string name_;

  explicit StringComponent(std::string name) : name_(name) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_STRING_COMPONENT_H_
