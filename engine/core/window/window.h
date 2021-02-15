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

namespace bsw {
class Event;

struct WindowProps {
  std::string title;
  unsigned int width;
  unsigned int height;

  explicit WindowProps(std::string title, int width = 1280, int height = 720)
      : title(std::move(title)), width(width), height(height) {}
};

class Window {
public:
  using CallbackFunction = std::function<void(Event &)>;

  explicit Window(const WindowProps &window_props);
  ~Window() = default;

  void Initialize();
  void Enable() const;
  void Shutdown() const;

  uint32_t GetWidth() const;
  uint32_t GetHeight() const;

  Single<ImGuiHandler> &GuiHandler() { return im_gui_handler_; }

  void SwapBuffers() const;
  bool ShouldClose() const { return glfwWindowShouldClose(window_); }
  void *GetNativeWindow() const { return (void *)window_; }

  void SetVSync(bool enabled);
  bool IsVSync() const;

  void SetEventCallback(const CallbackFunction &callback_function);

  void GetCursorPos(float &pox_x, float &pos_y);

  void SetTitle(const std::string& title);
private:
  Single<ImGuiHandler> im_gui_handler_;
  GLFWwindow *window_;

  struct WindowData {
    std::string title;
    unsigned int width, height;
    bool vsync = true;

    CallbackFunction on_event;
  };

  WindowData window_data_;
};
} // namespace bsw