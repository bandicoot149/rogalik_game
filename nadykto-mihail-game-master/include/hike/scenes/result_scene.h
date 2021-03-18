#ifndef INCLUDE_HIKE_SCENES_RESULT_SCENE_H_
#define INCLUDE_HIKE_SCENES_RESULT_SCENE_H_

#include <hike/controls.h>
#include <lib/ecs/engine.h>
#include <lib/scenes/i_scene.h>
#include <string>

class ResultScene : public IScene {
  const Engine engine{};
  Controls* controls;
  std::string results_path_;
 public:
  ResultScene(Context* const ctx, Controls* controls, std::string results_path);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_HIKE_SCENES_RESULT_SCENE_H_
