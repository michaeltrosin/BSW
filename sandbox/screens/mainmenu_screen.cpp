//
// Created by Michael on 12.02.2021.
//

#include "mainmenu_screen.h"

#include <core/render/renderer2d.h>
#include <engine.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <utils/math/easing.h>

using namespace bsw;

glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

float mx;
float my;

void MainMenu::OnRender() {
  Renderer2D::ResetStats();

  glm::mat4 cam_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  Renderer2D::Begin(projection);
  Renderer2D::DrawString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", {5, 500}, *Font::Default);
  //Renderer2D::DrawQuad({1280/2, 720/2}, {50.0f, 50.0f}, {0.4f, 0.5f, 0.3f, 0.5f});
  Renderer2D::End();

  Renderer2D::Begin(projection);
  Renderer2D::DrawQuad({mx, my}, {50.0f, 50.0f}, {1.0f, 0.5f, 0.3f, 1.0f});
  Renderer2D::End();
}

void MainMenu::OnImGuiRender() {
  ImGui::Begin("Debug");

  auto stats = Renderer2D::GetStats();
  ImGui::Text("Renderer2D Stats:");
  ImGui::Text("Draw Calls: %d", stats.draw_calls);
  ImGui::Text("Quads: %d", stats.quad_count);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

  // ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();

  ImGui::Begin("Testing", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  if (ImGui::Button("Goto Settings")) {
    ScreenChangeEvent e("settings");
    ScreenChangeRequested(e);
  }
  ImGui::End();
}

void MainMenu::OnEvent(Event &event) {
  if (event.Is<MouseMovedEvent>()) {
    auto *e = dynamic_cast<MouseMovedEvent *>(&event);
    mx = e->GetX();
    my = -(e->GetY() - 720);
  }
}

void MainMenu::OnUpdate(float delta_time) {}
