#ifndef INCLUDE_HIKE_COMPONENTS_CHOOSE_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_CHOOSE_COMPONENT_H_

#include <lib/ecs/component.h>

#include <string>

//  хранит название сцены, при столкновении с объектом включается новая, задумывалась для меню, на данный момент не
//  используется

class ChooseComponent : public IComponent {
 public:
  std::string name_scene_;
  explicit ChooseComponent(std::string name_scene) : name_scene_(name_scene) {}
};

#endif  // INCLUDE_HIKE_COMPONENTS_CHOOSE_COMPONENT_H_
