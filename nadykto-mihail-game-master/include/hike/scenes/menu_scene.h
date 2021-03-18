#ifndef INCLUDE_HIKE_SCENES_MENU_SCENE_H_
#define INCLUDE_HIKE_SCENES_MENU_SCENE_H_

#include <hike/controls.h>
#include <lib/ecs/engine.h>
#include <lib/scenes/i_scene.h>

class MenuScene : public IScene {
  const Engine engine{};
  Controls* controls;

 public:
  MenuScene(Context* const ctx, Controls* controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_HIKE_SCENES_MENU_SCENE_H_
