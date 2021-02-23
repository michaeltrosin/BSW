//
// Created by Michael on 14.02.2021.
//

#include "index_buffer.h"

#include <glad/glad.h>

bsw::IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count) : m_buffer_id{0}, m_count(count) {
    glCreateBuffers(1, &m_buffer_id);

    // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO
    // state.
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}
bsw::IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_buffer_id); }

void bsw::IndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id); }
void bsw::IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }