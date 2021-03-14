//
// Created by Michael on 21.02.2021.
//

#pragma once

#include <bsw.h>
#include <core/input/key_codes.h>
#include <core/input/mouse_codes.h>
#include <glm/glm.hpp>

namespace bsw {
using namespace key;
using namespace mouse;

class Input {
public:
    /**
     * Returns true if a given KeyCode is pressed
     * @param key
     * @return
     */
    static bool is_key_pressed(KeyCode key);

    /**
     * Returns true if a given MouseButton is pressed
     * @param button
     * @return
     */
    static bool is_mouse_button_pressed(MouseCode button);

    /**
     * Gets the current Mouse position
     * @return
     */
    static glm::vec2 get_mouse_position();

    /**
     * Returns the mouse x position
     * @return
     */
    static float get_mouse_x();

    /**
     * Returns the mouse y position
     * @return
     */
    static float get_mouse_y();
};
}// namespace bsw