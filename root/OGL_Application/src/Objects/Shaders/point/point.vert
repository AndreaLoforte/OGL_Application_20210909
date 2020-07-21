#version 450 core

uniform mat4 transformMatrix;
in vec4 vertices;

void main(){


gl_Position = transformMatrix*(vertices);

};


