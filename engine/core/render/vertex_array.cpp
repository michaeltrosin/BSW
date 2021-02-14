//
// Created by Michael on 14.02.2021.
//

#include "vertex_array.h"

#include <glad/glad.h>

namespace bsw {
static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type) {
  switch (type) {
  case ShaderDataType::FLOAT:
  case ShaderDataType::FLOAT_2:
  case ShaderDataType::FLOAT_3:
  case ShaderDataType::FLOAT_4:
  case ShaderDataType::MAT_3:
  case ShaderDataType::MAT_4:
    return GL_FLOAT;
  case ShaderDataType::INT:
  case ShaderDataType::INT_2:
  case ShaderDataType::INT_3:
  case ShaderDataType::INT_4:
    return GL_INT;
  case ShaderDataType::BOOL:
    return GL_BOOL;
  default:
    break;
  }

  ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

VertexArray::VertexArray() : render_id_{0}, vertex_buffer_index_{0} {
  glCreateVertexArrays(1, &render_id_);
}
VertexArray::~VertexArray() { glDeleteVertexArrays(1, &render_id_); }
void VertexArray::Bind() const { glBindVertexArray(render_id_); }
void VertexArray::Unbind() const { glBindVertexArray(0); }
void VertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertex_buffer) {
  Bind();
  vertex_buffer->Bind();

  const auto &layout = vertex_buffer->GetLayout();
  for (const auto &element : layout) {
    switch (element.type) {
    case ShaderDataType::FLOAT:
    case ShaderDataType::FLOAT_2:
    case ShaderDataType::FLOAT_3:
    case ShaderDataType::FLOAT_4: {
      glEnableVertexAttribArray(vertex_buffer_index_);
      glVertexAttribPointer(vertex_buffer_index_, element.GetComponentCount(),
                            ShaderDataTypeToOpenGlBaseType(element.type),
                            element.normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(), (const void *)element.offset);
      vertex_buffer_index_++;
      break;
    }
    case ShaderDataType::INT:
    case ShaderDataType::INT_2:
    case ShaderDataType::INT_3:
    case ShaderDataType::INT_4:
    case ShaderDataType::BOOL: {
      glEnableVertexAttribArray(vertex_buffer_index_);
      glVertexAttribIPointer(vertex_buffer_index_, element.GetComponentCount(),
                             ShaderDataTypeToOpenGlBaseType(element.type),
                             layout.GetStride(), (const void *)element.offset);
      vertex_buffer_index_++;
      break;
    }
    case ShaderDataType::MAT_3:
    case ShaderDataType::MAT_4: {
      uint8_t count = element.GetComponentCount();
      for (uint8_t i = 0; i < count; i++) {
        glEnableVertexAttribArray(vertex_buffer_index_);
        glVertexAttribPointer(
            vertex_buffer_index_, count,
            ShaderDataTypeToOpenGlBaseType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
            (const void *)(element.offset + sizeof(float) * count * i));
        glVertexAttribDivisor(vertex_buffer_index_, 1);
        vertex_buffer_index_++;
      }
      break;
    }
    default:
      ASSERT(false, "Unknown ShaderDataType!");
    }
  }

  vertex_buffers_.push_back(vertex_buffer);
}

void VertexArray::SetIndexBuffer(const Ref<IndexBuffer> &index_buffer) {
  glBindVertexArray(render_id_);
  index_buffer->Bind();

  index_buffer_ = index_buffer;
}
}; // namespace bsw