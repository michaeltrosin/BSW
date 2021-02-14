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

float camx = 0.0f;
float camy = 0.0f;

float endx = 0.0f;
float endy = 0.0f;
float stx = 0.0f;
float sty = 0.0f;
float curx = 0.0f;
float cury = 0.0f;

float mx = 0.0f;
float my = 0.0f;

void MainMenu::OnRender() {
  Renderer2D::ResetStats();

  glm::mat4 cam_view =
      glm::translate(glm::mat4(1.0f), glm::vec3(camx, camy, 0));

  Renderer2D::Begin(projection);
  Renderer2D::DrawQuad({curx, cury}, {50.0f, 50.0f}, {1.0f, 0.5f, 0.3f, 1.0f});
  Renderer2D::End();

  Renderer2D::Begin(projection * cam_view);
  Renderer2D::DrawQuad({0, 0}, {200.0f, 200.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
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

  ImGui::Begin("Test");
  ImGui::SliderFloat("Cam x", &camx, 0.0f, 500.0f);
  ImGui::SliderFloat("Cam y", &camy, 0.0f, 500.0f);

  if (ImGui::Button("Test")) {
    ScreenChangeEvent e("settings");
    ScreenChangeRequested(e);
  }
  ImGui::End();
}

float tsl;
float lerptime = 5;

bool l = false;

void MainMenu::OnEvent(Event &event) {
  if (event.Is<MouseMovedEvent>()) {
    auto e = dynamic_cast<MouseMovedEvent *>(&event);
    mx = e->GetX();
    my = (e->GetY() - 720) * -1;
  }
  if (event.Is<KeyPressedEvent>()) {
    auto e = dynamic_cast<KeyPressedEvent *>(&event);
    if (e->GetKeyCode() == keycodes::A) {
      camx--;
    }
    if (e->GetKeyCode() == keycodes::D) {
      camx++;
    }
    if (e->GetKeyCode() == keycodes::S) {
      camy--;
    }
    if (e->GetKeyCode() == keycodes::W) {
      camy++;
    }
  }
  if (event.Is<MouseButtonPressedEvent>()) {
    auto e = dynamic_cast<MouseButtonPressedEvent *>(&event);
    if (e->GetMouseButton() == mousecodes::BUTTONLEFT) {
      tsl = Engine::Get().GetTime();
      l = true;

      stx = curx;
      sty = cury;
      endx = e->GetMouseX();
      endy = (e->GetMouseY() - 720) * -1;
    }
  }
}

void Lerp() {
  float tss = Engine::Get().GetTime() - tsl;
  float pc = tss / lerptime;

  curx = (float)mathf::Lerp(stx, endx, pc);
  cury = (float)mathf::Lerp(sty, endy, pc);
}

void MainMenu::OnUpdate(float delta_time) {
  std::cout << "Time: " << Engine::Get().GetTime() << std::endl;
  if (l)
    Lerp();
}
