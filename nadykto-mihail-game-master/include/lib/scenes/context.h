#ifndef INCLUDE_LIB_SCENES_CONTEXT_H_
#define INCLUDE_LIB_SCENES_CONTEXT_H_

#include <string>

class Context {
 public:
  std::string scene_ = "";
  int level_number;
  bool graphic;
  bool is_first_;
};

#endif  // INCLUDE_LIB_SCENES_CONTEXT_H_
