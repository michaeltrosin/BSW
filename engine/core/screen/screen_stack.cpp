//
// Created by Michael on 12.02.2021.
//

#include "screen_stack.h"

#include <core/screen/screen.h>

namespace bsw {

void ScreenStack::Push(const std::string &name, const Ref<Screen> &screen) {
  screens_.emplace_back(name, screen);
}

void ScreenStack::Pop(const std::string &name) {
  int index = IndexOf(name);
  if (index < 0)
    return;

  screens_.erase(screens_.begin() + IndexOf(name));
}

Ref<Screen> ScreenStack::operator[](const std::string &name) {
  for (auto &a : screens_) {
    if (a.first == name) {
      return a.second;
    }
  }
  return nullptr;
}

int ScreenStack::IndexOf(const std::string &name) {
  for (int i = 0; i < screens_.size(); i++) {
    if (screens_[i].first == name)
      return i;
  }
  return -1;
}

Ref<Screen> ScreenStack::operator[](int index) {
  if (screens_.empty())
    return nullptr;
  if (index < 0)
    return nullptr;
  if (index > screens_.size())
    return nullptr;
  return screens_.at(index).second;
}
} // namespace bsw