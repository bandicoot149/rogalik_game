#include "hike/systems/choose_system.h"

#include <hike/components/choose_component.h>
#include <hike/components/player_control_component.h>
#include <hike/components/string_component.h>
#include <hike/components/transform_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

#include <string>

static bool FilterPlayer(const Entity& entity) {
  return entity.Contains<PlayerControlComponent>();
}

static bool FilterOther(const Entity& entity) {
  return entity.Contains<ChooseComponent>() && entity.Contains<TransformComponent>();
}

void ChooseSystem::Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;
  }
  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();
  auto cc2 = entity_2->Get<ChooseComponent>();
  if (tc1->x_ == tc2->x_ && tc1->y_ == tc2->y_) {
    ctx_->scene_ = cc2->name_scene_;
    if (entity_2->Contains<StringComponent>()) {
      auto sc2 = entity_2->Get<StringComponent>();
      if (sc2->name_ == "New game") {
        ctx_->level_number = 1;
        ctx_->is_first_ = true;
      } else if (sc2->name_ == "Continue") {
        ctx_->is_first_ = false;
      }
    }
  }
}

void ChooseSystem::OnUpdate() {
  for (auto& entity_1 : GetEntityManager()) {
    if (FilterPlayer(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (FilterOther(entity_2)) {
          Collide(&entity_1, &entity_2);
        }
      }
    }
  }
}
