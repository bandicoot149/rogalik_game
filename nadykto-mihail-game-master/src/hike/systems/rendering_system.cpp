#include "hike/systems/rendering_system.h"

#include <BearLibTerminal.h>

#include <string>

#include "hike/components/offset_component.h"
#include "hike/components/player_control_component.h"
#include "hike/components/string_component.h"
#include "hike/components/texture_component.h"
#include "hike/components/transform_component.h"
#include "hike/scenes/game_scene.h"
#include "lib/ecs/entity_manager.h"

void RenderingSystem::OnUpdate() {
  for (auto& e : GetEntityManager()) {
    if (e.Contains<TransformComponent>() && e.Contains<TextureComponent>()) {
      auto texture = e.Get<TextureComponent>();
      int display;
      if (ctx_->graphic) {
        display = texture->tile_;
      } else {
        display = texture->symbol_;
      }
      auto transform = e.Get<TransformComponent>();
      terminal_put(transform->x_, transform->y_, display);
    }
    if (e.Contains<StringComponent>()) {
      std::string texture = e.Get<StringComponent>()->name_;
      char buffer[20];
      texture.copy(buffer, texture.size() + 1);
      buffer[texture.size()] = '\0';
      auto transform = e.Get<TransformComponent>();
      terminal_printf(transform->x_, transform->y_, buffer);
    }
  }
}
void RenderingSystem::OnPreUpdate() {
  terminal_clear();
}
void RenderingSystem::OnPostUpdate() {
  terminal_refresh();
}
RenderingSystem::RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager, Context* ctx,
                                 Entity* player)
    : ISystem(entity_manager, system_manager), ctx_(ctx), player_(player) {}
