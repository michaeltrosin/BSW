//
// Created by Michael on 10.02.2021.
//
#include <core/font/font_manager.h>
#include <core/screen/screen.h>
#include <core/screen/screen_handler.h>
#include <engine.h>

#include <utils/file.h>

#include "screens/test2d.h"

using namespace bsw;

int main() {
    auto &engine = Engine::create(WindowProps{"bsw"});

    engine.get_screen_handler()->add_screen<Test2D>("test2d");
    engine.get_screen_handler()->switch_screen("test2d");

    FontManager::add_font("Title", R"(F:\BSW\resources\fonts\Roboto-Light.ttf)",
                          58);

    return engine.run();
}