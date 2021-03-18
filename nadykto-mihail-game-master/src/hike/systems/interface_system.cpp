#include "hike/systems/interface_system.h"

#include <BearLibTerminal.h>

#include <string>

#include "hike/components/armor_component.h"
#include "hike/components/coin_count_component.h"
#include "hike/components/health_component.h"
#include "hike/components/offset_component.h"
#include "hike/components/player_control_component.h"
#include "hike/components/step_count_component.h"
#include "hike/components/sword_component.h"
#include "hike/includes.h"
#include "lib/ecs/entity_manager.h"

void InterfaceSystem::OnUpdate() {}
void InterfaceSystem::OnPreUpdate() {
  terminal_clear_area(terminal_state(TK_WIDTH) - 14, 1, 14, terminal_state(TK_HEIGHT) - 1);
  for (auto &e : GetEntityManager()) {
    if (e.Contains<PlayerControlComponent>() && e.Contains<OffsetComponent>()) {
      char buffer[6];
      snprintf(buffer, sizeof(buffer), "%i", level_number_);
      terminal_printf(terminal_state(TK_WIDTH) - 5, 1, buffer);
      int value = e.Get<CoinCountComponent>()->count_;
      snprintf(buffer, sizeof(buffer), "%i", value);
      terminal_printf(terminal_state(TK_WIDTH) - 5, 3, buffer);
      value = e.Get<StepCountComponent>()->step_count_;
      snprintf(buffer, sizeof(buffer), "%i", value);
      terminal_printf(terminal_state(TK_WIDTH) - 5, 4, buffer);
      value = e.Get<HealthComponent>()->health_;
      snprintf(buffer, sizeof(buffer), "%i", value);
      terminal_printf(terminal_state(TK_WIDTH) - 5, 5, buffer);
      value = e.Get<SwordComponent>()->damage_;
      /*if (graphics_) {
        terminal_put(terminal_state(TK_WIDTH) - 5, 6, swords[value]);
      } else {*/
      snprintf(buffer, sizeof(buffer), "%i", value);
      terminal_printf(terminal_state(TK_WIDTH) - 5, 6, buffer);
      // }
      value = e.Get<ArmorComponent>()->protection_;
      /*if (graphics_) {
        terminal_put(terminal_state(TK_WIDTH) - 5, 7, armors[value]);
      } else {*/
      snprintf(buffer, sizeof(buffer), "%i", value);
      terminal_printf(terminal_state(TK_WIDTH) - 5, 7, buffer);
      // }
      value = e.Get<StepCountComponent>()->balance_;
      snprintf(buffer, sizeof(buffer), "%i", value);
      terminal_printf(terminal_state(TK_WIDTH) - 5, terminal_state(TK_HEIGHT) - 2, buffer);
    }
  }

  terminal_printf(terminal_state(TK_WIDTH) - 11, 1, "level");
  terminal_printf(terminal_state(TK_WIDTH) - 10, 3, "coin:");
  terminal_printf(terminal_state(TK_WIDTH) - 11, 4, "steps:");
  terminal_printf(terminal_state(TK_WIDTH) - 12, 5, "health:");
  terminal_printf(terminal_state(TK_WIDTH) - 11, 6, "sword:");
  terminal_printf(terminal_state(TK_WIDTH) - 11, 7, "armor:");
  terminal_printf(terminal_state(TK_WIDTH) - 13, terminal_state(TK_HEIGHT) - 2, "balance:");
}

void InterfaceSystem::OnPostUpdate() {}
InterfaceSystem::InterfaceSystem(EntityManager *entity_manager, SystemManager *system_manager, Context *ctx)
    : ISystem(entity_manager, system_manager) {
  level_number_ = ctx->level_number;
  graphics_ = ctx->graphic;
}
