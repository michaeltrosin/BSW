//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <core/event/event.h>

#include <utility>

namespace bsw {

class ScreenChangeEvent : public Event {
public:
  explicit ScreenChangeEvent(std::string name) : name_(std::move(name)) {}

  const std::string &GetScreenName() const { return name_; }

  EVENT_TYPE(SCREEN_CHANGE_REQUESTED)
  EVENT_CATEGORY(EventCategory::INTERNAL)
private:
  std::string name_;
};

} // namespace bsw