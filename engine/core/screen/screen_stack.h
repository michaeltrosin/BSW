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
    /**
     * Adds a screen to the back
     * @param name
     * @param screen
     */
    void push(const std::string &name, const Ref<Screen> &screen);

    /**
     * Removes the screen
     * @param name
     */
    void pop(const std::string &name);

    /**
     * Returns the screen from the name
     * @param name
     * @return
     */
    Ref<Screen> operator[](const std::string &name);

    /**
     * Returns the screen at an index
     * @param index
     * @return
     */
    Ref<Screen> operator[](int index);

private:
    /**
     * Gets the index of a given screen
     * @param name
     * @return
     */
    int index_of(const std::string &name);

    std::vector<std::pair<std::string, Ref<Screen>>> m_screens;
};
}// namespace bsw
