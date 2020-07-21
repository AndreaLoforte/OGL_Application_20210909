#version 450 core
in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords; //data from openGL


void main()
{
   
	gl_Position = vertex;
	TexCoords = vertex.xy;

} 