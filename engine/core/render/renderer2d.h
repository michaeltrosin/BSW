//
// Created by Michael on 12.02.2021.
//

#pragma once

#include <core/render/texture/texture2d.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace bsw {
// Batch rendering
class Renderer2D {
public:
  Renderer2D();
  ~Renderer2D();

  static void Init();
  static void Shutdown();

  static void Begin(const glm::mat4 &view_projection);
  static void End();
  static void Flush();

  // Primitives
  static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                       const glm::vec4 &color);
  static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                       const glm::vec4 &color);
  static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                       const Ref<Texture2D> &texture,
                       float tiling_factor = 1.0f,
                       const glm::vec4 &tint_color = glm::vec4(1.0f));
  static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                       const Ref<Texture2D> &texture,
                       float tiling_factor = 1.0f,
                       const glm::vec4 &tint_color = glm::vec4(1.0f));

  static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color);
  static void DrawQuad(const glm::mat4 &transform,
                       const Ref<Texture2D> &texture,
                       float tiling_factor = 1.0f,
                       const glm::vec4 &tint_color = glm::vec4(1.0f));

  static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size,
                              float rotation, const glm::vec4 &color);
  static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size,
                              float rotation, const glm::vec4 &color);
  static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size,
                              float rotation, const Ref<Texture2D> &texture,
                              float tiling_factor = 1.0f,
                              const glm::vec4 &tint_color = glm::vec4(1.0f));
  static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size,
                              float rotation, const Ref<Texture2D> &texture,
                              float tiling_factor = 1.0f,
                              const glm::vec4 &tint_color = glm::vec4(1.0f));

  struct Statistics {
    uint32_t draw_calls = 0;
    uint32_t quad_count = 0;

    uint32_t GetTotalVertexCount() const { return quad_count * 4; }
    uint32_t GetTotalIndexCount() const { return quad_count * 6; }
  };
  static void ResetStats();
  static Statistics GetStats();

private:
  static void StartBatch();
  static void NextBatch();
};
} // namespace bsw