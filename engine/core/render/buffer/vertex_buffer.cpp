//
// Created by Michael on 14.02.2021.
//

#include "vertex_buffer.h"

#include <glad/glad.h>

namespace bsw {
VertexBuffer::VertexBuffer(uint32_t size) : buffer_id_{0} {
  glCreateBuffers(1, &buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
VertexBuffer::VertexBuffer(float *vertices, uint32_t size) : buffer_id_{0} {
  glCreateBuffers(1, &buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &buffer_id_); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, buffer_id_); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::SetData(const void *data, uint32_t size) const {
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
} // namespace bsw