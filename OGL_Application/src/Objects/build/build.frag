#version 450 core

out vec4 frag_color;
//uniform float counter;
layout (location = 0) uniform vec4 color;

void main(void){
	

	/*frag_color = vec4(cos(counter),sin(counter),cos(-counter),0.7);*/
	frag_color = color;
}
