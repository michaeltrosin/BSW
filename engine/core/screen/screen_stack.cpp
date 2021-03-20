//
// Created by Michael on 12.02.2021.
//

#include "screen_stack.h"

#include <core/screen/screen.h>

void bsw::ScreenStack::push(const std::string &name, const Ref<Screen> &screen) { m_screens.emplace_back(name, screen); }

void bsw::ScreenStack::pop(const std::string &name) {
    int index = index_of(name);
    if (index < 0) return;

    m_screens.erase(m_screens.begin() + index);
}

Ref<bsw::Screen> bsw::ScreenStack::operator[](const std::string &name) {
    for (auto &a : m_screens) {
        if (a.first == name) { return a.second; }
    }
    return nullptr;
}

int bsw::ScreenStack::index_of(const std::string &name) {
    for (int i = 0; i < m_screens.size(); i++) {
        if (m_screens[i].first == name) return i;
    }
    return -1;
}

Ref<bsw::Screen> bsw::ScreenStack::operator[](int index) {
    if (m_screens.empty()) return nullptr;
    if (index < 0) return nullptr;
    if (index > m_screens.size()) return nullptr;
    return m_screens.at(index).second;
}