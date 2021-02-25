//
// Created by Michael on 23.02.2021.
//

#pragma once

#include <glm/glm.hpp>

#include <cstdint>
#include <vector>

class Geometry {
public:
    virtual ~Geometry() = 0;

    uint32_t index_count() const;

protected:
    void set_data(const std::vector<glm::vec4>& vertices);

private:
    std::vector<glm::vec4> m_vertices;
    float m_width{1.0f};
};
