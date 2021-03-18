#include <BearLibTerminal.h>
#include <hike/controls.h>
#include <hike/scenes/game_scene.h>
#include <hike/scenes/menu_scene.h>
#include <hike/scenes/result_scene.h>

#include "lib/scenes/scene_manager.h"

int main() {
  terminal_open();
  terminal_color("#abb3bd");
  terminal_set("window: size=48x24, cellsize=32x32, resizeable=true");
  terminal_set("font: resource/fonts/AlbionicTitulInfl_Bold.ttf, size=25");
  terminal_set("0x1000: resource/tiles/fantasy-tileset.png,  size=32x32, align=center");
  terminal_refresh();
  Controls controls;
  Context ctx{};
  SceneManager sm(ctx);
  sm.Put("menu", new MenuScene(&ctx, &controls));
  sm.Put("level", new GameScene(&ctx, &controls, "resource/maps/", "resource/results/result.txt"));
  sm.Put("result", new ResultScene(&ctx, &controls, "resource/results/result.txt"));
  ctx.scene_ = "menu";

  while (true) {
    if (controls.IsPressed(TK_CLOSE)) {
      break;
    }
    controls.Reset();
    sm.OnRender();
    // controls.OnUpdate();
  }
  sm.OnExit();
  terminal_close();
}
