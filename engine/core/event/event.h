//
// Created by Michael on 12.02.2021.
//

#pragma once

#include <bsw.h>

#define MAKE_EVENT_CALLBACK(fn)                                                \
  [this](auto &&...args) -> decltype(auto) {                                   \
    return this->fn(std::forward<decltype(args)>(args)...);                    \
  }
#define EVENT_TYPE(type)                                                       \
  static EventType GetStaticType() { return EventType::type; }                 \
  virtual EventType GetType() const override { return GetStaticType(); }       \
  virtual const char *GetName() const override { return #type; }
#define EVENT_CATEGORY(category)                                               \
  virtual EventCategory GetCategoryFlags() const override { return category; }

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

  SCREEN_CHANGE_REQUESTED,
};

class Event {
public:
  bool Handled = false;

  virtual EventType GetType() const = 0;
  virtual const char *GetName() const = 0;
  virtual EventCategory GetCategoryFlags() const = 0;

  template <typename T> bool Is() { return typeid(T) == typeid(*this); }

  bool operator==(const EventCategory &rhs) const { return IsInCategory(rhs); }

  bool IsInCategory(const EventCategory &category) const {
    return GetCategoryFlags() & category;
  }
};
} // namespace bsw