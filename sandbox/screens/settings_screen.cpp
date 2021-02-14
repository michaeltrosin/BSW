//
// Created by Michael on 14.02.2021.
//

#include "settings_screen.h"
#include <core/render/renderer2d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace bsw;

extern glm::mat4 projection;

void SettingsScreen::OnRender() {
  Renderer2D::ResetStats();

  glm::mat4 cam_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  Renderer2D::Begin(projection * cam_view);
  Renderer2D::DrawQuad({100, 100}, {200.0f, 200.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
  Renderer2D::End();

}

void SettingsScreen::OnImGuiRender() {
}