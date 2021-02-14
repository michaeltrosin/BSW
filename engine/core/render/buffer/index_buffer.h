//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <cstdint>

namespace bsw {
class IndexBuffer {
public:
  IndexBuffer(uint32_t *indices, uint32_t count);
  ~IndexBuffer();

  void Bind() const;
  void Unbind() const;

  uint32_t GetCount() const { return count_; }

private:
  uint32_t buffer_id_;
  uint32_t count_;
};
}