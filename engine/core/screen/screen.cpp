//
// Created by Michael on 17.02.2021.
//

#include "screen.h"

#include <engine.h>

uint32_t bsw::Screen::window_width() { return Engine::get().get_window_width(); }
uint32_t bsw::Screen::window_height() { return Engine::get().get_window_height(); }

bool bsw::Screen::key_pressed(bsw::KeyCode key_code) { return Engine::get().get_window_handle()->is_key_pressed(key_code); }
bool bsw::Screen::mouse_pressed(bsw::MouseCode mouse_code) { return Engine::get().get_window_handle()->is_mouse_button_pressed(mouse_code); }