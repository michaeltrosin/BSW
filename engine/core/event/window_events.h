//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>

namespace bsw {

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(uint32_t width, uint32_t height)
      : width_(width), height_(height) {}

  uint32_t GetWidth() const { return width_; }
  uint32_t GetHeight() const { return height_; }

  EVENT_TYPE(WINDOW_RESIZED)
  EVENT_CATEGORY(EventCategory::INTERNAL)
private:
  uint32_t width_, height_;
};

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent() = default;

  EVENT_TYPE(WINDOW_CLOSED)
  EVENT_CATEGORY(EventCategory::INTERNAL);
};

} // namespace bsw