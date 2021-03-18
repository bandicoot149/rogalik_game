#include "hike/systems/toggle_system.h"

#include <hike/components/player_control_component.h>
#include <hike/components/string_component.h>
#include <hike/components/transform_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

#include "hike/components/toggle_component.h"

static bool FilterPlayer(const Entity& entity) {
  return entity.Contains<PlayerControlComponent>();
}

static bool FilterOther(const Entity& entity) {
  return entity.Contains<ToggleComponent>() && entity.Contains<TransformComponent>();
}

void ToggleSystem::Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;  // на данный момент ненужная проверка
  }
  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();
  auto tgc2 = entity_2->Get<ToggleComponent>();
  if (tc1->x_ == tc2->x_ && tc1->y_ == tc2->y_) {
    tc1->x_--;
    tgc2->status_ = !tgc2->status_;
    ctx_->graphic = tgc2->status_;
  }
}

void ToggleSystem::OnPreUpdate() {
  for (auto& entity_1 : GetEntityManager()) {
    if (FilterPlayer(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (FilterOther(entity_2)) {
          if (entity_2.Get<ToggleComponent>()->status_) {
            entity_2.Get<StringComponent>()->name_ = "Graphics : ON";
          } else {
            entity_2.Get<StringComponent>()->name_ = "Graphics : OF";
          }
          Collide(&entity_1, &entity_2);
        }
      }
    }
  }
}
