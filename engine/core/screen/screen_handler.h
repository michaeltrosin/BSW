//
// Created by Michael on 11.02.2021.
//

#pragma once

#include <bsw.h>
#include <core/screen/screen.h>
#include <core/screen/screen_stack.h>

#include <vector>

namespace bsw {
class Event;

class ScreenHandler {
public:
    ScreenHandler();

    template<typename T>
    void add_screen(const std::string &name) {
        auto type = create_ref<T>();
        Ref<Screen> screen = std::dynamic_pointer_cast<Screen>(type);

        if (!screen) { ASSERT_NOT_REACHED_NO_MSG(); }
        m_screen_stack->push(name, screen);
    }

    void switch_screen(const std::string &name);

    void on_render();
    void on_im_gui_render();
    void on_update(float delta_time);

    void on_event(Event &event);

private:
    void switch_screen(int index);

    Ref<Screen> m_current_screen{nullptr};
    Single<ScreenStack> m_screen_stack;
};
}// namespace bsw
