//
// Created by Michael on 12.02.2021.
//

#include "renderer2d.h"

#include <core/render/gl_render.h>
#include <core/render/shader.h>
#include <glm/gtc/matrix_transform.hpp>

namespace bsw {
struct QuadVertex {
  glm::vec3 position;
  glm::vec4 color;
  glm::vec2 tex_coord;
  float tex_index;
  float tiling_factor;
};

struct Renderer2DData {
  static constexpr uint32_t max_quads = 20000;
  static constexpr uint32_t max_vertices = max_quads * 4;
  static constexpr uint32_t max_indices = max_quads * 6;
  static constexpr uint32_t max_texture_slots = 32; // TODO: RenderCaps

  Ref<VertexArray> quad_vertex_array;
  Ref<VertexBuffer> quad_vertex_buffer;
  Ref<Shader> texture_shader;
  Ref<Texture2D> white_texture;

  uint32_t quad_index_count = 0;
  QuadVertex *quad_vertex_buffer_base = nullptr;
  QuadVertex *quad_vertex_buffer_ptr = nullptr;

  std::array<Ref<Texture2D>, max_texture_slots> texture_slots{};
  uint32_t texture_slot_index = 1; // 0 = white texture

  glm::vec4 quad_vertex_positions[4]{};

  Renderer2D::Statistics stats{};
};

static Renderer2DData sData;

void Renderer2D::Init() {
  sData.quad_vertex_array = CreateRef<VertexArray>();
  sData.quad_vertex_buffer =
      CreateRef<VertexBuffer>(bsw::Renderer2DData::max_vertices * sizeof(QuadVertex));
  sData.quad_vertex_buffer->SetLayout(
      {{ShaderDataType::FLOAT_3, "a_Position"},
       {ShaderDataType::FLOAT_4, "a_Color"},
       {ShaderDataType::FLOAT_2, "a_TexCoord"},
       {ShaderDataType::FLOAT, "a_TexIndex"},
       {ShaderDataType::FLOAT, "a_TilingFactor"}});

  sData.quad_vertex_array->AddVertexBuffer(sData.quad_vertex_buffer);
  sData.quad_vertex_buffer_base = new QuadVertex[bsw::Renderer2DData::max_vertices];

  auto *quad_indices = new uint32_t[bsw::Renderer2DData::max_indices];
  uint32_t offset = 0;

  for (uint32_t i = 0; i < bsw::Renderer2DData::max_indices; i += 6) {
    quad_indices[i + 0] = offset + 0;
    quad_indices[i + 1] = offset + 1;
    quad_indices[i + 2] = offset + 2;

    quad_indices[i + 3] = offset + 2;
    quad_indices[i + 4] = offset + 3;
    quad_indices[i + 5] = offset + 0;

    offset += 4;
  }

  Ref<IndexBuffer> quad_ib =
      CreateRef<IndexBuffer>(quad_indices, bsw::Renderer2DData::max_indices);
  sData.quad_vertex_array->SetIndexBuffer(quad_ib);

  sData.white_texture = CreateRef<Texture2D>(1, 1);
  uint32_t white_texture_data = 0xffffffff;
  sData.white_texture->SetData(&white_texture_data, sizeof(uint32_t));

  int32_t samplers[bsw::Renderer2DData::max_texture_slots];
  for (uint32_t i = 0; i < bsw::Renderer2DData::max_texture_slots; i++)
    samplers[i] = i;

  sData.texture_shader = CreateRef<Shader>(
      "basic_texture",
#pragma region vertex
      "#version 450\n"
      "\n"
      "layout(location = 0) in vec3 a_Position;\n"
      "layout(location = 1) in vec4 a_Color;\n"
      "layout(location = 2) in vec2 a_TexCoord;\n"
      "layout(location = 3) in float a_TexIndex;\n"
      "layout(location = 4) in float a_TilingFactor;\n"
      "\n"
      "uniform mat4 u_ViewProjection;\n"
      "\n"
      "out vec4 v_Color;\n"
      "out vec2 v_TexCoord;\n"
      "out flat float v_TexIndex;\n"
      "out float v_TilingFactor;\n"
      "\n"
      "void main()\n"
      "{\n"
      "\tv_Color = a_Color;\n"
      "\tv_TexCoord = a_TexCoord;\n"
      "\tv_TexIndex = a_TexIndex;\n"
      "\tv_TilingFactor = a_TilingFactor;\n"
      "\tgl_Position = u_ViewProjection * vec4(a_Position, 1.0);\n"
      "}",
#pragma endregion
#pragma region fragment
      "#version 450\n"
      "\n"
      "layout(location = 0) out vec4 color;\n"
      "\n"
      "in vec4 v_Color;\n"
      "in vec2 v_TexCoord;\n"
      "in flat float v_TexIndex;\n"
      "in float v_TilingFactor;\n"
      "\n"
      "uniform sampler2D u_Textures[32];\n"
      "\n"
      "void main()\n"
      "{\n"
      "\tvec4 texColor = v_Color;\n"
      "\tswitch(int(v_TexIndex))\n"
      "\t{\n"
      "\t\tcase 0: texColor *= texture(u_Textures[0], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 1: texColor *= texture(u_Textures[1], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 2: texColor *= texture(u_Textures[2], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 3: texColor *= texture(u_Textures[3], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 4: texColor *= texture(u_Textures[4], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 5: texColor *= texture(u_Textures[5], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 6: texColor *= texture(u_Textures[6], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 7: texColor *= texture(u_Textures[7], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 8: texColor *= texture(u_Textures[8], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 9: texColor *= texture(u_Textures[9], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 10: texColor *= texture(u_Textures[10], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 11: texColor *= texture(u_Textures[11], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 12: texColor *= texture(u_Textures[12], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 13: texColor *= texture(u_Textures[13], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 14: texColor *= texture(u_Textures[14], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 15: texColor *= texture(u_Textures[15], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 16: texColor *= texture(u_Textures[16], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 17: texColor *= texture(u_Textures[17], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 18: texColor *= texture(u_Textures[18], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 19: texColor *= texture(u_Textures[19], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 20: texColor *= texture(u_Textures[20], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 21: texColor *= texture(u_Textures[21], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 22: texColor *= texture(u_Textures[22], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 23: texColor *= texture(u_Textures[23], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 24: texColor *= texture(u_Textures[24], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 25: texColor *= texture(u_Textures[25], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 26: texColor *= texture(u_Textures[26], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 27: texColor *= texture(u_Textures[27], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 28: texColor *= texture(u_Textures[28], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 29: texColor *= texture(u_Textures[29], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 30: texColor *= texture(u_Textures[30], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t\tcase 31: texColor *= texture(u_Textures[31], v_TexCoord * "
      "v_TilingFactor); break;\n"
      "\t}\n"
      "\tcolor = texColor;\n"
      "}"
#pragma endregion
  );

  sData.texture_shader->Bind();

  sData.texture_shader->SetIntArray("u_Textures", samplers, bsw::Renderer2DData::max_texture_slots);
  sData.texture_slots[0] = sData.white_texture;

  sData.quad_vertex_positions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
  sData.quad_vertex_positions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
  sData.quad_vertex_positions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
  sData.quad_vertex_positions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
}

void Renderer2D::Shutdown() { delete[] sData.quad_vertex_buffer_base; }

void Renderer2D::Begin(const glm::mat4 &view_projection) {
  sData.texture_shader->Bind();
  sData.texture_shader->SetMat4("u_ViewProjection", view_projection);

  StartBatch();
}

void Renderer2D::End() { Flush(); }

void Renderer2D::StartBatch() {
  sData.quad_index_count = 0;
  sData.quad_vertex_buffer_ptr = sData.quad_vertex_buffer_base;

  sData.texture_slot_index = 1;
}
void Renderer2D::NextBatch() {
  Flush();
  StartBatch();
}

void Renderer2D::Flush() {
  if (sData.quad_index_count == 0)
    return;

  auto data_size = (uint32_t)((uint8_t *)sData.quad_vertex_buffer_ptr -
                              (uint8_t *)sData.quad_vertex_buffer_base);
  sData.quad_vertex_buffer->SetData(sData.quad_vertex_buffer_base, data_size);

  for (uint32_t i = 0; i < sData.texture_slot_index; i++)
    sData.texture_slots[i]->Bind(i);

  GLRenderer::DrawIndexed(sData.quad_vertex_array, sData.quad_index_count);
  sData.stats.draw_calls++;
}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const glm::vec4 &color) {
  DrawQuad({position.x, position.y, 0.0f}, size, color);
}
void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const glm::vec4 &color) {
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

  DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const Ref<Texture2D> &texture, float tiling_factor,
                          const glm::vec4 &tint_color) {
  DrawQuad({position.x, position.y, 0.0f}, size, texture, tiling_factor,
           tint_color);
}
void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const Ref<Texture2D> &texture, float tiling_factor,
                          const glm::vec4 &tint_color) {
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

  DrawQuad(transform, texture, tiling_factor, tint_color);
}

void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color) {
  constexpr size_t kQuadVertexCount = 4;
  const float kTextureIndex = 0.0f; // White Texture
  constexpr glm::vec2 kTextureCoords[] = {
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  const float kTilingFactor = 1.0f;

  if (sData.quad_index_count >= bsw::Renderer2DData::max_indices)
    NextBatch();

  for (size_t i = 0; i < kQuadVertexCount; i++) {
    sData.quad_vertex_buffer_ptr->position =
        transform * sData.quad_vertex_positions[i];
    sData.quad_vertex_buffer_ptr->color = color;
    sData.quad_vertex_buffer_ptr->tex_coord = kTextureCoords[i];
    sData.quad_vertex_buffer_ptr->tex_index = kTextureIndex;
    sData.quad_vertex_buffer_ptr->tiling_factor = kTilingFactor;
    sData.quad_vertex_buffer_ptr++;
  }

  sData.quad_index_count += 6;

  sData.stats.quad_count++;
}

void Renderer2D::DrawQuad(const glm::mat4 &transform,
                          const Ref<Texture2D> &texture, float tiling_factor,
                          const glm::vec4 &tint_color) {
  constexpr size_t kQuadVertexCount = 4;
  constexpr glm::vec2 kTextureCoords[] = {
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

  if (sData.quad_index_count >= bsw::Renderer2DData::max_indices)
    NextBatch();

  float texture_index = 0.0f;
  for (uint32_t i = 1; i < sData.texture_slot_index; i++) {
    if (*sData.texture_slots[i] == *texture) {
      texture_index = (float)i;
      break;
    }
  }

  if (texture_index == 0.0f) {
    if (sData.texture_slot_index >= bsw::Renderer2DData::max_texture_slots)
      NextBatch();

    texture_index = (float)sData.texture_slot_index;
    sData.texture_slots[sData.texture_slot_index] = texture;
    sData.texture_slot_index++;
  }

  for (size_t i = 0; i < kQuadVertexCount; i++) {
    sData.quad_vertex_buffer_ptr->position =
        transform * sData.quad_vertex_positions[i];
    sData.quad_vertex_buffer_ptr->color = tint_color;
    sData.quad_vertex_buffer_ptr->tex_coord = kTextureCoords[i];
    sData.quad_vertex_buffer_ptr->tex_index = texture_index;
    sData.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    sData.quad_vertex_buffer_ptr++;
  }

  sData.quad_index_count += 6;

  sData.stats.quad_count++;
}

void Renderer2D::DrawRotatedQuad(const glm::vec2 &position,
                                 const glm::vec2 &size, float rotation,
                                 const glm::vec4 &color) {
  DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3 &position,
                                 const glm::vec2 &size, float rotation,
                                 const glm::vec4 &color) {
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f}) *
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

  DrawQuad(transform, color);
}
void Renderer2D::DrawRotatedQuad(const glm::vec2 &position,
                                 const glm::vec2 &size, float rotation,
                                 const Ref<Texture2D> &texture,
                                 float tiling_factor,
                                 const glm::vec4 &tint_color) {
  DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture,
                  tiling_factor, tint_color);
}
void Renderer2D::DrawRotatedQuad(const glm::vec3 &position,
                                 const glm::vec2 &size, float rotation,
                                 const Ref<Texture2D> &texture,
                                 float tiling_factor,
                                 const glm::vec4 &tint_color) {
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f}) *
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

  DrawQuad(transform, texture, tiling_factor, tint_color);
}

void Renderer2D::ResetStats() { memset(&sData.stats, 0, sizeof(Statistics)); }

Renderer2D::Statistics Renderer2D::GetStats() { return sData.stats; }
}; // namespace bsw