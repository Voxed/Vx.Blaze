#version 440 core
layout (location = 0) in vec3 POSITION;
layout (location = 1) in vec3 NORMAL;

layout (location = 0) uniform mat4 PROJECTION;
layout (location = 1) uniform mat4 VIEW;
layout (location = 2) uniform mat4 MODEL;

out vec3 fNorm;
out vec3 wNorm;
out vec3 fPos;

void main()
{
    gl_Position = PROJECTION*VIEW*MODEL*vec4(POSITION.x, POSITION.y, POSITION.z, 1.0);
    fNorm = normalize((inverse(transpose(VIEW*MODEL))*vec4(NORMAL, 1.0)).xyz);
    wNorm = normalize((inverse(transpose(MODEL))*vec4(NORMAL, 1.0)).xyz);
    fPos = (VIEW*MODEL*vec4(POSITION, 1.0)).xyz;
}