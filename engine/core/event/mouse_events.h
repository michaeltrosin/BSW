//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>
#include <core/input/mouse_codes.h>

namespace bsw {
using namespace mousecodes;

class MouseMovedEvent : public Event {
public:
  MouseMovedEvent(const float mouse_x, const float mouse_y)
      : mouse_x_(mouse_x), mouse_y_(mouse_y) {}

  float GetX() const { return mouse_x_; }
  float GetY() const { return mouse_y_; }

  EVENT_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT)
  EVENT_TYPE(MOUSE_MOVED)

private:
  float mouse_x_;
  float mouse_y_;
};

class MouseScrolledEvent : public Event {
public:
  MouseScrolledEvent(const float x_offset, const float y_offset)
      : x_offset_(x_offset), y_offset_(y_offset) {}

  float GetXOffset() const { return x_offset_; }
  float GetYOffset() const { return y_offset_; }

  EVENT_TYPE(MOUSE_SCROLLED)
  EVENT_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT)
private:
  float x_offset_, y_offset_;
};

class MouseButtonEvent : public Event {
public:
  MouseCode GetMouseButton() const { return button_; }

  float GetMouseX() const { return mouse_x_; }
  float GetMouseY() const { return mouse_y_; }

  EVENT_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT |
                 EventCategory::MOUSE_BUTTON)
protected:
  MouseButtonEvent(const MouseCode button, float mx, float my)
      : button_(button), mouse_x_(mx), mouse_y_(my) {}
  MouseCode button_;

private:
  float mouse_x_;
  float mouse_y_;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
  explicit MouseButtonPressedEvent(const MouseCode button, float mx, float my)
      : MouseButtonEvent(button, mx, my) {}

  EVENT_TYPE(MOUSE_BUTTON_PRESSED)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  explicit MouseButtonReleasedEvent(const MouseCode button, float mx, float my)
      : MouseButtonEvent(button, mx, my) {}

  EVENT_TYPE(MOUSE_BUTTON_RELEASED)
};

} // namespace bsw