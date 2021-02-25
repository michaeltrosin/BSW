//
// Created by Michael on 23.02.2021.
//

#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

namespace bsw {
class ShaderStorageBuffer {
public:
    explicit ShaderStorageBuffer(const std::vector<glm::vec4> &vertex_array);

    void bind() const;
    void unbind() const;
private:
    uint32_t m_buffer_id;
};
}// namespace bsw