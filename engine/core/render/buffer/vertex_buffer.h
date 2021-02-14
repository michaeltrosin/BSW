//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <cstdint>
#include <core/render/buffer/buffer_layout.h>

namespace bsw {
class VertexBuffer {
public:
  explicit VertexBuffer(uint32_t size);
  VertexBuffer(float* vertices, uint32_t size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;

  void SetData(const void* data, uint32_t size) const;

  const BufferLayout& GetLayout() const { return layout_; }
  void SetLayout(const BufferLayout& layout) { layout_ = layout; }
private:
  uint32_t buffer_id_;
  BufferLayout layout_;
};
} // namespace bsw