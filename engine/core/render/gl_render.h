//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <core/render/vertex_array.h>
#include <bsw.h>
#include <glm/glm.hpp>

namespace bsw {
class GlRenderer {
public:
  static void Init() ;
  static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) ;

  static void SetClearColor(const glm::vec4& color);
  static void Clear();

  static void DrawIndexed(const Ref<VertexArray>& vertex_array, uint32_t index_count = 0);
};
} // namespace b
// sw