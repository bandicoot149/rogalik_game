#include "hike/systems/game_rendering_system.h"

#include <BearLibTerminal.h>

#include <string>

#include "hike/components/armor_component.h"
#include "hike/components/offset_component.h"
#include "hike/components/player_control_component.h"
#include "hike/components/string_component.h"
#include "hike/components/sword_component.h"
#include "hike/components/texture_component.h"
#include "hike/components/transform_component.h"
#include "hike/includes.h"
#include "lib/ecs/entity_manager.h"

void GameRenderingSystem::OnUpdate() {}
void GameRenderingSystem::OnPreUpdate() {
  terminal_layer(1);
  terminal_clear_area(1, 1, terminal_state(TK_WIDTH) - (interface_width_ + 1), terminal_state(TK_HEIGHT) - 2);
  terminal_layer(2);
  terminal_clear_area(1, 1, terminal_state(TK_WIDTH) - (interface_width_ + 1), terminal_state(TK_HEIGHT) - 2);
  terminal_layer(3);
  terminal_clear_area(1, 1, terminal_state(TK_WIDTH) - (interface_width_ + 1), terminal_state(TK_HEIGHT) - 2);
  terminal_layer(0);
  GameRenderingSystem::DrawFrame(ctx_);
  terminal_layer(1);
  for (auto& e : GetEntityManager()) {
    if (e.Contains<TransformComponent>() && e.Contains<TextureComponent>()) {
      auto texture = e.Get<TextureComponent>();
      auto transform = e.Get<TransformComponent>();
      int display;
      if (ctx_->graphic) {
        display = texture->tile_;
        if (e.Contains<SwordComponent>() && e.Contains<PlayerControlComponent>()) {
          terminal_layer(3);
          terminal_put(transform->x_ + player_->Get<OffsetComponent>()->x_,
                       transform->y_ + player_->Get<OffsetComponent>()->y_, swords[e.Get<SwordComponent>()->damage_]);
          terminal_crop(1, 1, terminal_state(TK_WIDTH) - (interface_width_ + 1), terminal_state(TK_HEIGHT) - 2);
          terminal_layer(1);
        }
        if (e.Contains<ArmorComponent>() && e.Contains<PlayerControlComponent>()) {
          terminal_layer(2);
          terminal_put(transform->x_ + player_->Get<OffsetComponent>()->x_,
                       transform->y_ + player_->Get<OffsetComponent>()->y_,
                       armors[e.Get<ArmorComponent>()->protection_]);
          terminal_crop(1, 1, terminal_state(TK_WIDTH) - (interface_width_ + 1), terminal_state(TK_HEIGHT) - 2);
          terminal_layer(1);
        }
      } else {
        display = texture->symbol_;
      }
      terminal_put(transform->x_ + player_->Get<OffsetComponent>()->x_,
                   transform->y_ + player_->Get<OffsetComponent>()->y_, display);
    }
  }
  terminal_crop(1, 1, terminal_state(TK_WIDTH) - (interface_width_ + 1),
                terminal_state(TK_HEIGHT) - 2);  // рисуем только в пределах рамки
  if (ctx_->graphic) {
    terminal_layer(0);  // рисуем текстуру пола, слой нижний, чтобы никому не мешать
    for (int i = 1; i < terminal_state(TK_WIDTH) - interface_width_; i++) {
      for (int j = 1; j < terminal_state(TK_HEIGHT) - 1; j++) {
        terminal_put(i, j, 0x101E);
      }
    }
  }
  terminal_refresh();
  terminal_layer(0);
}
void GameRenderingSystem::OnPostUpdate() {}
GameRenderingSystem::GameRenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                         Context* ctx, Entity* player)
    : ISystem(entity_manager, system_manager), ctx_(ctx), player_(player) {
  interface_width_ = 14;  // отступ от левого края для интерфейса
}
void GameRenderingSystem::DrawFrame(Context* ctx) {
  int top_bottom;
  int left_right;
  int corners;
  if (ctx->graphic) {
    top_bottom = 0x1008;
    left_right = 0x1008;
    corners = 0x1009;
  } else {
    top_bottom = '-';
    left_right = '|';
    corners = '+';
  }
  for (int i = 1; i < terminal_state(TK_HEIGHT) - 1; i++) {
    terminal_put(0, i, left_right);
    terminal_put(terminal_state(TK_WIDTH) - interface_width_, i, left_right);
  }
  for (int i = 1; i < terminal_state(TK_WIDTH) - interface_width_; i++) {
    terminal_put(i, 0, top_bottom);
    terminal_put(i, terminal_state(TK_HEIGHT) - 1, top_bottom);
  }
  terminal_put(0, 0, corners);
  terminal_put(0, terminal_state(TK_HEIGHT) - 1, corners);
  terminal_put(terminal_state(TK_WIDTH) - interface_width_, 0, corners);
  terminal_put(terminal_state(TK_WIDTH) - interface_width_, terminal_state(TK_HEIGHT) - 1, corners);
}
