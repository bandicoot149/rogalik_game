#ifndef INCLUDE_HIKE_SYSTEMS_INTERFACE_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_INTERFACE_SYSTEM_H_

#include <lib/ecs/system.h>
#include <lib/scenes/context.h>

class InterfaceSystem : public ISystem {
  int level_number_;
  bool graphics_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  InterfaceSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* ctx);
};

#endif  // INCLUDE_HIKE_SYSTEMS_INTERFACE_SYSTEM_H_
