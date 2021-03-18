#ifndef INCLUDE_LIB_SCENES_I_SCENE_H_
#define INCLUDE_LIB_SCENES_I_SCENE_H_

#include "lib/scenes/context.h"

class IScene {
 protected:
  Context* const ctx_;

 public:
  int current_level;

  explicit IScene(Context* const ctx) : ctx_(ctx) {}

  virtual ~IScene() = default;

  virtual void OnCreate() = 0;

  virtual void OnRender() = 0;

  virtual void OnExit() = 0;
};

#endif  // INCLUDE_LIB_SCENES_I_SCENE_H_
