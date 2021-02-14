//
// Created by Michael on 11.02.2021.
//

#include <core/event/event.h>
#include <core/event/events.h>

#include "window.h"

namespace bsw {

Window::Window(const WindowProps &window_props) {
  if (!glfwInit()) {
    ASSERT_NOT_REACHED_NO_MSG();
  }

  window_data_.title = window_props.title;
  window_data_.width = window_props.width;
  window_data_.height = window_props.height;

  //  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  //  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  //  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window_ = glfwCreateWindow((int)window_props.width, (int)window_props.height,
                             window_props.title.c_str(), nullptr, nullptr);
  if (!window_) {
    Shutdown();
    ASSERT_NOT_REACHED_NO_MSG();
  }

  glfwSetWindowUserPointer(window_, &window_data_);
  SetVSync(true);

  glfwSetWindowSizeCallback(
      window_, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.on_event(event);
      });

  glfwSetWindowCloseCallback(window_, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    WindowCloseEvent event;
    data.on_event(event);
  });

  glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode,
                                 int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

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
    default:
      break;
    }
  });

  glfwSetCharCallback(window_, [](GLFWwindow *window, unsigned int keycode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    KeyTypedEvent event(keycode);
    data.on_event(event);
  });

  glfwSetMouseButtonCallback(
      window_, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        double px;
        double py;
        glfwGetCursorPos(window, &px, &py);

        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(button, (float)px, (float)py);
          data.on_event(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(button, (float)px, (float)py);
          data.on_event(event);
          break;
        }
        default:
          break;
        }
      });

  glfwSetScrollCallback(
      window_, [](GLFWwindow *window, double x_offset, double y_offset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)x_offset, (float)y_offset);
        data.on_event(event);
      });

  glfwSetCursorPosCallback(
      window_, [](GLFWwindow *window, double x_pos, double y_pos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)x_pos, (float)y_pos);
        data.on_event(event);
      });

  Enable();
}

void Window::Initialize() {
  im_gui_handler_ = CreateSingle<ImGuiHandler>(window_);
  im_gui_handler_->InitializeImGui(
      (char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

  std::cout << "OpenGL Info:" << std::endl;
  std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;
}

void Window::Enable() const { glfwMakeContextCurrent(window_); }

void Window::Shutdown() const {
  im_gui_handler_->Shutdown();

  glfwTerminate();
}

unsigned int Window::GetWidth() const {
  int width;
  glfwGetWindowSize(window_, &width, nullptr);
  return width;
}

unsigned int Window::GetHeight() const {
  int height;
  glfwGetWindowSize(window_, nullptr, &height);
  return height;
}

void Window::SwapBuffers() const {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void Window::SetVSync(bool enabled) {
  glfwSwapInterval((int)enabled);
  window_data_.vsync = enabled;
}

bool Window::IsVSync() const { return window_data_.vsync; }

void Window::SetEventCallback(
    const Window::CallbackFunction &callback_function) {
  window_data_.on_event = callback_function;
}

void Window::GetCursorPos(float &pos_x, float &pos_y) {
  double px;
  double py;
  glfwGetCursorPos(window_, &px, &py);

  pos_x = (float)px;
  pos_y = (float)py;
}

void Window::SetTitle(const std::string &title) {
  glfwSetWindowTitle(window_, title.c_str());
}
} // namespace bsw