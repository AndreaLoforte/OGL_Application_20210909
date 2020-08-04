#version 450 core
//projectile
layout (location = 1) uniform mat4 transformMatrix;
layout (location = 2) uniform mat4 physics_transformation_matrix;
layout (location = 3) in float radius;
void main(){

const int N = 100;
vec4 vertices;
float pi = 180.0;
float r = radius;
int i = 0;
float theta = 2*pi/N*gl_VertexID;

vertices.x = r*cos(theta);
vertices.y = r*sin(theta);
vertices.z = 0.0;
vertices.w = 1.0;

for(int M = 0; M < 7; M++){
    //con 7 iterazioni (M<7) ottengo un giro completo di circonferenze equidistribuite nello spazio.
		if(gl_VertexID >= M*N && gl_VertexID <= (M+1)*N){
			float x_angle = M*pi/N;
			mat4 rotation = 
			mat4(vec4(1.0,0.0,0.0,0.0),
				vec4(0.0,cos(x_angle),-sin(x_angle),0.0),
				vec4(0.0,sin(x_angle),cos(x_angle),0.0),
				vec4(0.0,0.0,0.0,1.0)); 
					
				vertices = vertices*rotation;

			  gl_Position = transformMatrix*physics_transformation_matrix*vertices;
				
		}
} 



}

   
