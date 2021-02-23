//
// Created by Michael on 21.02.2021.
//

#include "input.h"

#include <core/window/window.h>
#include <engine.h>

bool bsw::Input::is_key_pressed(KeyCode key) { return Engine::get().get_window_handle()->is_key_pressed(key); }
bool bsw::Input::is_mouse_button_pressed(MouseCode button) { return Engine::get().get_window_handle()->is_mouse_button_pressed(button); }
glm::vec2 bsw::Input::get_mouse_position() { return Engine::get().get_window_handle()->get_mouse_position(); }
float bsw::Input::get_mouse_x() { return get_mouse_position().x; }
float bsw::Input::get_mouse_y() { return get_mouse_position().y; }
