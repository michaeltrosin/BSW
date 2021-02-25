//
// Created by Michael on 11.02.2021.
//

#include "window.h"

#include <core/event/event.h>
#include <core/event/events.h>

bsw::Window::Window(const WindowProps &window_props) {
    if (!glfwInit()) { ASSERT_NOT_REACHED_NO_MSG(); }

    m_window_data.title = window_props.title;
    m_window_data.width = window_props.width;
    m_window_data.height = window_props.height;

    //  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    //  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //    glfwWindowHint(GLFW_SAMPLES, 4);
    m_window = glfwCreateWindow((int) window_props.width, (int) window_props.height, window_props.title.c_str(), nullptr, nullptr);
    if (!m_window) {
        shutdown();
        ASSERT_NOT_REACHED_NO_MSG();
    }

    glfwSetWindowUserPointer(m_window, &m_window_data);
    set_v_sync(true);

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.on_event(event);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        data.on_event(event);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, mods);
                data.on_event(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key, mods);
                data.on_event(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, mods, 1);
                data.on_event(event);
                break;
            }
            default: break;
        }
    });

    glfwSetCharCallback(m_window, [](GLFWwindow *window, uint32_t keycode) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        data.on_event(event);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        double px;
        double py;
        glfwGetCursorPos(window, &px, &py);

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button, (float) px, (float) py);
                data.on_event(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button, (float) px, (float) py);
                data.on_event(event);
                break;
            }
            default: break;
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow *window, double x_offset, double y_offset) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float) x_offset, (float) y_offset);
        data.on_event(event);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double x_pos, double y_pos) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float) x_pos, (float) y_pos);
        data.on_event(event);
    });

    enable();
}

void bsw::Window::initialize() {
    m_im_gui_handler = create_single<ImGuiHandler>(m_window);
    m_im_gui_handler->initialize_im_gui((char *) glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    std::cout << "OpenGL Info:" << std::endl;
    std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;
}

void bsw::Window::enable() const { glfwMakeContextCurrent(m_window); }

void bsw::Window::shutdown() const {
    m_im_gui_handler->shutdown();

    glfwTerminate();
}

uint32_t bsw::Window::get_width() const {
    int width;
    glfwGetWindowSize(m_window, &width, nullptr);
    return width;
}

uint32_t bsw::Window::get_height() const {
    int height;
    glfwGetWindowSize(m_window, nullptr, &height);
    return height;
}

void bsw::Window::swap_buffers() const {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void bsw::Window::set_v_sync(bool enabled) {
    glfwSwapInterval((int) enabled);
    m_window_data.vsync = enabled;
}

bool bsw::Window::is_v_sync() const { return m_window_data.vsync; }

void bsw::Window::set_event_callback(const Window::CallbackFunction &callback_function) { m_window_data.on_event = callback_function; }

glm::vec2 bsw::Window::get_mouse_position() {
    double px;
    double py;
    glfwGetCursorPos(m_window, &px, &py);

    return {(float) px, (float) py};
}

bool bsw::Window::is_mouse_button_pressed(bsw::MouseCode button) { return glfwGetMouseButton(m_window, button); }

bool bsw::Window::is_key_pressed(bsw::KeyCode key) { return glfwGetKey(m_window, key); }

void bsw::Window::set_title(const std::string &title) { glfwSetWindowTitle(m_window, title.c_str()); }