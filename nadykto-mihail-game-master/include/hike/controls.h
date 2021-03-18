#ifndef INCLUDE_HIKE_CONTROLS_H_
#define INCLUDE_HIKE_CONTROLS_H_

#include <BearLibTerminal.h>

#include <list>
#include <map>

class Controls {
  std::list<int> is_pressed_button;
  std::map<int, bool> is_pressed_{};

 public:
  void Press(int btn_key) {
    is_pressed_[btn_key] = true;
  }
  bool IsPressed(int btn_key) const {
    if (is_pressed_.count(btn_key) == 0) {
      return false;
    }
    return is_pressed_.at(btn_key);
  }
  void Reset() {
    for (auto& btn : is_pressed_) {
      btn.second = false;
    }
    is_pressed_button.clear();
  }

  void OnUpdate() {
    // if (terminal_has_input()) {
      auto key = terminal_read();
      is_pressed_[key] = true;
      is_pressed_button.push_front(key);
    // }
  }
  int GetButton() const {
    return is_pressed_button.front();
  }
};

#endif  // INCLUDE_HIKE_CONTROLS_H_
