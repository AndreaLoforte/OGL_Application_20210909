#version 450 core
//particle
layout (location = 10) uniform mat4 transformMatrix;
layout (location = 11) in vec4 point;
/* layout (location = 12) in vec4 movePoint; */

void main(){


const int N = 100; //numero di vertici per circonferenza
vec4 vertices;
float x,y,z;
float pi = 180.0;
float r = .5;
int i = 0;


 
//point = point + movePoint;
gl_Position = transformMatrix*point;


}

   
    
 
 
   
