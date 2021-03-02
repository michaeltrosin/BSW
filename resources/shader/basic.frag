#version 450

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in flat float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

#define OVAL   0
#define LINE     1
#define TRIANGLE 2
#define ARC      3

// If true, this will enable geometric drawing e.g. Lines, Circles, Arcs, etc.
uniform bool u_GeometryMode = false;
uniform float u_LineThicknes = 1.0f;// if <= 0.0f then filled
uniform int u_DrawMode = 0;

bool filled() {
    return u_LineThicknes <= 0.0f;
}

void main()
{
    if (u_GeometryMode) {
        switch (u_DrawMode) {
            case OVAL:
            { }
            break;
            case LINE:
            { }
            break;
            case TRIANGLE:
            { }
            break;
            case ARC:
            { }
            break;
        }
    }

    vec4 texColor = v_Color;
    texColor *= texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor);
    color = texColor;
}