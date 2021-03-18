#include "hike/scenes/result_scene.h"

#include <string>
#include <utility>

#include "hike/components/choose_component.h"
#include "hike/components/player_control_component.h"
#include "hike/components/string_component.h"
#include "hike/components/texture_component.h"
#include "hike/components/transform_component.h"
#include "hike/layer.h"
#include "hike/systems/choose_system.h"
#include "hike/systems/menu_move_system.h"
#include "hike/systems/move_system.h"
#include "hike/systems/rendering_system.h"
#include "hike/systems/result_system.h"

void ResultScene::OnCreate() {
  Layer fence_layer;
  int center = terminal_state(TK_WIDTH)/2 - terminal_state(TK_WIDTH)/5;
  fence_layer.AddFacility(std::make_pair(center - 1, 4), '#');
  fence_layer.AddFacility(std::make_pair(center - 1, 7), '#');

    Entity* pointer = engine.GetEntityManager()->CreateEntity();
    pointer->Add<TransformComponent>(center - 1, 5);
    pointer->Add<TextureComponent>('>', 0x1088);
    pointer->Add<PlayerControlComponent>(fence_layer.GetFacility());

  {
    Entity* item = engine.GetEntityManager()->CreateEntity();
    item->Add<TransformComponent>(center, 5);
    item->Add<StringComponent>("next level");
    item->Add<ChooseComponent>("level");
  }
  {
    Entity* item = engine.GetEntityManager()->CreateEntity();
    item->Add<TransformComponent>(center, 6);
    item->Add<StringComponent>("menu");
    item->Add<ChooseComponent>("menu");
  }

  auto sys = engine.GetSystemManager();
  sys->AddSystem<ResultSystem>(results_path_);
  sys->AddSystem<RenderingSystem>(ctx_, pointer);
  sys->AddSystem<MenuMoveSystem>(controls);
  sys->AddSystem<ChooseSystem>(ctx_);
}
void ResultScene::OnRender() {
  engine.OnUpdate();
}
void ResultScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
ResultScene::ResultScene(Context* const ctx, Controls* controls, std::string results_path)
    : IScene(ctx), controls(controls), results_path_(results_path) {}
