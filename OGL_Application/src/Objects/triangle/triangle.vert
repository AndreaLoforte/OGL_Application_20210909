#version 450 core
layout (location = 0) in vec4 triangle;
uniform mat4 transformMatrix;



void main(void)
{

   
	gl_Position = transformMatrix*triangle;
	
}