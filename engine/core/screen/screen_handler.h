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

    /**
     * Adds a Screen to the stack
     *
     * T will be the Screen type
     * @tparam T
     * @param name
     */
    template<typename T>
    void add_screen(const std::string &name) {
        auto type = create_ref<T>();
        Ref<Screen> screen = std::dynamic_pointer_cast<Screen>(type);

        if (!screen) { ASSERT_NOT_REACHED_NO_MSG(); }
        m_screen_stack->push(name, screen);
    }

    /**
     * Changes the current Screen to the one defined by the name
     * @param name
     */
    void switch_screen(const std::string &name);

    /**
     * Will be called on every render call
     */
    void on_render();

    /**
     * Will be called on IMGUI render call
     */
    void on_im_gui_render();

    /**
     * Will be called on every update call
     * @param delta_time
     */
    void on_update(float delta_time);

    /**
     * Will be called on a received event
     * @param event
     */
    void on_event(Event &event);

private:
    /**
     * Switches the Screen to the one given by the index
     * @param index
     */
    void switch_screen(int index);

    Ref<Screen> m_current_screen{nullptr};
    Single<ScreenStack> m_screen_stack;
};
}// namespace bsw
