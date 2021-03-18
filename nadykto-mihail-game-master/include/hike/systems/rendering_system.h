#ifndef INCLUDE_HIKE_SYSTEMS_RENDERING_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_RENDERING_SYSTEM_H_

#include <lib/ecs/entity.h>

#include "lib/ecs/system.h"
#include "lib/scenes/context.h"

class RenderingSystem : public ISystem {
  Context* ctx_;
  Entity* player_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* ctx, Entity* player);
};

#endif  // INCLUDE_HIKE_SYSTEMS_RENDERING_SYSTEM_H_
