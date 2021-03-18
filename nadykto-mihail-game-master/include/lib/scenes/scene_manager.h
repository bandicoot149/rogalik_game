#ifndef INCLUDE_LIB_SCENES_SCENE_MANAGER_H_
#define INCLUDE_LIB_SCENES_SCENE_MANAGER_H_

#include <map>
#include <memory>
#include <string>

#include "lib/scenes/context.h"
#include "lib/scenes/i_scene.h"

class SceneManager {
  std::map<std::string, std::unique_ptr<IScene>> scenes_;
  const Context& ctx_;
  std::string current_scene_ = "";

 public:
  explicit SceneManager(const Context& ctx);
  void OnRender();
  void OnExit() const;
  void Put(const std::string& name, IScene* scene);
};

#endif  // INCLUDE_LIB_SCENES_SCENE_MANAGER_H_
