//
// Created by Michael on 12.02.2021.
//

#pragma once

#include <bsw.h>

#define MAKE_EVENT_CALLBACK(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define EVENT_TYPE(type)                                                                                                                             \
    static EventType get_static_type() { return EventType::type; }                                                                                   \
    virtual EventType get_type() const override { return get_static_type(); }                                                                        \
    virtual const char *get_name() const override { return #type; }
#define EVENT_CATEGORY(category)                                                                                                                     \
    virtual EventCategory get_category_flags() const override { return category; }

namespace bsw {
enum class EventCategory : unsigned short {
    NONE = 0,
    INTERNAL = BIT(0),
    INPUT = BIT(1),
    KEYBOARD = BIT(2),
    MOUSE = BIT(3),
    MOUSE_BUTTON = BIT(4),
};

BITFIELD(EventCategory)

enum class EventType {
    NONE = 0,

    WINDOW_CLOSED,
    WINDOW_RESIZED,
    WINDOW_FOCUSED,
    WINDOW_LOST_FOCUS,
    WINDOW_MOVED,

    KEY_PRESSED,
    KEY_RELEASED,
    KEY_TYPED,

    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_MOVED,
    MOUSE_SCROLLED,
};

class Event {
public:
    bool handled = false;

    virtual EventType get_type() const = 0;
    virtual const char *get_name() const = 0;
    virtual EventCategory get_category_flags() const = 0;

    template<typename T>
    bool is() {
        return typeid(T) == typeid(*this);
    }

    bool operator==(const EventCategory &rhs) const { return is_in_category(rhs); }

    bool is_in_category(const EventCategory &category) const { return get_category_flags() & category; }
};
}// namespace bsw