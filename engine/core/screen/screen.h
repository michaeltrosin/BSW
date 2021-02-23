//
// Created by Michael on 11.02.2021.
//

#pragma once

#include <core/event/event.h>
#include <core/event/event_handler.h>
#include <imgui/imgui.h>

namespace bsw {
class Engine;

class Screen {
public:
    virtual void on_show() {}
    virtual void on_render() {}
    virtual void on_update(float delta_time) {}
    virtual void on_im_gui_render() {}
    virtual void on_close() {}

    virtual void on_event(Event &event) {}

protected:
    uint32_t window_width();
    uint32_t window_height();
};

}// namespace bsw