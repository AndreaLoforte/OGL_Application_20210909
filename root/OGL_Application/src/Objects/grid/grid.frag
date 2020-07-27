#version 450 core

out vec4 frag_color;
layout(location = 3) uniform vec4 color;
 
void main(){
//frag_color = vec4(0.1,1.0,0.1,.2);
	frag_color = color;
};
