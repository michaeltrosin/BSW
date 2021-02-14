//
// Created by Michael on 14.02.2021.
//

#include "index_buffer.h"

#include <glad/glad.h>

namespace bsw {
IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count)
    : buffer_id_{0}, count_(count) {
  glCreateBuffers(1, &buffer_id_);

  // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
  // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO
  // state.
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &buffer_id_); }

void IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
}
void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
} // namespace bsw