#version 450 core
layout (location = 0) in vec4 triangle;
uniform mat4 modelviewMatrix;
uniform mat4 AOTrMatrix;

out vec2 tex_coords;

void main(void)
{
	//tex_coords = (modelviewMatrix*triangle).xy;
	
	gl_Position = modelviewMatrix*AOTrMatrix*triangle;
	tex_coords = triangle.xy;
}