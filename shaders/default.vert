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


    vec2 cellOrigin = vec2(x, y) ;

    vec2 pos = (cellOrigin + aPos ) + uCamera;

    gl_Position = uProj * vec4(pos, 0.0, 1.0);
    switch(aType){
        case 0://air
            Color = vec3(0.0, 0.0, 0.0); //air
            break;
        case 1://solid
           Color = vec3(0.0863, 0.079, 0.046);
            break;
        case 2://sand
            Color = vec3(0.8863, 0.7922, 0.4627);
            break;
        case 3://water
            Color = vec3(0.15, 0.15, 0.45);
            break;
        case 4://gas
            Color = vec3(0.1, 0.1, 0.1);
            break;
        case 10:
            Color = vec3(0.15, 0.15, 0.15);
            break;
        default:
            Color = vec3(0.5, 0.5, 0.5);
            break;
    }

}