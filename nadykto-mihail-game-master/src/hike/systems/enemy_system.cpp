#include "hike/systems/enemy_system.h"

#include <hike/components/player_control_component.h>
#include <hike/components/transform_component.h>
#include <lib/ecs/entity_manager.h>

#include <cmath>

#include "hike/components/offset_component.h"

static bool FilterPlayer(const Entity& entity) {
  return (entity.Contains<PlayerControlComponent>() && entity.Contains<OffsetComponent>());
}

static bool FilterEnemy(const Entity& entity) {
  return (entity.Contains<PlayerControlComponent>() && entity.Contains<TransformComponent>());
}

void EnemySystem::Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;
  }
  auto tcp = entity_1->Get<TransformComponent>();
  auto tce = entity_2->Get<TransformComponent>();
  auto ecp = entity_2->Get<PlayerControlComponent>();
  int length = round(pow(tcp->x_ - tce->x_, 2) + pow(tcp->y_ - tce->y_, 2));
  if (length < 14) {
    if (tce->x_ < tcp->x_) {
      if (ecp->floor_[std::make_pair(tce->x_ + 1, tce->y_)] == '.') {
        tce->x_ += 1;
      }
    } else if (tce->x_ > tcp->x_) {
      if (ecp->floor_[std::make_pair(tce->x_ - 1, tce->y_)] == '.') {
        tce->x_ -= 1;
      }
    } else if (tce->y_ < tcp->y_) {
      if (ecp->floor_[std::make_pair(tce->x_, tce->y_ + 1)] == '.') {
        tce->y_ += 1;
      }
    } else if (tce->y_ > tcp->y_) {
      if (ecp->floor_[std::make_pair(tce->x_, tce->y_ - 1)] == '.') {
        tce->y_ -= 1;
      }
    }
  }
}

void EnemySystem::OnUpdate() {
  for (auto& entity_1 : GetEntityManager()) {
    if (FilterPlayer(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (FilterEnemy(entity_2)) {
          Collide(&entity_1, &entity_2);
        }
      }
    }
  }
}
