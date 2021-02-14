//
// Created by Michael on 11.02.2021.
//

#pragma once

#include <imgui/imgui_impl_glfw.h>

#include <bsw.h>

namespace bsw {

class ImGuiHandler {
public:
  explicit ImGuiHandler(GLFWwindow *window);

  void InitializeImGui(char *glsl_version);
  void Begin();
  void End();
  void Shutdown();

private:
  GLFWwindow *window_;
};
} // namespace bsw