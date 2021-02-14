//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <vector>

#include <bsw.h>
#include <core/render/buffer/index_buffer.h>
#include <core/render/buffer/vertex_buffer.h>

namespace bsw {
class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void Bind() const;
  void Unbind() const;

  void AddVertexBuffer(const Ref<VertexBuffer> &vertex_buffer);
  void SetIndexBuffer(const Ref<IndexBuffer> &index_buffer);

  const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const {
    return vertex_buffers_;
  }
  const Ref<bsw::IndexBuffer> &GetIndexBuffer() const { return index_buffer_; }

private:
  uint32_t render_id_;
  uint32_t vertex_buffer_index_;

  std::vector<Ref<VertexBuffer>> vertex_buffers_;
  Ref<IndexBuffer> index_buffer_;
};
} // namespace bsw