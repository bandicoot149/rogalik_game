#ifndef INCLUDE_HIKE_SYSTEMS_GAME_RENDERING_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_GAME_RENDERING_SYSTEM_H_

#include <lib/ecs/entity.h>

#include "hike/layer.h"
#include "lib/ecs/system.h"
#include "lib/scenes/context.h"

class GameRenderingSystem : public ISystem {
  Context* ctx_;
  Entity* player_;
  int interface_width_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  GameRenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* ctx, Entity* player);
  void DrawFrame(Context* ctx);
};

#endif  // INCLUDE_HIKE_SYSTEMS_GAME_RENDERING_SYSTEM_H_
