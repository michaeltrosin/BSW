//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <bsw.h>

#include <utility>
#include <vector>

namespace bsw {
enum class ShaderDataType {
  NONE = 0,
  FLOAT,
  FLOAT_2,
  FLOAT_3,
  FLOAT_4,
  MAT_3,
  MAT_4,
  INT,
  INT_2,
  INT_3,
  INT_4,
  BOOL
};

static uint32_t ShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
  case ShaderDataType::FLOAT:
    return 4;
  case ShaderDataType::FLOAT_2:
    return 4 * 2;
  case ShaderDataType::FLOAT_3:
    return 4 * 3;
  case ShaderDataType::FLOAT_4:
    return 4 * 4;
  case ShaderDataType::MAT_3:
    return 4 * 3 * 3;
  case ShaderDataType::MAT_4:
    return 4 * 4 * 4;
  case ShaderDataType::INT:
    return 4;
  case ShaderDataType::INT_2:
    return 4 * 2;
  case ShaderDataType::INT_3:
    return 4 * 3;
  case ShaderDataType::INT_4:
    return 4 * 4;
  case ShaderDataType::BOOL:
    return 1;
  default:
    break;
  }

  ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

struct BufferElement {
  std::string name;
  ShaderDataType type;
  uint32_t size;
  size_t offset;
  bool normalized;

  BufferElement(ShaderDataType type, std::string name,
                bool normalized = false)
      : name(std::move(name)), type(type), size(ShaderDataTypeSize(type)),
        offset(0), normalized(normalized) {}

  uint32_t GetComponentCount() const {
    switch (type) {
    case ShaderDataType::FLOAT:
      return 1;
    case ShaderDataType::FLOAT_2:
      return 2;
    case ShaderDataType::FLOAT_3:
      return 3;
    case ShaderDataType::FLOAT_4:
      return 4;
    case ShaderDataType::MAT_3:
      return 3; // 3* float3
    case ShaderDataType::MAT_4:
      return 4; // 4* float4
    case ShaderDataType::INT:
      return 1;
    case ShaderDataType::INT_2:
      return 2;
    case ShaderDataType::INT_3:
      return 3;
    case ShaderDataType::INT_4:
      return 4;
    case ShaderDataType::BOOL:
      return 1;
    default:
      break;
    }

    ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }
};

class BufferLayout {
public:
  BufferLayout() = default;

  BufferLayout(std::initializer_list<BufferElement> elements)
      : elements_(elements) {
    CalculateOffsetsAndStride();
  }

  uint32_t GetStride() const { return stride_; }
  const std::vector<BufferElement> &GetElements() const { return elements_; }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
  std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
  std::vector<BufferElement>::iterator end() { return elements_.end(); }
  std::vector<BufferElement>::const_iterator begin() const {
    return elements_.begin();
  }
  std::vector<BufferElement>::const_iterator end() const {
    return elements_.end();
  }
#pragma clang diagnostic pop

private:
  void CalculateOffsetsAndStride() {
    size_t offset = 0;
    stride_ = 0;
    for (auto &element : elements_) {
      element.offset = offset;
      offset += element.size;
      stride_ += element.size;
    }
  }

private:
  std::vector<BufferElement> elements_{};
  uint32_t stride_ = 0;
};
} // namespace bsw