//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>
#include <core/input/mouse_codes.h>

namespace bsw {
using namespace mouse;

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const float mouse_x, const float mouse_y) : m_mouse_x(mouse_x), m_mouse_y(mouse_y) {}

    float get_x() const { return m_mouse_x; }
    float get_y() const { return m_mouse_y; }

    EVENT_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT)
    EVENT_TYPE(MOUSE_MOVED)

private:
    float m_mouse_x;
    float m_mouse_y;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const float x_offset, const float y_offset) : m_x_offset(x_offset), m_y_offset(y_offset) {}

    float get_x_offset() const { return m_x_offset; }
    float get_y_offset() const { return m_y_offset; }

    EVENT_TYPE(MOUSE_SCROLLED)
    EVENT_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT)
private:
    float m_x_offset, m_y_offset;
};

class MouseButtonEvent : public Event {
public:
    MouseCode get_mouse_button() const { return m_button; }

    float get_mouse_x() const { return m_mouse_x; }
    float get_mouse_y() const { return m_mouse_y; }

    EVENT_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT | EventCategory::MOUSE_BUTTON)

protected:
    MouseButtonEvent(const MouseCode button, float mx, float my) : m_button(button), m_mouse_x(mx), m_mouse_y(my) {}
    MouseCode m_button;

private:
    float m_mouse_x;
    float m_mouse_y;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(const MouseCode button, float mx, float my) : MouseButtonEvent(button, mx, my) {}

    EVENT_TYPE(MOUSE_BUTTON_PRESSED)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(const MouseCode button, float mx, float my) : MouseButtonEvent(button, mx, my) {}

    EVENT_TYPE(MOUSE_BUTTON_RELEASED)
};

}// namespace bsw