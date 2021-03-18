#ifndef INCLUDE_HIKE_COMPONENTS_SAVE_PATH_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_SAVE_PATH_COMPONENT_H_

#include <lib/ecs/component.h>

#include <string>

class SavePathComponent : public IComponent {
 public:
  std::string path_;

  explicit SavePathComponent(std::string path) : path_(path) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_SAVE_PATH_COMPONENT_H_
