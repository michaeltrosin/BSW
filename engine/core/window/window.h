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

    void initialize();
    void enable() const;
    void shutdown() const;

    uint32_t get_width() const;
    uint32_t get_height() const;

    Single<ImGuiHandler> &gui_handler() { return m_im_gui_handler; }

    void swap_buffers() const;
    bool should_close() const { return glfwWindowShouldClose(m_window); }
    void *get_native_window() const { return (void *) m_window; }

    void set_v_sync(bool enabled);
    bool is_v_sync() const;

    void set_event_callback(const CallbackFunction &callback_function);

    bool is_mouse_button_pressed(MouseCode button);
    bool is_key_pressed(KeyCode key);
    glm::vec2 get_mouse_position();

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