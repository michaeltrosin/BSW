//
// Created by Michael on 21.02.2021.
//

#pragma once

#include <glm/glm.hpp>

namespace bsw {
class Camera {
public:
    Camera() = default;
    explicit Camera(const glm::mat4 &projection) : m_projection(projection) {}

    virtual ~Camera() = default;

    glm::mat4 get_view_projection() const { return m_projection * m_view; }
    const glm::mat4 &get_projection() const { return m_projection; }

protected:
    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);
};
}// namespace bsw