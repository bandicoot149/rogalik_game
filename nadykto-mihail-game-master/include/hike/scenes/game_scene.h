#ifndef INCLUDE_HIKE_SCENES_GAME_SCENE_H_
#define INCLUDE_HIKE_SCENES_GAME_SCENE_H_

#include <hike/controls.h>
#include <lib/ecs/engine.h>
#include <lib/scenes/i_scene.h>

#include <string>

#include "hike/layer.h"

class GameScene : public IScene {
  const Engine engine{};
  Controls* controls;
  std::string map_dir_;
  std::string map_path_;
  std::string result_;
  Entity* player_;
  int start_steps_;
  int start_coins_;
  int start_heath_;
  int start_sword_;
  int start_armor_;
  int frame_width_;
  int frame_height_;
  void ReadResults();
  Layer fence_layer_;
  Layer coin_layer_;
  Layer start_layer_;
  Layer end_layer_;
  Layer floor_layer_;
  Layer enemy_layer_;
  Layer sword_layer_;
  Layer armor_layer_;
  Layer potion_layer_;

 public:
  GameScene(Context* const ctx, Controls* controls, std::string map_path, std::string result);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
  void ReadLayers();
  std::string GenerateMapPath(int number, std::string map_dir);
  bool entrance_side;
};

#endif  // INCLUDE_HIKE_SCENES_GAME_SCENE_H_
