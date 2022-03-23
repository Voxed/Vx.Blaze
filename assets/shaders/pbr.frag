#version 440 core
out vec4 FragColor;

in vec3 fNorm;

void main()
{
    FragColor = vec4(fNorm, 1.0f);
}
