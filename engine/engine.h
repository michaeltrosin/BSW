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

    /**
     * Gets the Instance
     * @return
     */
    static Engine &get() { return *m_instance; }

    /**
     * Creates a new Engine instance
     * @param props
     * @param argv
     * @return
     */
    static Engine &create(const WindowProps &props, const char **argv);

    /**
     * Starts the main loop and returns the exit code
     * @return
     */
    int run();

    /**
     * Gets the window width
     * @return
     */
    uint32_t get_window_width();

    /**
     * Gets the window height
     * @return
     */
    uint32_t get_window_height();

    /**
     * Gets the time since start of engine
     * @return
     */
    float get_runtime() const;

    /**
     * Gets the screenhandler instance
     * @return
     */
    Single<ScreenHandler> &get_screen_handler() { return m_screen_handler; }

    /**
     * Gets the window handle
     * @return
     */
    const Single<bsw::Window> &get_window_handle() const;

private:
    static Single<Engine> m_instance;

    /**
     * Will be called on every event
     * @param event
     */
    void on_event(Event &event);

    /**
     * Initializes the engine
     */
    void initialize();

private:
    float m_fps_limit = 60.0f;

    Single<ScreenHandler> m_screen_handler;
    Single<Window> m_main_window;
};
}// namespace bsw
