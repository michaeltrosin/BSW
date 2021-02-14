//
// Created by Michael on 12.02.2021.
//

#pragma once

#include <string>
#include <vector>

#include <bsw.h>

namespace bsw {
class Screen;

class ScreenStack {
public:
  void Push(const std::string &name, const Ref<Screen> &screen);
  void Pop(const std::string &name);

  Ref<Screen> operator[](const std::string &name);
  Ref<Screen> operator[](int index);

private:
  int IndexOf(const std::string &name);

  std::vector<std::pair<std::string, Ref<Screen>>> screens_;
};
} // namespace bsw
