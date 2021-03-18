#include "hike/systems/result_system.h"

#include <BearLibTerminal.h>

#include <map>
#include <string>
#include <utility>

#include "hike/components/coin_count_component.h"
#include "hike/components/step_count_component.h"
#include "lib/ecs/entity_manager.h"

void ResultSystem::OnUpdate() {
  std::ifstream file(path_);
  std::map<std::string, int> results;
  int center = terminal_state(TK_WIDTH)/2 - terminal_state(TK_WIDTH)/5;
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
  terminal_printf(center, 2, "coin:");
  terminal_printf(center, 3, "steps:");
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "%i", results["coins"]);
  terminal_printf(center + 7, 2, buffer);
  snprintf(buffer, sizeof(buffer), "%i", results["steps"]);
  terminal_printf(center + 7, 3, buffer);
}
void ResultSystem::OnPreUpdate() {
}
void ResultSystem::OnPostUpdate() {
}
ResultSystem::ResultSystem(EntityManager* const entity_manager, SystemManager* const system_manager, std::string path)
    : ISystem(entity_manager, system_manager), path_(path) {}
