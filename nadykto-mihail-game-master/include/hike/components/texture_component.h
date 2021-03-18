#ifndef INCLUDE_HIKE_COMPONENTS_TEXTURE_COMPONENT_H_
#define INCLUDE_HIKE_COMPONENTS_TEXTURE_COMPONENT_H_
#include <lib/ecs/component.h>
#include <string>

class TextureComponent : public IComponent {
 public:
  int symbol_;
  int tile_;
  TextureComponent(char symbol, int tile) : symbol_(symbol), tile_(tile) {}
};
#endif  // INCLUDE_HIKE_COMPONENTS_TEXTURE_COMPONENT_H_
