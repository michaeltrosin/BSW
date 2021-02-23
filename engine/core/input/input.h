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
    static bool is_key_pressed(KeyCode key);

    static bool is_mouse_button_pressed(MouseCode button);
    static glm::vec2 get_mouse_position();
    static float get_mouse_x();
    static float get_mouse_y();
};
}// namespace bsw