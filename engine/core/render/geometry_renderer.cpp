//
// Created by Michael on 23.02.2021.
//

#include "geometry_renderer.h"

#include <core/render/buffer/vertex_buffer.h>
#include <core/render/shader.h>

#include <glad/glad.h>

struct GeometryData{
    Ref<bsw::VertexBuffer> quad_vertex_buffer;
    Ref<bsw::Shader> geometry_shader;
};

void bsw::GeometryRenderer::init() {

}

void bsw::GeometryRenderer::draw_geometry(const Geometry &geometry) {

    glDrawArrays(GL_TRIANGLES, 0, 6*(geometry.index_count()-1));

}
