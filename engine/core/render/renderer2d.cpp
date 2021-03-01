//
// Created by Michael on 12.02.2021.
//

#include "renderer2d.h"

#include <bsw.h>
#include <core/render/gl_render.h>
#include <core/render/shading/shader.h>

#include <glm/gtc/matrix_transform.hpp>

struct QuadVertex {
    glm::vec3 position{};
    Color color;
    glm::vec2 tex_coord{};
    float tex_index{};
    float tiling_factor{};
};

struct Renderer2DData {
    static constexpr uint32_t max_quads = 20000;
    static constexpr uint32_t max_vertices = max_quads * 4;
    static constexpr uint32_t max_indices = max_quads * 6;
    static constexpr uint32_t max_texture_slots = 32;// TODO: RenderCaps

    Ref<bsw::VertexArray> quad_vertex_array;
    Ref<bsw::VertexBuffer> quad_vertex_buffer;
    Ref<bsw::Shader> texture_shader;
    Ref<bsw::Texture2D> white_texture;

    uint32_t quad_index_count = 0;
    QuadVertex *quad_vertex_buffer_base = nullptr;
    QuadVertex *quad_vertex_buffer_ptr = nullptr;

    std::array<Ref<bsw::Texture2D>, max_texture_slots> texture_slots{};
    uint32_t texture_slot_index = 1;// 0 = white texture

    glm::vec4 quad_vertex_positions[4]{};

    bsw::Renderer2D::Statistics stats{};
};

static Renderer2DData data;

void bsw::Renderer2D::init() {
    data.quad_vertex_array = create_ref<VertexArray>();
    data.quad_vertex_buffer = create_ref<VertexBuffer>(Renderer2DData::max_vertices * sizeof(QuadVertex));
    data.quad_vertex_buffer->set_layout({{ShaderDataType::FLOAT_3, "a_Position"},
                                         {ShaderDataType::FLOAT_4, "a_Color"},
                                         {ShaderDataType::FLOAT_2, "a_TexCoord"},
                                         {ShaderDataType::FLOAT, "a_TexIndex"},
                                         {ShaderDataType::FLOAT, "a_TilingFactor"}});

    data.quad_vertex_array->add_vertex_buffer(data.quad_vertex_buffer);
    data.quad_vertex_buffer_base = new QuadVertex[Renderer2DData::max_vertices];

    auto *quad_indices = new uint32_t[Renderer2DData::max_indices];
    uint32_t offset = 0;

    for (uint32_t i = 0; i < Renderer2DData::max_indices; i += 6) {
        quad_indices[i + 0] = offset + 0;
        quad_indices[i + 1] = offset + 1;
        quad_indices[i + 2] = offset + 2;

        quad_indices[i + 3] = offset + 2;
        quad_indices[i + 4] = offset + 3;
        quad_indices[i + 5] = offset + 0;

        offset += 4;
    }

    Ref<IndexBuffer> quad_ib = create_ref<IndexBuffer>(quad_indices, Renderer2DData::max_indices);
    data.quad_vertex_array->set_index_buffer(quad_ib);

    data.white_texture = create_ref<Texture2D>(1, 1);
    uint32_t white_texture_data = 0xffffffff;
    data.white_texture->set_data(&white_texture_data, sizeof(uint32_t));

    int32_t samplers[Renderer2DData::max_texture_slots];
    for (uint32_t i = 0; i < Renderer2DData::max_texture_slots; i++) samplers[i] = i;

    data.texture_shader =
        create_ref<Shader>("basic_texture", AssetManager::read_all("shader/basic_vertex.glsl").data, AssetManager::read_all("shader/basic_fragment.glsl").data);

    data.texture_shader->bind();

    data.texture_shader->set_int_array("u_Textures", samplers, Renderer2DData::max_texture_slots);
    data.texture_slots[0] = data.white_texture;

    data.quad_vertex_positions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    data.quad_vertex_positions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    data.quad_vertex_positions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    data.quad_vertex_positions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
}

void bsw::Renderer2D::shutdown() { delete[] data.quad_vertex_buffer_base; }

void bsw::Renderer2D::begin(const glm::mat4 &view_projection) {
    data.texture_shader->bind();
    data.texture_shader->set_mat_4("u_ViewProjection", view_projection);

    start_batch();
}

void bsw::Renderer2D::end() { flush(); }

void bsw::Renderer2D::start_batch() {
    data.quad_index_count = 0;
    data.quad_vertex_buffer_ptr = data.quad_vertex_buffer_base;

    data.texture_slot_index = 1;
}

void bsw::Renderer2D::next_batch() {
    flush();
    start_batch();
}

void bsw::Renderer2D::flush() {
    if (data.quad_index_count == 0) return;

    auto data_size = (uint32_t)((uint8_t *) data.quad_vertex_buffer_ptr - (uint8_t *) data.quad_vertex_buffer_base);
    data.quad_vertex_buffer->set_data(data.quad_vertex_buffer_base, data_size);

    for (uint32_t i = 0; i < data.texture_slot_index; i++) data.texture_slots[i]->bind(i);

    GlRenderer::draw_indexed(data.quad_vertex_array, data.quad_index_count);
    data.stats.draw_calls++;
}

void bsw::Renderer2D::draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Color &color) {
    draw_quad({position.x, position.y, 0.0f}, size, color);
}
void bsw::Renderer2D::draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Color &color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, color);
}

void bsw::Renderer2D::draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, glm::vec2 *texture_coords,
                                float tiling_factor, const Color &tint_color) {
    draw_quad({position.x, position.y, 0.0f}, size, texture, texture_coords, tiling_factor, tint_color);
}

void bsw::Renderer2D::draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, glm::vec2 *texture_coords,
                                float tiling_factor, const Color &tint_color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, texture, texture_coords, tiling_factor, tint_color);
}

void bsw::Renderer2D::draw_quad(const glm::mat4 &transform, const Color &color) {
    constexpr size_t quad_vertex_count = 4;
    const float texture_index = 0.0f;// White Texture
    constexpr glm::vec2 texture_coords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    const float tiling_factor = 1.0f;

    if (data.quad_index_count >= Renderer2DData::max_indices) next_batch();

    for (size_t i = 0; i < quad_vertex_count; i++) {
        data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[i];
        data.quad_vertex_buffer_ptr->color = color;
        data.quad_vertex_buffer_ptr->tex_coord = texture_coords[i];
        data.quad_vertex_buffer_ptr->tex_index = texture_index;
        data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        data.quad_vertex_buffer_ptr++;
    }

    data.quad_index_count += 6;

    data.stats.quad_count++;
}

void bsw::Renderer2D::draw_quad(const glm::mat4 &transform, const Ref<Texture2D> &texture, glm::vec2 *tex_coords, float tiling_factor,
                                const Color &tint_color) {
    constexpr size_t quad_vertex_count = 4;
    Color color = tint_color;

    if (data.quad_index_count >= Renderer2DData::max_indices) next_batch();

    float texture_index = 0.0f;
    for (uint32_t i = 1; i < data.texture_slot_index; i++) {
        if (*data.texture_slots[i] == *texture) {
            texture_index = (float) i;
            break;
        }
    }

    if (texture_index == 0.0f) {
        if (data.texture_slot_index >= Renderer2DData::max_texture_slots) next_batch();

        texture_index = (float) data.texture_slot_index;
        data.texture_slots[data.texture_slot_index] = texture;
        data.texture_slot_index++;
    }

    //    if (tint_color.get_a() != 255) {
    //        color = color.blend(tint_color)
    //    }

    for (size_t i = 0; i < quad_vertex_count; i++) {
        data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[i];
        data.quad_vertex_buffer_ptr->color = color;
        data.quad_vertex_buffer_ptr->tex_coord = tex_coords[i];
        data.quad_vertex_buffer_ptr->tex_index = texture_index;
        data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        data.quad_vertex_buffer_ptr++;
    }

    data.quad_index_count += 6;

    data.stats.quad_count++;
}

void bsw::Renderer2D::draw_rotated_quad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Color &color) {
    draw_rotated_quad({position.x, position.y, 0.0f}, size, rotation, color);
}

void bsw::Renderer2D::draw_rotated_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Color &color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
                        * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, color);
}
void bsw::Renderer2D::draw_rotated_quad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture,
                                        float tiling_factor, const Color &tint_color) {
    draw_rotated_quad({position.x, position.y, 0.0f}, size, rotation, texture, tiling_factor, tint_color);
}
void bsw::Renderer2D::draw_rotated_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture,
                                        float tiling_factor, const Color &tint_color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
                        * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    draw_quad(transform, texture, tiling_factor, tint_color);
}

void bsw::Renderer2D::reset_stats() { memset(&data.stats, 0, sizeof(Statistics)); }

bsw::Renderer2D::Statistics bsw::Renderer2D::get_stats() { return data.stats; }

void bsw::Renderer2D::draw_quad(const glm::mat4 &transform, const Ref<Texture2D> &texture, float tiling_factor, const Color &tint_color) {
    glm::vec2 tex_coords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

    draw_quad(transform, texture, tex_coords, tiling_factor, tint_color);
}
void bsw::Renderer2D::draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tiling_factor,
                                const Color &tint_color) {
    glm::vec2 tex_coords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

    draw_quad(position, size, texture, tex_coords, tiling_factor, tint_color);
}
void bsw::Renderer2D::draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tiling_factor,
                                const Color &tint_color) {
    glm::vec2 tex_coords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    draw_quad(position, size, texture, tex_coords, tiling_factor, tint_color);
}
void bsw::Renderer2D::draw_sub_quad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const glm::vec2 &cut_offset,
                                    const glm::vec2 &cut_size, float tiling_factor, const Color &tint_color) {
    float cutoffx = cut_offset.x;
    float cutoffy = cut_offset.y;

    float cutwidth = cut_size.x;
    float cutheight = cut_size.y;

    cutoffx = (float) mathf::clamp(cutoffx, 0, texture->get_width());
    cutoffy = (float) mathf::clamp(cutoffy, 0, texture->get_height());
    cutwidth = (float) mathf::clamp(cutwidth, 0, texture->get_width());
    cutheight = (float) mathf::clamp(cutheight, 0, texture->get_height());

    auto normx = [texture](float value) -> float { return (float) mathf::normalize(value, 0.0, texture->get_width()); };
    auto normy = [texture](float value) -> float { return (float) mathf::normalize(value, 0.0, texture->get_height()); };

    // 01 11
    // 00 10
    glm::vec2 bl = {normx(cutoffx), normy(cutoffy)};
    glm::vec2 br = {normx(cutoffx + cutwidth), normy(cutoffy)};
    glm::vec2 tl = {normx(cutoffx), normy(cutoffy + cutheight)};
    glm::vec2 tr = {normx(cutoffx + cutwidth), normy(cutoffy + cutheight)};

    glm::vec2 tex_coords[] = {bl, br, tr, tl};

    draw_quad(position, size, texture, tex_coords, tiling_factor, tint_color);
}
void bsw::Renderer2D::draw_sub_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const glm::vec2 &cut_offset,
                                    const glm::vec2 &cut_size, float tiling_factor, const Color &tint_color) {
    float cutoffx = cut_offset.x;
    float cutoffy = cut_offset.y;

    float cutwidth = cut_size.x;
    float cutheight = cut_size.y;

    cutoffx = (float) mathf::clamp(cutoffx, 0, texture->get_width());
    cutoffy = (float) mathf::clamp(cutoffy, 0, texture->get_height());
    cutwidth = (float) mathf::clamp(cutwidth, 0, texture->get_width());
    cutheight = (float) mathf::clamp(cutheight, 0, texture->get_height());

    auto normx = [texture](float value) -> float { return (float) mathf::normalize(value, 0.0, texture->get_width()); };
    auto normy = [texture](float value) -> float { return (float) mathf::normalize(value, 0.0, texture->get_height()); };

    // 01 11
    // 00 10
    glm::vec2 bl = {normx(cutoffx), normy(cutoffy)};
    glm::vec2 br = {normx(cutoffx + cutwidth), normy(cutoffy)};
    glm::vec2 tl = {normx(cutoffx), normy(cutoffy + cutheight)};
    glm::vec2 tr = {normx(cutoffx + cutwidth), normy(cutoffy + cutheight)};

    glm::vec2 tex_coords[] = {bl, br, tr, tl};

    draw_quad(position, size, texture, tex_coords, tiling_factor, tint_color);
}
void bsw::Renderer2D::draw_sub_quad(const glm::mat4 &transform, const Ref<Texture2D> &texture, const glm::vec2 &cut_offset, const glm::vec2 &cut_size,
                                    float tiling_factor, const Color &tint_color) {
    float cutoffx = cut_offset.x;
    float cutoffy = cut_offset.y;

    float cutwidth = cut_size.x;
    float cutheight = cut_size.y;

    cutoffx = (float) mathf::clamp(cutoffx, 0, texture->get_width());
    cutoffy = (float) mathf::clamp(cutoffy, 0, texture->get_height());
    cutwidth = (float) mathf::clamp(cutwidth, 0, texture->get_width());
    cutheight = (float) mathf::clamp(cutheight, 0, texture->get_height());

    auto normx = [texture](float value) -> float { return (float) mathf::normalize(value, 0.0, texture->get_width()); };
    auto normy = [texture](float value) -> float { return (float) mathf::normalize(value, 0.0, texture->get_height()); };

    // 01 11
    // 00 10
    glm::vec2 bl = {normx(cutoffx), normy(cutoffy)};
    glm::vec2 br = {normx(cutoffx + cutwidth), normy(cutoffy)};
    glm::vec2 tl = {normx(cutoffx), normy(cutoffy + cutheight)};
    glm::vec2 tr = {normx(cutoffx + cutwidth), normy(cutoffy + cutheight)};

    glm::vec2 tex_coords[] = {bl, br, tr, tl};

    draw_quad(transform, texture, tex_coords, tiling_factor, tint_color);
}

#pragma region FontRendering
void bsw::Renderer2D::draw_string(const std::string &text, const glm::vec2 &position, const Font &font, const Color &text_color) {
    draw_string(text, glm::vec3(position, 1.0f), font, text_color);
}

void bsw::Renderer2D::draw_string(const std::string &text, const glm::vec3 &position, const bsw::Font &font, const Color &text_color) {
    float x = position.x;
    float y = position.y;

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        auto metrics = font.get_font_data(*c);

        float xpos = (x + metrics.bearing.x);
        float ypos = (y - metrics.bearing.y);

        float w = metrics.size.x;
        float h = metrics.size.y;

        draw_sub_quad({xpos + w / 2, ypos + h / 2, position.z}, {w, h}, font.get_atlas(), {metrics.xoffset, metrics.yoffset}, {w, h}, 1.0f,
                      text_color);

        x += metrics.advance.x / 64;
    }
}

void bsw::Renderer2D::draw_centered_string(const std::string &text, const glm::vec2 &position, const Font &font, const Color &text_color) {
    draw_centered_string(text, glm::vec3(position, 1.0f), font, text_color);
}

void bsw::Renderer2D::draw_centered_string(const std::string &text, const glm::vec3 &position, const bsw::Font &font, const Color &text_color) {
    float width = font.get_string_width(text);
    float height = font.get_string_height(text);

    draw_string(text, {position.x - width / 2, position.y - height / 2}, font, text_color);
}
#pragma endregion