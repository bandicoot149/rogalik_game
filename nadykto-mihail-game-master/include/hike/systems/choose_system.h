#ifndef INCLUDE_HIKE_SYSTEMS_CHOOSE_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_CHOOSE_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>
#include <lib/scenes/context.h>

class ChooseSystem : public ISystem {
  Context* ctx_;

 public:
  ChooseSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* ctx)
      : ISystem(entity_manager, system_manager), ctx_(ctx) {}

 protected:
  void OnUpdate() override;
  void Collide(Entity* entity_1, Entity* entity_2);
};

#endif  // INCLUDE_HIKE_SYSTEMS_CHOOSE_SYSTEM_H_
