#version 450 core
//grid
layout(location = 10) uniform mat4 modelViewMatrix;
layout(location = 0) uniform mat4 transformMatrix;
layout(location = 1) uniform float len1;
layout(location = 2) uniform float len2;

flat out int index;

void main() {

	float L = len1; // 100.0f;
	float L2 = len2;// 200.0f;
	float l = len1/2; // 100.0f;
	float l2 = len2/ 2;// 200.0f;

	const vec4 vertices[40] = vec4[40](
		vec4(-L, 0.0f, L2, 1.0f),
		vec4(-L, 0.0f, -L2, 1.0f),
		vec4(0.0f, 0.0f, L2, 1.0f),
		vec4(0.0f, 0.0f, -L2, 1.0f),
		vec4(L, 0.0f, L2, 1.0f),
		vec4(L, 0.0f, -L2, 1.0f),
		vec4(-l, 0.0f, L2, 1.0f),
		vec4(-l, 0.0f, -L2, 1.0f),
		vec4(l, 0.0f, -L2, 1.0f),
		vec4(l, 0.0f, L2, 1.0f),
		////////////////////////
		vec4(-L, 0.0f, L2, 1.0f),
		vec4(L, 0.0f, L2, 1.0f),
		vec4(-L, 0.0f, 0.0f, 1.0f),
		vec4(L, 0.0f, 0.0f, 1.0f),
		vec4(-L, 0.0f, -L2, 1.0f),
		vec4(L, 0.0f, -L2, 1.0f),
		vec4(-L, 0.0f, -l2, 1.0f),
		vec4(L, 0.0f, -l2, 1.0f),
		vec4(-L, 0.0f, l2, 1.0f),
		vec4(L, 0.0f, l2, 1.0f),
		//////////////QUADRATO PIU AMIO/////////////////////////
		vec4(-L2, 0.0f, L2, 1.0f),
		vec4(-L2, 0.0f, -L2, 1.0f),
		vec4(0.0f, 0.0f, L2, 1.0f),
		vec4(0.0f, 0.0f, -L2, 1.0f),
		vec4(L2, 0.0f, L2, 1.0f),
		vec4(L2, 0.0f, -L2, 1.0f),
		vec4(-l2, 0.0f, L2, 1.0f),
		vec4(-l2, 0.0f, -L2, 1.0f),
		vec4(l2, 0.0f, -L2, 1.0f),
		vec4(l2, 0.0f, L2, 1.0f),
		////////////////////////
		vec4(-L2, 0.0f, L2, 1.0f),
		vec4(L2, 0.0f, L2, 1.0f),
		vec4(-L2, 0.0f, 0.0f, 1.0f),
		vec4(L2, 0.0f, 0.0f, 1.0f),
		vec4(-L2, 0.0f, -L2, 1.0f),
		vec4(L2, 0.0f, -L2, 1.0f),
		vec4(-L2, 0.0f, -l2, 1.0f),
		vec4(L2, 0.0f, -l2, 1.0f),
		vec4(-L2, 0.0f, l2, 1.0f),
		vec4(L2, 0.0f, l2, 1.0f)
		);


	index = gl_VertexID;
	gl_Position =  modelViewMatrix * transformMatrix* vertices[gl_VertexID];
}