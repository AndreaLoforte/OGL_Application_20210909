#version 450 core
in vec4 vertices;
uniform mat4 modelviewT;
uniform mat4 physicsT;



void main(void){

 gl_Position = modelviewT* physicsT*vertices;
}

