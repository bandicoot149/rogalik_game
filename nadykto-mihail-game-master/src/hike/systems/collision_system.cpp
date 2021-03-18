#include "hike/systems/collision_system.h"

#include <hike/components/coin_count_component.h>
#include <hike/components/collision_component.h>
#include <hike/components/player_control_component.h>
#include <hike/components/step_count_component.h>
#include <hike/components/transform_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

#include <fstream>
#include <map>
#include <utility>

#include "hike/components/armor_component.h"
#include "hike/components/choose_component.h"
#include "hike/components/coin_cost_component.h"
#include "hike/components/damage_component.h"
#include "hike/components/door_component.h"
#include "hike/components/health_component.h"
#include "hike/components/offset_component.h"
#include "hike/components/potion_component.h"
#include "hike/components/save_path_component.h"
#include "hike/components/sword_component.h"
#include "hike/components/texture_component.h"
#include "hike/includes.h"

static bool FilterPlayer(const Entity& entity) {
  return entity.Contains<PlayerControlComponent>() && entity.Contains<OffsetComponent>();
}

static bool FilterOther(const Entity& entity) {
  return entity.Contains<CollisionComponent>() && entity.Contains<TransformComponent>();
}

void CollisionSystem::Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;
  }
  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();
  if (tc1->x_ == tc2->x_ && tc1->y_ == tc2->y_) {
    if (entity_2->Contains<SavePathComponent>()) {
      std::ofstream out;
      out.open(entity_2->Get<SavePathComponent>()->path_);
      if (out.is_open()) {
        out << "coins#" << entity_1->Get<CoinCountComponent>()->count_ << std::endl;
        out << "steps#" << entity_1->Get<StepCountComponent>()->step_count_ << std::endl;
        out << "health#" << entity_1->Get<HealthComponent>()->health_ << std::endl;
        out << "sword#" << entity_1->Get<SwordComponent>()->damage_ << std::endl;
        out << "armor#" << entity_1->Get<ArmorComponent>()->protection_;
      }
      if (entity_2->Contains<DoorComponent>()) {
        if (entity_2->Get<DoorComponent>()->vector_) {
          ctx_->level_number++;
          *entrance_side_ = true;
          ctx_->scene_ = "result";
        } else {
          ctx_->level_number--;
          *entrance_side_ = false;
        }
      }
    } else if (entity_2->Contains<CoinCostComponent>() && entity_1->Contains<CoinCountComponent>()) {
      auto coin_count1 = entity_1->Get<CoinCountComponent>();
      auto coin_cost2 = entity_2->Get<CoinCostComponent>();
      coin_count1->count_ += coin_cost2->cost_;
      GetEntityManager().DeleteEntity(entity_2->GetId());
    } else if (entity_2->Contains<HealthComponent>() && entity_2->Contains<DamageComponent>() &&
               entity_2->Contains<PlayerControlComponent>()) {
      auto hc2 = entity_2->Get<HealthComponent>();
      auto ac2 = entity_2->Get<ArmorComponent>();
      auto dc1 = entity_1->Get<DamageComponent>();
      auto sc1 = entity_1->Get<SwordComponent>();
      auto hc1 = entity_1->Get<HealthComponent>();
      auto ac1 = entity_1->Get<ArmorComponent>();
      auto dc2 = entity_2->Get<DamageComponent>();
      auto sc2 = entity_2->Get<SwordComponent>();
      int player_damage = dc1->damage_ + sc1->damage_ - ac2->protection_;
      if (player_damage > 0) {
        hc2->health_ -= player_damage;
      }
      int enemy_damage = dc2->damage_ + sc2->damage_ - ac1->protection_;
      if (enemy_damage > 0) {
        hc1->health_ -= enemy_damage;
      }
      if (hc2->health_ <= 0) {
        if (entity_2->Get<SwordComponent>()->damage_ != 0) {
          auto coordinates = CreateDropCoordinates(entity_2, true);
          if (coordinates != std::make_pair(0, 0)) {
            Entity* sword1 = GetEntityManager().CreateEntity();
            sword1->Add<TransformComponent>(coordinates.first, coordinates.second);
            sword1->Add<CollisionComponent>();
            sword1->Add<SwordComponent>(entity_2->Get<SwordComponent>()->damage_);
            sword1->Add<TextureComponent>('S', swords[entity_2->Get<SwordComponent>()->damage_]);
          }
        }
        if (entity_2->Get<ArmorComponent>()->protection_ != 0) {
          auto coordinates = CreateDropCoordinates(entity_2, false);
          if (coordinates != std::make_pair(0, 0)) {
            Entity* armor = GetEntityManager().CreateEntity();
            armor->Add<TransformComponent>(coordinates.first, coordinates.second);
            armor->Add<CollisionComponent>();
            armor->Add<ArmorComponent>(entity_2->Get<ArmorComponent>()->protection_);
            armor->Add<TextureComponent>('A', armors[entity_2->Get<ArmorComponent>()->protection_]);
          }
        }
        GetEntityManager().DeleteEntity(entity_2->GetId());
      }
    } else if (entity_2->Contains<SwordComponent>() && !entity_2->Contains<PlayerControlComponent>()) {
      int damage = entity_1->Get<SwordComponent>()->damage_;
      if (damage != 0) {
        auto coordinates = CreateDropCoordinates(entity_1, true);
        if (coordinates != std::make_pair(0, 0)) {
          Entity* sword = GetEntityManager().CreateEntity();
          sword->Add<TransformComponent>(coordinates.first, coordinates.second);
          sword->Add<CollisionComponent>();
          sword->Add<SwordComponent>(damage);
          sword->Add<TextureComponent>('S', swords[damage]);
        }
      }
      entity_1->Get<SwordComponent>()->damage_ = entity_2->Get<SwordComponent>()->damage_;
      entity_2->Delete<TransformComponent>();  // если удалять - дамп памяти, но только в том случае, если я создаю
      // новый с интерфейсом и графикой не связано, рушится при наличии сворд или текстур компонента
    } else if (entity_2->Contains<ArmorComponent>() && !entity_2->Contains<PlayerControlComponent>()) {
      int protection = entity_1->Get<ArmorComponent>()->protection_;
      if (protection != 0) {
        auto coordinates = CreateDropCoordinates(entity_1, false);
        if (coordinates != std::make_pair(0, 0)) {
          Entity* armor = GetEntityManager().CreateEntity();
          armor->Add<TransformComponent>(coordinates.first, coordinates.second);
          armor->Add<CollisionComponent>();
          armor->Add<ArmorComponent>(protection);
          armor->Add<TextureComponent>('A', armors[protection]);
        }
      }
      entity_1->Get<ArmorComponent>()->protection_ = entity_2->Get<ArmorComponent>()->protection_;
      entity_2->Delete<TransformComponent>();
    } else if (entity_2->Contains<PotionComponent>()) {
      entity_1->Get<HealthComponent>()->health_ += entity_2->Get<PotionComponent>()->health_;
      GetEntityManager().DeleteEntity(entity_2->GetId());
    }
  }
}

void CollisionSystem::OnUpdate() {
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
std::pair<int, int> CollisionSystem::CreateDropCoordinates(Entity* entity, bool type) {
  std::pair<int, int> coordinates = std::make_pair(0, 0);
  auto tc = entity->Get<TransformComponent>();
  std::map<std::pair<int, int>, char> floor = entity->Get<PlayerControlComponent>()->floor_;
  if (type) {
    int x = 0;
    if (floor.find(std::make_pair(tc->x_ + 1, tc->y_)) != floor.end()) {
      x = 1;
    } else if (floor.find(std::make_pair(tc->x_ - 1, tc->y_)) != floor.end()) {
      x = -1;
    }
    if (x != 0) {
      coordinates = std::make_pair(tc->x_ + x, tc->y_);
    }
  } else {
    int y = 0;
    if (floor.find(std::make_pair(tc->x_, tc->y_ + 1)) != floor.end()) {
      y = 1;
    } else if (floor.find(std::make_pair(tc->x_, tc->y_ - 1)) != floor.end()) {
      y = -1;
    }
    if (y != 0) {
      coordinates = std::make_pair(tc->x_, tc->y_ + y);
    }
  }
  return coordinates;
}
