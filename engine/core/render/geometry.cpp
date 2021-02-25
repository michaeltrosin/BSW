//
// Created by Michael on 23.02.2021.
//

#include "geometry.h"
uint32_t Geometry::index_count() const { return m_vertices.size(); }

void Geometry::set_data(const std::vector<glm::vec4> &vertices) { m_vertices = vertices; }
