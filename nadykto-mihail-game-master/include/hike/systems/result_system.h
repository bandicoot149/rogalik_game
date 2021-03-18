#ifndef INCLUDE_HIKE_SYSTEMS_RESULT_SYSTEM_H_
#define INCLUDE_HIKE_SYSTEMS_RESULT_SYSTEM_H_

#include <fstream>
#include <iostream>
#include <string>

#include "lib/ecs/system.h"

class ResultSystem : public ISystem {
 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;
  std::string path_;

 public:
  ResultSystem(EntityManager* entity_manager, SystemManager* system_manager, std::string path);
};

#endif  // INCLUDE_HIKE_SYSTEMS_RESULT_SYSTEM_H_
