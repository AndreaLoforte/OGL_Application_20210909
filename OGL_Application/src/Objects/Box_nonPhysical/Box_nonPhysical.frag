#version 450 core

out vec4 frag_color;
//uniform float counter;
layout (location = 0) uniform vec4 color;
 
void main(){
frag_color = color;
};
