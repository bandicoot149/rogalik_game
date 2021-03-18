#ifndef INCLUDE_LIB_MAP_GENERATOR_MAP_GENERATOR_H_
#define INCLUDE_LIB_MAP_GENERATOR_MAP_GENERATOR_H_

#include <string>
#include <utility>
#include <vector>

#include "lib/map_generator/space.h"
class MapGenerator {
 public:
  static void Generate(std::string map_dir, int number, int width, int height, int number_iterations,
                       bool horizontally);
  static std::vector<Space*> Divide(std::vector<Space*> spaces);
  static std::vector<Space*> DoBorder(std::vector<Space*> spaces);
  static std::pair<std::pair<int, int>, std::pair<int, int>> CreateLane(Space* space);
  static std::pair<std::pair<int, int>, std::pair<int, int>> CreateEnterExit(std::vector<Space*> spaces);
  static std::vector<std::pair<int, int>> CreateCoins(std::vector<Space*> spaces, int frequency);
  static std::vector<std::pair<int, int>> CreateEnemies(std::vector<Space*> spaces, int frequency);
};

#endif  // INCLUDE_LIB_MAP_GENERATOR_MAP_GENERATOR_H_
