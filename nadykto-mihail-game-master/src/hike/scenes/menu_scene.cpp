#include "hike/scenes/menu_scene.h"

#include <utility>

#include "hike/components/choose_component.h"
#include "hike/components/player_control_component.h"
#include "hike/components/string_component.h"
#include "hike/components/texture_component.h"
#include "hike/components/toggle_component.h"
#include "hike/components/transform_component.h"
#include "hike/layer.h"
#include "hike/systems/choose_system.h"
#include "hike/systems/menu_move_system.h"
#include "hike/systems/rendering_system.h"
#include "hike/systems/toggle_system.h"

void MenuScene::OnCreate() {
  Layer fence_layer;
  int center = terminal_state(TK_WIDTH)/2 - terminal_state(TK_WIDTH)/5;
  fence_layer.AddFacility(std::make_pair(center - 1, 4), '#');
  fence_layer.AddFacility(std::make_pair(center - 1, 8), '#');

    Entity* pointer = engine.GetEntityManager()->CreateEntity();
    pointer->Add<TransformComponent>(center - 1, 5);
    pointer->Add<TextureComponent>('>', 0x10B9);
    pointer->Add<PlayerControlComponent>(fence_layer.GetFacility());

  {
    Entity* item = engine.GetEntityManager()->CreateEntity();
    item->Add<TransformComponent>(center, 5);
    item->Add<StringComponent>("New game");
    item->Add<ChooseComponent>("level");
  }
  {
    Entity* item = engine.GetEntityManager()->CreateEntity();
    item->Add<TransformComponent>(center, 6);
    item->Add<StringComponent>("Continue");
    item->Add<ChooseComponent>("level");
  }
  {
    Entity* item = engine.GetEntityManager()->CreateEntity();
    item->Add<TransformComponent>(center, 7);
    item->Add<StringComponent>("Graphics");
    item->Add<ToggleComponent>(ctx_->graphic);
  }
  {
    Entity* item = engine.GetEntityManager()->CreateEntity();
    item->Add<TransformComponent>(terminal_state(TK_WIDTH)/2, 2);
    item->Add<StringComponent>("HIKE");
  }

  auto sys = engine.GetSystemManager();
  sys->AddSystem<RenderingSystem>(ctx_, pointer);
  sys->AddSystem<MenuMoveSystem>(controls);
  sys->AddSystem<ChooseSystem>(ctx_);
  sys->AddSystem<ToggleSystem>(ctx_);
}
void MenuScene::OnRender() {
  engine.OnUpdate();
}
void MenuScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
MenuScene::MenuScene(Context* const ctx, Controls* controls) : IScene(ctx), controls(controls) {}
