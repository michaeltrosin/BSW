//
// Created by Michael on 10.02.2021.
//

#define NO_DEBUG_DRAW

#include <core/assets/resource_manager.h>
#include <core/screen/screen.h>
#include <core/screen/screen_handler.h>
#include <engine.h>

#include "screens/test2d.h"
#include "snake/snake_screen.h"

using namespace bsw;

int main(int, const char **argv) {
    auto &engine = Engine::create(WindowProps{"Snake :)", 64 * 8, 64 * 8, false}, argv);

    engine.get_screen_handler()->add_screen<SnakeGame>("test2d");
    engine.get_screen_handler()->switch_screen("test2d");

    return engine.run();
}