#ifndef INCLUDE_HIKE_SYSTEMS_COLLISION_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_COLLISION_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>
#include <lib/scenes/context.h>

#include <utility>

class CollisionSystem : public ISystem {
  Context* ctx_;
  bool* entrance_side_;

 public:
  CollisionSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* ctx, bool* entrance_side)
      : ISystem(entity_manager, system_manager), ctx_(ctx), entrance_side_(entrance_side) {}

 protected:
  void OnUpdate() override;
  void Collide(Entity* entity_1, Entity* entity_2);
  static std::pair<int, int> CreateDropCoordinates(Entity* entity, bool type);  // sword - true - x, armor - false - y
};

#endif  // INCLUDE_HIKE_SYSTEMS_COLLISION_SYSTEM_H_
