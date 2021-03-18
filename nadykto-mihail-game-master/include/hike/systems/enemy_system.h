#ifndef INCLUDE_HIKE_SYSTEMS_ENEMY_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_ENEMY_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>

class EnemySystem : public ISystem {
 public:
  EnemySystem(EntityManager* entity_manager, SystemManager* system_manager) : ISystem(entity_manager, system_manager) {}

 protected:
  void OnUpdate() override;
  void Collide(Entity* entity_1, Entity* entity_2);
};

#endif  // INCLUDE_HIKE_SYSTEMS_ENEMY_SYSTEM_H_
