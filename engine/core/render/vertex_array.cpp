//
// Created by Michael on 14.02.2021.
//

#include "vertex_array.h"

#include <glad/glad.h>

static GLenum shader_data_type_to_open_gl_base_type(bsw::ShaderDataType type) {
    switch (type) {
        case bsw::ShaderDataType::FLOAT:
        case bsw::ShaderDataType::FLOAT_2:
        case bsw::ShaderDataType::FLOAT_3:
        case bsw::ShaderDataType::FLOAT_4:
        case bsw::ShaderDataType::MAT_3:
        case bsw::ShaderDataType::MAT_4: return GL_FLOAT;
        case bsw::ShaderDataType::INT:
        case bsw::ShaderDataType::INT_2:
        case bsw::ShaderDataType::INT_3:
        case bsw::ShaderDataType::INT_4: return GL_INT;
        case bsw::ShaderDataType::BOOL: return GL_BOOL;
        default: break;
    }

    ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

bsw::VertexArray::VertexArray() : m_render_id{0}, m_vertex_buffer_index{0} { glCreateVertexArrays(1, &m_render_id); }
bsw::VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_render_id); }

void bsw::VertexArray::bind() const { glBindVertexArray(m_render_id); }
void bsw::VertexArray::unbind() const { glBindVertexArray(0); }
void bsw::VertexArray::add_vertex_buffer(const Ref<VertexBuffer> &vertex_buffer) {
    bind();
    vertex_buffer->bind();

    const auto &layout = vertex_buffer->get_layout();
    for (const auto &element : layout) {
        switch (element.type) {
            case ShaderDataType::FLOAT:
            case ShaderDataType::FLOAT_2:
            case ShaderDataType::FLOAT_3:
            case ShaderDataType::FLOAT_4: {
                glEnableVertexAttribArray(m_vertex_buffer_index);
                glVertexAttribPointer(m_vertex_buffer_index, element.get_component_count(), shader_data_type_to_open_gl_base_type(element.type),
                                      element.normalized ? GL_TRUE : GL_FALSE, layout.get_stride(), (const void *) element.offset);
                m_vertex_buffer_index++;
                break;
            }
            case ShaderDataType::INT:
            case ShaderDataType::INT_2:
            case ShaderDataType::INT_3:
            case ShaderDataType::INT_4:
            case ShaderDataType::BOOL: {
                glEnableVertexAttribArray(m_vertex_buffer_index);
                glVertexAttribIPointer(m_vertex_buffer_index, element.get_component_count(), shader_data_type_to_open_gl_base_type(element.type),
                                       layout.get_stride(), (const void *) element.offset);
                m_vertex_buffer_index++;
                break;
            }
            case ShaderDataType::MAT_3:
            case ShaderDataType::MAT_4: {
                uint8_t count = element.get_component_count();
                for (uint8_t i = 0; i < count; i++) {
                    glEnableVertexAttribArray(m_vertex_buffer_index);
                    glVertexAttribPointer(m_vertex_buffer_index, count, shader_data_type_to_open_gl_base_type(element.type),
                                          element.normalized ? GL_TRUE : GL_FALSE, layout.get_stride(),
                                          (const void *) (element.offset + sizeof(float) * count * i));
                    glVertexAttribDivisor(m_vertex_buffer_index, 1);
                    m_vertex_buffer_index++;
                }
                break;
            }
            default: ASSERT(false, "Unknown ShaderDataType!");
        }
    }

    m_vertex_buffers.push_back(vertex_buffer);
}

void bsw::VertexArray::set_index_buffer(const Ref<IndexBuffer> &index_buffer) {
    glBindVertexArray(m_render_id);
    index_buffer->bind();

    m_index_buffer = index_buffer;
}