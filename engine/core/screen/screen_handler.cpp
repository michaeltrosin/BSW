//
// Created by Michael on 11.02.2021.
//

#include "screen_handler.h"

#include <core/event/event.h>

bsw::ScreenHandler::ScreenHandler() { m_screen_stack = create_scoped<ScreenStack>(); }

void bsw::ScreenHandler::switch_screen(const std::string &name) {
    if (m_current_screen) m_current_screen->on_close();
    m_current_screen = (*m_screen_stack)[name];
    ASSERT(m_current_screen, "Screen is null!");

    m_current_screen->on_show();
}

void bsw::ScreenHandler::switch_screen(int index) {
    if (m_current_screen) m_current_screen->on_close();
    m_current_screen = (*m_screen_stack)[index];
    ASSERT(m_current_screen, "Screen is null!");

    m_current_screen->on_show();
}

void bsw::ScreenHandler::on_render() {
    if (m_current_screen) m_current_screen->on_render();
}

void bsw::ScreenHandler::on_im_gui_render() {
    if (m_current_screen) m_current_screen->on_im_gui_render();
}

void bsw::ScreenHandler::on_update(float delta_time) {
    if (m_current_screen) m_current_screen->on_update(delta_time);
}

void bsw::ScreenHandler::on_event(Event &event) {
    if (m_current_screen) m_current_screen->on_event(event);
}