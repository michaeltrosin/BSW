//
// Created by Michael on 11.02.2021.
//

#pragma once

#include <vector>

#include <bsw.h>
#include <core/screen/screen.h>
#include <core/screen/screen_stack.h>

namespace bsw {
class Event;

class ScreenHandler {
public:
  ScreenHandler();

  template <typename T> void AddScreen(const std::string &name) {
    auto type = CreateRef<T>();
    Ref<Screen> screen = std::dynamic_pointer_cast<Screen>(type);

    if (!screen) {
      ASSERT_NOT_REACHED_NO_MSG();
    }

    screen->ScreenChangeRequested += [this](ScreenChangeEvent &event) {
      SwitchScreen(event.GetScreenName());
    };
    screen_stack_->Push(name, screen);
  }

  void SwitchScreen(const std::string &name);

  void OnRender();
  void OnImGuiRender();
  void OnUpdate(float delta_time);

  void OnEvent(Event &event);

private:
  void SwitchScreen(int index);

  Ref<Screen> current_screen_{nullptr};
  Single<ScreenStack> screen_stack_;
};
} // namespace bsw
