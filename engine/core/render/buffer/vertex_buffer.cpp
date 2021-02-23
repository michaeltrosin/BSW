//
// Created by Michael on 14.02.2021.
//

#include "vertex_buffer.h"

#include <glad/glad.h>

bsw::VertexBuffer::VertexBuffer(uint32_t size) : m_buffer_id{0} {
    glCreateBuffers(1, &m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
bsw::VertexBuffer::VertexBuffer(float *vertices, uint32_t size) : m_buffer_id{0} {
    glCreateBuffers(1, &m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
bsw::VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_buffer_id); }

void bsw::VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id); }
void bsw::VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void bsw::VertexBuffer::set_data(const void *data, uint32_t size) const {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

}// namespace bsw