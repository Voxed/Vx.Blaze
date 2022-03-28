#version 420
// This vertex shader simply outputs the input coordinates to the rasterizer. It only uses 2D coordinates.
layout(location = 0) in vec3 POSITION;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(POSITION, 1.0);
	texCoord = 0.5 * (POSITION.xy + vec2(1,1));
}