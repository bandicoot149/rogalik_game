#ifndef INCLUDE_HIKE_LAYER_H_
#define INCLUDE_HIKE_LAYER_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

class Layer {
 public:
  std::map<std::pair<int, int>, char> facility_;
  std::map<std::pair<int, int>, char> GetFacility() {
    return facility_;
  }
  void AddFacility(std::pair<int, int> coordinates, char symbol) {
    facility_.insert(std::make_pair(coordinates, symbol));
  }
};
#endif  // INCLUDE_HIKE_LAYER_H_
