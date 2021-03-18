#include "hike/systems/game_over_system.h"

#include <fstream>

#include "hike/components/health_component.h"
#include "hike/components/step_count_component.h"

void GameOverSystem::OnUpdate() {
  if ((player_->Get<StepCountComponent>()->balance_ <= 0) || (player_->Get<HealthComponent>()->health_ <= 0)) {
    ctx_->scene_ = "result";
    ctx_->level_number = 1;
    ctx_->is_first_ = true;
    std::ofstream out;
    out.open(save_path_);
    if (out.is_open()) {
      out << "coins#" << 0 << std::endl;
      out << "steps#" << 0 << std::endl;
      out << "health#" << 20 << std::endl;
      out << "sword#" << 0 << std::endl;
      out << "armor#" << 0;
    }
  }
}
