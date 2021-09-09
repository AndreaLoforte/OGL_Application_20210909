#version 450 core

out vec4 frag_color;
in vec4 fcolor;

void main(){
	frag_color = fcolor;
};
