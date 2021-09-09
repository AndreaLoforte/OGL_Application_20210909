 #version 450 core
 //sphere
uniform mat4 modelviewMatrix;
uniform mat4 AOTrMatrix;
layout (location = 2) in vec4 vcolor;
//out vec4 fcolor;
in vec4 sphere;

out VS_OUT
{
	vec2 tc;
}vs_out;


void main(){

	

	vs_out.tc = vec2(sphere.x/10,sphere.y/10);
	gl_Position = modelviewMatrix * AOTrMatrix*sphere;
	


	


}

   
