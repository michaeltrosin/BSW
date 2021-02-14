//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>

namespace bsw {

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(unsigned int width, unsigned int height)
      : width_(width), height_(height) {}

  unsigned int GetWidth() const { return width_; }
  unsigned int GetHeight() const { return height_; }

  EVENT_TYPE(WINDOW_RESIZED)
  EVENT_CATEGORY(EventCategory::INTERNAL)
private:
  unsigned int width_, height_;
};

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent() = default;

  EVENT_TYPE(WINDOW_CLOSED)
  EVENT_CATEGORY(EventCategory::INTERNAL);
};

} // namespace bsw