//
// Created by Michael on 14.02.2021.
//

#include "gl_render.h"

#include <glad/glad.h>

namespace bsw {
void GLRenderer::Init() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
}

void GLRenderer::SetViewport(uint32_t x, uint32_t y, uint32_t width,
                           uint32_t height) {
  glViewport(x, y, width, height);
}

void GLRenderer::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.r, color.g, color.b, color.a);
}
void GLRenderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void GLRenderer::DrawIndexed(const Ref<VertexArray> &vertex_array,
                           uint32_t index_count) {
  uint32_t count =
      index_count ? index_count : vertex_array->GetIndexBuffer()->GetCount();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);
}
} // namespace bsw