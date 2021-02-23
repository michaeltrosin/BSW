//
// Created by Michael on 12.02.2021.
//

#pragma once

#include <bsw.h>

#include <string>
#include <vector>

namespace bsw {
class Screen;

class ScreenStack {
public:
    void push(const std::string &name, const Ref<Screen> &screen);
    void pop(const std::string &name);

    Ref<Screen> operator[](const std::string &name);
    Ref<Screen> operator[](int index);

private:
    int index_of(const std::string &name);

    std::vector<std::pair<std::string, Ref<Screen>>> m_screens;
};
}// namespace bsw
