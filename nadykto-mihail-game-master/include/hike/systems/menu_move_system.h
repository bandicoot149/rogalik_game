#ifndef INCLUDE_HIKE_SYSTEMS_MENU_MOVE_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_MENU_MOVE_SYSTEM_H_

#include <hike/controls.h>
#include <lib/ecs/system.h>

#include <map>
#include <utility>

class Entity;

class MenuMoveSystem : public ISystem {
  Controls* controls_;
  std::map<int, std::pair<int, int>> buttons_;
  void OnUpdateEntity(Entity* entity) const;

 protected:
  void OnPostUpdate() override;

 public:
  MenuMoveSystem(EntityManager* entity_manager, SystemManager* system_manager, Controls* controls);
};

#endif  // INCLUDE_HIKE_SYSTEMS_MENU_MOVE_SYSTEM_H_
