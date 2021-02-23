//
// Created by Michael on 17.02.2021.
//

#include "screen.h"

#include <engine.h>

uint32_t bsw::Screen::window_width() { return Engine::get().get_window_width(); }
uint32_t bsw::Screen::window_height() { return Engine::get().get_window_height(); }
