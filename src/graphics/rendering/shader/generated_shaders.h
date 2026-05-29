
// Auto-generated file. Do not edit.
#pragma once

namespace generated_shaders {

inline constexpr const char* default_vert = R"GLSL(
#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in uint aType;

out vec3 Color;

uniform mat4 uProj;
uniform vec2 uCellSize; //in world units
uniform ivec2 uGridSize; // (GRID_W, GRID_H)
uniform vec2 uCamera;

void main()
{
    int id = gl_InstanceID;
    int x  = id % uGridSize.x;
    int y  = id / uGridSize.x;

    vec2 cellOrigin = vec2(x, y) * uCellSize;

    vec2 pos = (cellOrigin + aPos) + uCamera;

    gl_Position = uProj * vec4(pos, 0.0, 1.0);
    Color = vec3(0.0, y, x);
    switch(aType){
        case 0:
            //Color = vec3(0.0, 0.5, 0.0); //air
            break;
        case 1:
           Color = vec3(0.8863, 0.7922, 0.4627); // sand
            break;
        case 2:
            Color = vec3(0.1, 0.1, 0.1); //solid
            break;
        case 3:
            Color = vec3(0.0, 1.0, 1.0);
            break;
        case 4:
            Color = vec3(0.0, 0.0, 1.0);
            break;
        case 5:
            Color = vec3(0.0, 0.0, 0.0);
            break;
        default:
            Color = vec3(0.5, 0.5, 0.5);
            break;
    }

}
)GLSL";

inline constexpr const char* default_frag = R"GLSL(
#version 460 core
out vec4 FragColor;
in vec3 Color;

uniform sampler2D texture1;

void main()
{
    FragColor = vec4(Color, 1.0);
}
)GLSL";

inline constexpr const char* screen_vert = R"GLSL(
#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;



void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);

}
)GLSL";

inline constexpr const char* screen_frag = R"GLSL(
#version 460 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main() {
    vec3 col = texture(screenTexture, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
}

)GLSL";

} // namespace generated_shaders
