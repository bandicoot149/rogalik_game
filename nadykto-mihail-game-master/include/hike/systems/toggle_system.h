#ifndef INCLUDE_HIKE_SYSTEMS_TOGGLE_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_TOGGLE_SYSTEM_H_

#include <lib/ecs/entity.h>

#include "lib/ecs/system.h"
#include "lib/scenes/context.h"

class ToggleSystem : public ISystem {
  Context* ctx_;

 public:
  ToggleSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* ctx)
      : ISystem(entity_manager, system_manager), ctx_(ctx) {}

 protected:
  void OnPreUpdate() override;
  void Collide(Entity* entity_1, Entity* entity_2);
};

#endif  // INCLUDE_HIKE_SYSTEMS_TOGGLE_SYSTEM_H_
