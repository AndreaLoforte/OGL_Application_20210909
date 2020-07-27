#version 450 core
layout (location = 0) in vec4 triangle;
uniform mat4 transformMatrix;

out vec2 tex_coords;

void main(void)
{
	//tex_coords = (transformMatrix*triangle).xy;
	
	gl_Position = transformMatrix*triangle;
	tex_coords = triangle.xy;
}