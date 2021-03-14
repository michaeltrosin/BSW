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

    /**
     * Initializes the im gui handler with a given version
     * @param glsl_version
     */
    void initialize_im_gui(char *glsl_version);

    /**
     * Begins the IMGUI drawing
     */
    void begin();

    /**
     * Ends the IMGUI drawing
     */
    void end();

    /**
     * Resets all created IMGUI functions and definitions
     */
    void shutdown();

private:
    GLFWwindow *m_window;
};
}// namespace bsw