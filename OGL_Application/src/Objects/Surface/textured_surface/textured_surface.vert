#version 450 core
//ground
in vec4 vertices;
uniform mat4 modelviewM;
uniform mat4 transfM;
//uniform mat4 physicsT;

out vec2 tex_coords;

void main(){



	/*index = gl_VertexID;*/
	gl_Position = modelviewM * transfM* vertices;


//float L = 100.0f;
//float L2 = 200.0f;
//float l = 100.0f;
//float l2 = 200.0f;
//float h1 = 100.0f;
//
//     const vec4 vertices[80] = vec4[80](
//         vec4(-L,0.0f,L,1.0f),
//        vec4(-L,0.0f,-L,1.0f),
//        vec4(0.0f,0.0f,L,1.0f),
//        vec4(0.0f,0.0f,-L,1.0f),
//        vec4(L,0.0f,L,1.0f),
//        vec4(L,0.0f,-L,1.0f),
//        vec4(-l,0.0f,L,1.0f),
//        vec4(-l,0.0f,-L,1.0f),
//        vec4(l,0.0f,-L,1.0f),
//        vec4(l,0.0f,L,1.0f),
//        ////////////////////////
//        vec4(-L,0.0f,L,1.0f),
//        vec4(L,0.0f,L,1.0f),
//        vec4(-L,0.0f,0.0f,1.0f),
//        vec4(L,0.0f,0.0f,1.0f),
//        vec4(-L,0.0f,-L,1.0f),
//        vec4(L,0.0f,-L,1.0f),
//        vec4(-L,0.0f,-l,1.0f),
//        vec4(L,0.0f,-l,1.0f),
//        vec4(-L,0.0f,l,1.0f),
//        vec4(L,0.0f,l,1.0f),
//		 ////////////////*2° PIANO////////////////
//		 vec4(-L, h1, L, 1.0f),
//		 vec4(-L, h1, -L, 1.0f),
//		 vec4(0.0f, h1, L, 1.0f),
//		 vec4(0.0f, h1, -L, 1.0f),
//		 vec4(L, h1, L, 1.0f),
//		 vec4(L, h1, -L, 1.0f),
//		 vec4(-l, h1, L, 1.0f),
//		 vec4(-l, h1, -L, 1.0f),
//		 vec4(l, h1, -L, 1.0f),
//		 vec4(l, h1, L, 1.0f),
//		 ////////////////////////
//		 vec4(-L, h1, L, 1.0f),
//		 vec4(L, h1, L, 1.0f),
//		 vec4(-L, h1, 0.0f, 1.0f),
//		 vec4(L, h1, 0.0f, 1.0f),
//		 vec4(-L, h1, -L, 1.0f),
//		 vec4(L, h1, -L, 1.0f),
//		 vec4(-L, h1, -l, 1.0f),
//		 vec4(L, h1, -l, 1.0f),
//		 vec4(-L, h1, l, 1.0f),
//		 vec4(L, h1, l, 1.0f),
//		 //////////////QUADRATO PIU AMIO/////////////////////////
//		 vec4(-L2, 0.0f, L2, 1.0f),
//		 vec4(-L2, 0.0f, -L2, 1.0f),
//		 vec4(0.0f, 0.0f, L2, 1.0f),
//		 vec4(0.0f, 0.0f, -L2, 1.0f),
//		 vec4(L2, 0.0f, L2, 1.0f),
//		 vec4(L2, 0.0f, -L2, 1.0f),
//		 vec4(-l2, 0.0f, L2, 1.0f),
//		 vec4(-l2, 0.0f, -L2, 1.0f),
//		 vec4(l2, 0.0f, -L2, 1.0f),
//		 vec4(l2, 0.0f, L2, 1.0f),
//		 ////////////////////////
//		 vec4(-L2, 0.0f, L2, 1.0f),
//		 vec4(L2, 0.0f, L2, 1.0f),
//		 vec4(-L2, 0.0f, 0.0f, 1.0f),
//		 vec4(L2, 0.0f, 0.0f, 1.0f),
//		 vec4(-L2, 0.0f, -L2, 1.0f),
//		 vec4(L2, 0.0f, -L2, 1.0f),
//		 vec4(-L2, 0.0f, -l2, 1.0f),
//		 vec4(L2, 0.0f, -l2, 1.0f),
//		 vec4(-L2, 0.0f, l2, 1.0f),
//		 vec4(L2, 0.0f, l2, 1.0f),
//		 ////////////////*2° PIANO////////////////
//		 vec4(-L2, h1, L2, 1.0f),
//		 vec4(-L2, h1, -L2, 1.0f),
//		 vec4(0.0f, h1, L2, 1.0f),
//		 vec4(0.0f, h1, -L2, 1.0f),
//		 vec4(L2, h1, L2, 1.0f),
//		 vec4(L2, h1, -L2, 1.0f),
//		 vec4(-l2, h1, L2, 1.0f),
//		 vec4(-l2, h1, -L2, 1.0f),
//		 vec4(l2, h1, -L2, 1.0f),
//		 vec4(l2, h1, L2, 1.0f),
//		 ////////////////////////
//		 vec4(-L2, h1, L2, 1.0f),
//		 vec4(L2, h1, L2, 1.0f),
//		 vec4(-L2, h1, 0.0f, 1.0f),
//		 vec4(L2, h1, 0.0f, 1.0f),
//		 vec4(-L2, h1, -L2, 1.0f),
//		 vec4(L2, h1, -L2, 1.0f),
//		 vec4(-L2, h1, -l2, 1.0f),
//		 vec4(L2, h1, -l2, 1.0f),
//		 vec4(-L2, h1, l2, 1.0f),
//		 vec4(L2, h1, l2, 1.0f)
//        );
//

			
}