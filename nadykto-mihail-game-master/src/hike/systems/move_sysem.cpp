#include <hike/components/player_control_component.h>
#include <hike/components/step_count_component.h>
#include <hike/components/transform_component.h>

#include <utility>

#include "hike/components/offset_component.h"
#include "hike/systems/move_system.h"
#include "lib/ecs/entity_manager.h"

static bool Filter(const Entity& entity) {
  return (entity.Contains<PlayerControlComponent>() && entity.Contains<OffsetComponent>());
}

void MoveSystem::OnUpdateEntity(Entity* entity) const {
  controls_->OnUpdate();
  auto tc = entity->Get<TransformComponent>();
  auto oc = entity->Get<OffsetComponent>();
  auto scc = entity->Get<StepCountComponent>();
  auto pcc = entity->Get<PlayerControlComponent>();
  int button = controls_->GetButton();
  if (controls_->IsPressed(button) && !(buttons_.find(button) == buttons_.end())) {
    if (pcc->floor_[std::make_pair((tc->x_ + buttons_.at(button).first), (tc->y_ + buttons_.at(button).second))] ==
        '.') {
      tc->x_ += buttons_.at(button).first;
      tc->y_ += buttons_.at(button).second;
      oc->dx_ += buttons_.at(button).first;
      oc->dy_ += buttons_.at(button).second;
      if (oc->dy_ > offset_ || oc->dy_ < -offset_) {
        oc->y_ -= buttons_.at(button).second;
        if (oc->dy_ > 0) {
          oc->dy_ = offset_;
        } else {
          oc->dy_ = -offset_;
        }
      }
      if (oc->dx_ > offset_ || oc->dx_ < -offset_) {
        oc->x_ -= buttons_.at(button).first;
        if (oc->dx_ > 0) {
          oc->dx_ = offset_;
        } else {
          oc->dx_ = -offset_;
        }
      }
      scc->step_count_++;
      scc->balance_--;
    }
  }
}

void MoveSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      OnUpdateEntity(&entity);
    }
  }
}
MoveSystem::MoveSystem(EntityManager* const entity_manager, SystemManager* const system_manager, Controls* controls,
                       int offset)
    : ISystem(entity_manager, system_manager), controls_(controls), offset_(offset) {
  buttons_.emplace(TK_UP, std::make_pair(0, -1));
  buttons_.emplace(TK_DOWN, std::make_pair(0, 1));
  buttons_.emplace(TK_LEFT, std::make_pair(-1, 0));
  buttons_.emplace(TK_RIGHT, std::make_pair(1, 0));
  buttons_.emplace(TK_SPACE, std::make_pair(0, 0));
  buttons_.emplace(TK_CLOSE, std::make_pair(0, 0));
}
