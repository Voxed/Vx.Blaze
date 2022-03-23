#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 norm;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

out vec3 fNorm;

void main()
{
    gl_Position = projection*view*model*vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fNorm = (inverse(transpose(model))*vec4(norm, 1.0)).xyz;
}