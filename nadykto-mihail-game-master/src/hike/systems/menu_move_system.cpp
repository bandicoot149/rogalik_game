#include "hike/systems/menu_move_system.h"

#include <hike/components/player_control_component.h>
#include <hike/components/transform_component.h>

#include <utility>

#include "lib/ecs/entity_manager.h"

static bool Filter(const Entity& entity) {
  return entity.Contains<PlayerControlComponent>();
}

void MenuMoveSystem::OnUpdateEntity(Entity* entity) const {
  if (terminal_has_input()) {
    controls_->OnUpdate();
  }
  auto tc = entity->Get<TransformComponent>();
  auto pcc = entity->Get<PlayerControlComponent>();
  int button = controls_->GetButton();
  if (controls_->IsPressed(button) && !(buttons_.find(button) == buttons_.end())) {
    if (pcc->floor_[std::make_pair((tc->x_ + buttons_.at(button).first), (tc->y_ + buttons_.at(button).second))] !=
        '#') {
      tc->x_ += buttons_.at(button).first;
      tc->y_ += buttons_.at(button).second;
    }
  }
}

void MenuMoveSystem::OnPostUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      OnUpdateEntity(&entity);
    }
  }
}
MenuMoveSystem::MenuMoveSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                               Controls* controls)
    : ISystem(entity_manager, system_manager), controls_(controls) {
  buttons_.emplace(TK_UP, std::make_pair(0, -1));
  buttons_.emplace(TK_DOWN, std::make_pair(0, 1));
  buttons_.emplace(TK_ENTER, std::make_pair(1, 0));
}
