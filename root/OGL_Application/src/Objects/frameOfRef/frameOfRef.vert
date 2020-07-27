#version 450 core
//frameofref
layout (location = 10) uniform mat4 transformMatrix;
//layout (location = 11) uniform float length_;

flat out int index;

void main(){

    float l = 10.0f; //length_;

     const vec4 vertices[6] = vec4[6](
                //asse x
     	   	    vec4(0.0,0.0,0.0,1.0),
		        vec4(l,0.0,0.0,1.0),
                    //asse y
                vec4(0.0,0.0,0.0,1.0),
                vec4(0.0,l,0.0,1.0),
                        //asse z
                vec4(0.0,0.0,0.0,1.0),
                vec4(0.0,0.0,l,1.0));


			   index = gl_VertexID;
     gl_Position = transformMatrix*vertices[gl_VertexID];
	 
}