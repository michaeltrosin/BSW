//
// Created by Michael on 09.02.2021.
//
#pragma once
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <core/imgui/imgui_handler.h>

#include <cstdint>
#include <functional>
#include <utility>
#include <core/input/key_codes.h>
#include <core/input/mouse_codes.h>

#include <glm/glm.hpp>

namespace bsw {
using namespace key;
using namespace mouse;

class Event;

struct WindowProps {
    std::string title;
    uint32_t width;
    uint32_t height;

    explicit WindowProps(std::string title, int width = 1280, int height = 720) : title(std::move(title)), width(width), height(height) {}
};

class Window {
public:
    using CallbackFunction = std::function<void(Event &)>;

    explicit Window(const WindowProps &window_props);
    ~Window() = default;

    /**
     * Initializes the window
     */
    void initialize();

    /**
     * Enables the window
     */
    void enable() const;

    /**
     * Destroys the window
     */
    void shutdown() const;

    /**
     * Gets the window width
     * @return
     */
    uint32_t get_width() const;

    /**
     * Gets the window height
     * @return
     */
    uint32_t get_height() const;

    /**
     * Gets the ImGuiHandler instance
     * @return
     */
    Single<ImGuiHandler> &gui_handler() { return m_im_gui_handler; }

    /**
     * Swaps the current frame buffers
     */
    void swap_buffers() const;

    /**
     * Returns true if the window should close
     * @return
     */
    bool should_close() const { return glfwWindowShouldClose(m_window); }

    /**
     * Gets a pointer to the native window
     * @return
     */
    void *get_native_window() const { return (void *) m_window; }

    /**
     * Enables/Disables the window vsync
     * @param enabled
     */
    void set_v_sync(bool enabled);

    /**
     * Returns true if vsync is enabled
     * @return
     */
    bool is_v_sync() const;

    /**
     * Sets the event callback function
     * @param callback_function
     */
    void set_event_callback(const CallbackFunction &callback_function);

    /**
     * Returns true if MouseCode is pressed
     * @param button
     * @return
     */
    bool is_mouse_button_pressed(MouseCode button);

    /**
     * Returns true if KeyCode is pressed
     * @param key
     * @return
     */
    bool is_key_pressed(KeyCode key);

    /**
     * Gets the mouse position
     * @return
     */
    glm::vec2 get_mouse_position();

    /**
     * Sets the window title
     * @param title
     */
    void set_title(const std::string &title);

private:
    Single<ImGuiHandler> m_im_gui_handler;
    GLFWwindow *m_window;

    struct WindowData {
        std::string title;
        uint32_t width, height;
        bool vsync = true;

        CallbackFunction on_event;
    };

    WindowData m_window_data;
};
}// namespace bsw