
// Auto-generated file. Do not edit.
#pragma once

namespace generated_shaders {

inline constexpr const char* default_vert = R"GLSL(
#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform float x;
uniform float y;
void main()
{
    gl_Position = vec4(aPos.x + x, aPos.y +y , aPos.z, 1.0);
    Color = aColor;
    TexCoord = aTexCoord;
}
)GLSL";

inline constexpr const char* default_frag = R"GLSL(
#version 400 core
out vec4 FragColor;
in vec3 Color;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord) * vec4(Color, 1.0);
}
)GLSL";

inline constexpr const char* screen_vert = R"GLSL(
#version 400 core
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
#version 400 core
out vec4 FragColor;
in vec2 TexCoords;

uniform smapler2D screenTexture;

void main() {
    vec3 col = texture(screenTexture, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
}

)GLSL";

} // namespace generated_shaders
