 #version 450 core
 //sphere
uniform mat4 transformMatrix;
uniform mat4 physics_transformation;
layout (location = 2) in vec4 vcolor;
out vec4 fcolor;
in vec4 sphere;


void main(){

	fcolor = vcolor;
	gl_Position = transformMatrix * physics_transformation*sphere;



	


}

   
