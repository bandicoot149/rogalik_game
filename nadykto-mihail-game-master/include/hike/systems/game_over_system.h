#ifndef INCLUDE_HIKE_SYSTEMS_GAME_OVER_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_GAME_OVER_SYSTEM_H_

#include <lib/ecs/entity.h>

#include <string>

#include "lib/ecs/system.h"
#include "lib/scenes/context.h"

class GameOverSystem : public ISystem {
  Context* ctx_;
  Entity* player_;
  std::string save_path_;

 public:
  GameOverSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* ctx, Entity* player,
                 std::string save_path)
      : ISystem(entity_manager, system_manager), ctx_(ctx), player_(player), save_path_(save_path) {}

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_HIKE_SYSTEMS_GAME_OVER_SYSTEM_H_
