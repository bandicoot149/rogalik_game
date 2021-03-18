#include "hike/scenes/game_scene.h"

#include <BearLibTerminal.h>

#include <map>
#include <random>
#include <string>
#include <utility>

#include "hike/components/armor_component.h"
#include "hike/components/coin_cost_component.h"
#include "hike/components/coin_count_component.h"
#include "hike/components/collision_component.h"
#include "hike/components/damage_component.h"
#include "hike/components/door_component.h"
#include "hike/components/health_component.h"
#include "hike/components/offset_component.h"
#include "hike/components/player_control_component.h"
#include "hike/components/potion_component.h"
#include "hike/components/save_path_component.h"
#include "hike/components/step_count_component.h"
#include "hike/components/sword_component.h"
#include "hike/components/texture_component.h"
#include "hike/components/transform_component.h"
#include "hike/includes.h"
#include "hike/layer.h"
#include "hike/systems/collision_system.h"
#include "hike/systems/enemy_system.h"
#include "hike/systems/game_over_system.h"
#include "hike/systems/game_rendering_system.h"
#include "hike/systems/interface_system.h"
#include "hike/systems/move_system.h"
#include "lib/map_generator/map_generator.h"

void GameScene::OnCreate() {
  terminal_clear();
  start_steps_ = 0;
  start_coins_ = 0;
  int width_center = (terminal_state(TK_WIDTH) - 20) / 2;  // координаты для смещения карты на центр игрового окна
  int height_center = terminal_state(TK_HEIGHT) / 2;
  if (ctx_->level_number > 1) {
    ctx_->is_first_ = false;
  }
  if (!ctx_->is_first_) {
    GameScene::ReadResults();
  } else {
    start_heath_ = 20;
    start_steps_ = 0;
    start_coins_ = 0;
    start_sword_ = 0;
    start_armor_ = 0;
  }
  std::default_random_engine rng;
  std::uniform_int_distribution<int> dist_a_b(1, 5);  // для монеток
  std::uniform_int_distribution<int> dist_sword_armor_players(0, 3);
  std::uniform_int_distribution<int> dist_sword_armor(1, 3);
  std::uniform_int_distribution<int> dist_potion(1, 2);
  map_path_ = GenerateMapPath(current_level, map_dir_);
  ReadLayers();

  Entity* player = engine.GetEntityManager()->CreateEntity();
  if (entrance_side) {
    player->Add<TransformComponent>(start_layer_.GetFacility().begin()->first.first,
                                    start_layer_.GetFacility().begin()->first.second);
    player->Add<OffsetComponent>(width_center - start_layer_.GetFacility().begin()->first.first,
                                 height_center - start_layer_.GetFacility().begin()->first.second, 0, 0);
  } else {
    player->Add<TransformComponent>(end_layer_.GetFacility().begin()->first.first - 1,
                                    end_layer_.GetFacility().begin()->first.second);
    player->Add<OffsetComponent>(width_center - end_layer_.GetFacility().begin()->first.first - 1,
                                 height_center - end_layer_.GetFacility().begin()->first.second, 0, 0);
  }
  player->Add<TextureComponent>(start_layer_.GetFacility().begin()->second, 0x1090);
  player->Add<PlayerControlComponent>(floor_layer_.GetFacility());
  player->Add<StepCountComponent>(start_steps_, 500);
  player->Add<CoinCountComponent>(start_coins_);
  player->Add<HealthComponent>(start_heath_);
  player->Add<DamageComponent>(4);
  player->Add<SwordComponent>(start_sword_);
  player->Add<ArmorComponent>(start_armor_);

  for (std::pair<const std::pair<int, int>, char> coordinates : enemy_layer_.GetFacility()) {
    Entity* enemy = engine.GetEntityManager()->CreateEntity();
    enemy->Add<TransformComponent>(coordinates.first.first, coordinates.first.second);
    enemy->Add<TextureComponent>(coordinates.second, 0x1093);
    enemy->Add<PlayerControlComponent>(floor_layer_.GetFacility());
    enemy->Add<HealthComponent>(8);
    enemy->Add<DamageComponent>(1);
    enemy->Add<CollisionComponent>();
    rng.seed(std::random_device()());
    enemy->Add<SwordComponent>(dist_sword_armor_players(rng));
    rng.seed(std::random_device()());
    enemy->Add<ArmorComponent>(dist_sword_armor_players(rng));
  }

  for (std::pair<const std::pair<int, int>, char> coordinates : fence_layer_.GetFacility()) {
    Entity* facility = engine.GetEntityManager()->CreateEntity();
    facility->Add<TransformComponent>(coordinates.first.first, coordinates.first.second);
    facility->Add<TextureComponent>(coordinates.second, 0x1012);
  }
  for (std::pair<const std::pair<int, int>, char> coordinates : potion_layer_.GetFacility()) {
    Entity* potion = engine.GetEntityManager()->CreateEntity();
    potion->Add<TransformComponent>(coordinates.first.first, coordinates.first.second);
    potion->Add<CollisionComponent>();
    rng.seed(std::random_device()());
    int health = 5 * dist_potion(rng);
    potion->Add<TextureComponent>(coordinates.second, potions[health]);
    potion->Add<PotionComponent>(health);
  }
  for (std::pair<const std::pair<int, int>, char> coordinates : coin_layer_.GetFacility()) {
    Entity* coin = engine.GetEntityManager()->CreateEntity();
    coin->Add<TransformComponent>(coordinates.first.first, coordinates.first.second);
    coin->Add<TextureComponent>(coordinates.second, 0x1078);
    coin->Add<CollisionComponent>();
    rng.seed(std::random_device()());
    coin->Add<CoinCostComponent>(dist_a_b(rng));
  }
  for (std::pair<const std::pair<int, int>, char> coordinates : sword_layer_.GetFacility()) {
    Entity* sword = engine.GetEntityManager()->CreateEntity();
    sword->Add<TransformComponent>(coordinates.first.first, coordinates.first.second);
    sword->Add<CollisionComponent>();
    rng.seed(std::random_device()());
    int sword_number = dist_sword_armor(rng);
    sword->Add<SwordComponent>(sword_number);
    sword->Add<TextureComponent>(coordinates.second, swords[sword_number]);
  }

  for (std::pair<const std::pair<int, int>, char> coordinates : armor_layer_.GetFacility()) {
    Entity* armor = engine.GetEntityManager()->CreateEntity();
    armor->Add<TransformComponent>(coordinates.first.first, coordinates.first.second);
    armor->Add<CollisionComponent>();
    rng.seed(std::random_device()());
    int armor_number = dist_sword_armor(rng);
    armor->Add<ArmorComponent>(armor_number);
    armor->Add<TextureComponent>(coordinates.second, armors[armor_number]);
  }

  {
    if (current_level > 1) {
      Entity* enter = engine.GetEntityManager()->CreateEntity();
      enter->Add<TransformComponent>(start_layer_.GetFacility().begin()->first.first - 1,
                                     start_layer_.GetFacility().begin()->first.second);
      enter->Add<TextureComponent>('<', 0x1015);
      enter->Add<SavePathComponent>(result_);
      enter->Add<CollisionComponent>();
      enter->Add<DoorComponent>(false);
    }
  }
  {
    Entity* exit = engine.GetEntityManager()->CreateEntity();
    exit->Add<TransformComponent>(end_layer_.GetFacility().begin()->first.first,
                                  end_layer_.GetFacility().begin()->first.second);
    exit->Add<TextureComponent>(end_layer_.GetFacility().begin()->second, 0x1016);
    exit->Add<SavePathComponent>(result_);
    exit->Add<CollisionComponent>();
    exit->Add<DoorComponent>(true);
  }

  auto sys = engine.GetSystemManager();
  sys->AddSystem<MoveSystem>(controls, (terminal_state(TK_WIDTH) - 20) / 4);
  sys->AddSystem<InterfaceSystem>(ctx_);
  sys->AddSystem<CollisionSystem>(ctx_, &entrance_side);
  sys->AddSystem<GameOverSystem>(ctx_, player, result_);
  sys->AddSystem<GameRenderingSystem>(ctx_, player);
  sys->AddSystem<EnemySystem>();
}
void GameScene::OnRender() {
  engine.OnUpdate();
}
void GameScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
GameScene::GameScene(Context* const ctx, Controls* controls, std::string map_path, std::string result)
    : IScene(ctx), controls(controls), map_dir_(map_path), result_(result) {
  ctx_->level_number = 1;  // изменяется в колизии
  ctx_->graphic = false;   // по умолчаию текстовая графика
  current_level = 1;       // сравнивается в менеджере сцен
  entrance_side = true;  // // отвеает за то, рядом с какой дверью появляется персонаж
  frame_width_ = 30;
  frame_height_ = 23;
}
void GameScene::ReadLayers() {
  fence_layer_.facility_.clear();
  coin_layer_.facility_.clear();
  start_layer_.facility_.clear();
  end_layer_.facility_.clear();
  floor_layer_.facility_.clear();
  enemy_layer_.facility_.clear();
  sword_layer_.facility_.clear();
  armor_layer_.facility_.clear();
  potion_layer_.facility_.clear();
  std::ifstream file(map_path_);
  if (!file.is_open()) {
    file.close();
    std::default_random_engine rng;
    std::uniform_int_distribution<int> dist_width(40, 60);
    std::uniform_int_distribution<int> dist_height(40, 60);
    std::uniform_int_distribution<int> dist_iterations(2, 4);
    bool horizontally = ctx_->level_number % 2 == 0;
    rng.seed(std::random_device()());
    MapGenerator::Generate(map_path_, ctx_->level_number, dist_width(rng), dist_height(rng), dist_iterations(rng),
                           horizontally);
    file.open(map_path_);
  }
  if (file.is_open()) {
    char symbol;
    while (!file.eof()) {
      int i = 1;
      int j = 1;
      while (file.get(symbol)) {
        switch (symbol) {
          case ' ':
            i++;
            break;
          case '\n':
            j++;
            i = 1;  // тоже сдвиг
            break;
          case '#':
            fence_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            i++;
            break;
          case '$':
            coin_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), '.'));
            i++;
            break;
          case '@':
            start_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), '.'));
            i++;
            break;
          case '>':
            end_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), '.'));
            i++;
            break;
          case '.':
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            i++;
            break;
          case 'E':
            enemy_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), '.'));
            i++;
            break;
          case 'S':
            sword_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), '.'));
            i++;
            break;
          case 'A':
            armor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), '.'));
            i++;
            break;
          case 'P':
            potion_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), symbol));
            floor_layer_.facility_.insert(std::make_pair((std::make_pair(i, j)), '.'));
            i++;
            break;
          default:
            i++;
            break;
        }
      }
    }
  }
  file.close();
}
std::string GameScene::GenerateMapPath(int number, std::string map_dir) {
  std::stringstream ss;
  ss << number;
  std::string str = ss.str();
  return (map_dir + "map" + str + ".txt");
}
void GameScene::ReadResults() {
  std::ifstream file(result_);
  std::map<std::string, int> results;
  if (file.is_open()) {
    std::string line;
    std::string divisor = "#";
    while (!file.eof()) {
      size_t pos = 0;
      std::getline(file, line);
      pos = line.find(divisor);
      std::string name = line.substr(0, pos);
      line.erase(0, pos + divisor.length());
      int value = std::stoi(line.substr(0, pos));
      results[name] = value;
    }
  }
  start_coins_ = results["coins"];
  start_steps_ = results["steps"];
  start_heath_ = results["health"];
  start_sword_ = results["sword"];
  start_armor_ = results["armor"];
}
