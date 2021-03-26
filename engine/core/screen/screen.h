//
// Created by Michael on 11.02.2021.
//

#pragma once

#include <core/event/event.h>
#include <core/event/event_handler.h>
#include <core/input/input.h>
#include <imgui/imgui.h>

namespace bsw {
class Engine;

class Screen {
public:
    /**
     * Will be called when the screen shows
     */
    virtual void on_show() {}

    /**
     * Will be called on every render
     */
    virtual void on_render() {}

    /**
     * Will be called on every update
     * @param delta_time
     */
    virtual void on_update(float delta_time) {}

    /**
     * Will be called on every IMGUI render call
     *
     * Use this for IMGUI drawing!!
     */
    virtual void on_im_gui_render() {}

    /**
     * Will be called if the screen closes
     */
    virtual void on_close() {}

    /**
     * Will be called if the engine receives an event
     * @param event
     */
    virtual void on_event(Event &event) {}

protected:
    /**
     * Gets the Window width
     * @return
     */
    uint32_t window_width();

    /**
     * Gets the Window height
     * @return
     */
    uint32_t window_height();

    bool key_pressed(bsw::KeyCode key_code);
    bool mouse_pressed(bsw::MouseCode mouse_code);
};

}// namespace bsw