//
// Created by Michael on 10.02.2021.
//
#pragma once

#include <bsw.h>
#include <core/event/event.h>
#include <core/event/event_handler.h>
#include <core/event/events.h>

#include <core/imgui/imgui_handler.h>
#include <core/screen/screen_handler.h>
#include <core/window/window.h>

namespace bsw {
class Engine {
public:
  Engine() = default;
  virtual ~Engine();

  static Engine &Create(const WindowProps &props);
  int Run();

  static Engine &Get() { return *k_instance_; }
  void ChangeTitle(const std::string& title);

  float GetTime() const;

  Single<ScreenHandler> &GetScreenHandler() { return screen_handler_; }
private:
  static Single<Engine> k_instance_;

  void OnEvent(Event &event);
  void Initialize();
private:
  float fps_limit_ = 60.0f;

  Single<ScreenHandler> screen_handler_;
  Single<Window> main_window_;
};
} // namespace bsw
