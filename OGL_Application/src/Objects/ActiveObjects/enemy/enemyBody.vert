 #version 450 core
 //sphere
uniform mat4 modelView_Matrix;
uniform mat4 AOTrMatrix;
layout (location = 2) in vec4 vcolor;
out vec4 fcolor;
in vec4 sphere;


void main(){

	fcolor = vcolor;
	gl_Position = modelView_Matrix * AOTrMatrix*sphere;



	


}

   
