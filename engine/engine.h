//
// Created by Michael on 10.02.2021.
//
#pragma once

#include <bsw.h>
#include <core/event/event.h>
#include <core/event/event_handler.h>
#include <core/event/events.h>
#include <core/imgui/imgui_handler.h>
#include <core/screen/screen_handler.h>
#include <core/window/window.h>

namespace bsw {
class Engine {
public:
    Engine() = default;
    virtual ~Engine();

    static Engine &get() { return *m_instance; }
    static Engine &create(const WindowProps &props);
    int run();

    uint32_t get_window_width();
    uint32_t get_window_height();

    float get_runtime() const;

    Single<ScreenHandler> &get_screen_handler() { return m_screen_handler; }

    const Single<bsw::Window> &get_window_handle() const;

private:
    static Single<Engine> m_instance;

    void on_event(Event &event);
    void initialize();

private:
    float m_fps_limit = 60.0f;

    Single<ScreenHandler> m_screen_handler;
    Single<Window> m_main_window;
};
}// namespace bsw
