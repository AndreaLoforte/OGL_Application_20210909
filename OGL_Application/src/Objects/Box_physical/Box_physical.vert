#version 450 core
in vec4 vertices;
uniform mat4 modelviewT;
uniform mat4 AOTrMatrix;



void main(void){

 gl_Position = modelviewT* AOTrMatrix*vertices;
}

