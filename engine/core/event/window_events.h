//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>

namespace bsw {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}

    uint32_t get_width() const { return m_width; }
    uint32_t get_height() const { return m_height; }

    EVENT_TYPE(WINDOW_RESIZED)
    EVENT_CATEGORY(EventCategory::INTERNAL)
private:
    uint32_t m_width, m_height;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_TYPE(WINDOW_CLOSED)
    EVENT_CATEGORY(EventCategory::INTERNAL);
};

}// namespace bsw