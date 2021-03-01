#version 450

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in flat float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

// If true, this will enable geometric drawing e.g. Lines, Circles, Arcs, etc.
uniform bool u_GeometryMode = false;

void main()
{
    vec4 texColor = v_Color;
    texColor *= texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor);
    color = texColor;
}