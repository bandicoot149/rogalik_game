#ifndef INCLUDE_HIKE_SYSTEMS_MOVE_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_MOVE_SYSTEM_H_
#include <hike/controls.h>
#include <lib/ecs/system.h>

#include <map>
#include <utility>

class Entity;

class MoveSystem : public ISystem {
  Controls* controls_;
  std::map<int, std::pair<int, int>> buttons_;
  void OnUpdateEntity(Entity* entity) const;
  int offset_;  // отклонение от центральной точки, на которое не реагирует камера
 protected:
  void OnUpdate() override;

 public:
  MoveSystem(EntityManager* entity_manager, SystemManager* system_manager, Controls* controls, int offset);
};

#endif  // INCLUDE_HIKE_SYSTEMS_MOVE_SYSTEM_H_
