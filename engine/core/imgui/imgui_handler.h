//
// Created by Michael on 11.02.2021.
//

#pragma once

#include <bsw.h>
#include <imgui/imgui_impl_glfw.h>

namespace bsw {

class ImGuiHandler {
public:
    explicit ImGuiHandler(GLFWwindow *window);

    void initialize_im_gui(char *glsl_version);
    void begin();
    void end();
    void shutdown();

private:
    GLFWwindow *m_window;
};
}// namespace bsw