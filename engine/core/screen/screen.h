//
// Created by Michael on 11.02.2021.
//

#pragma once

#include <imgui/imgui.h>

#include <core/event/event.h>
#include <core/event/event_handler.h>
#include <core/event/screen_events.h>

namespace bsw {
class Screen {
public:
  EventHandler<ScreenChangeEvent> ScreenChangeRequested;

  virtual void OnShow() {}
  virtual void OnRender() {}
  virtual void OnUpdate(float delta_time) {}
  virtual void OnImGuiRender() {}
  virtual void OnClose() {}

  virtual void OnEvent(Event &event) {}
};

} // namespace bsw