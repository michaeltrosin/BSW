//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <functional>
#include <vector>

#include <core/event/event.h>

namespace bsw {

template <typename T> class EventHandler {
  using CallbackFunction = std::function<void(T &)>;

public:
  EventHandler &operator+=(const CallbackFunction &callback_function) {
    attached_callbacks_.push_back(callback_function);
    return *this;
  }

  void operator()(T &event) {
    for (auto &cb : attached_callbacks_) {
      cb(event);
    }
  }

//  template <typename... Args> void operator()(Args &&...args) {
//    for (auto &cb : attached_callbacks_) {
//      cb(std::forward<Args>(args)...);
//    }
//  }

private:
  std::vector<CallbackFunction> attached_callbacks_;
};
} // namespace bsw