//
// Created by Michael on 11.02.2021.
//
// clang-format off
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
// clang-format on

#include "imgui_handler.h"

bsw::ImGuiHandler::ImGuiHandler(GLFWwindow *window) : m_window(window) {}

void bsw::ImGuiHandler::initialize_im_gui(char *glsl_version) {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void bsw::ImGuiHandler::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void bsw::ImGuiHandler::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void bsw::ImGuiHandler::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}