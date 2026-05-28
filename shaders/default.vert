#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in uint aType;

out vec3 Color;

uniform mat4 uProj;
uniform vec2 uCellSize; //in world units
vec2 pos = aPos * uCellSize + instanceOffset; //instanceOffset in world units

void main()
{
    gl_Position = uProj * vec4(pos, 0.0, 1.0);
    switch(aType){
        case 0:
            Color = vec3(0.0, 0.0, 0.0); //air
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