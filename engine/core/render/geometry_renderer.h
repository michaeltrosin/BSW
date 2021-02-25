//
// Created by Michael on 23.02.2021.
//

#pragma once

#include <core/render/geometry.h>
#include <glm/glm.hpp>
#include <math/color.h>

//https://stackoverflow.com/questions/60440682/drawing-a-line-in-modern-opengl

namespace bsw {
class GeometryRenderer {
public:
    static void init();

    static void draw_geometry(const Geometry &geometry);
};
}// namespace bsw