#version 450 core

layout (location = 10) uniform mat4 transformMatrix;

void main(){

	float w = 10.0f, h = 60.0f, b = 0.0f, s =1.0f;
	const int N = 36;
	const vec4 vertices[N] =
	vec4[N](
	//square base
	vec4(-w,b,w,s),
	vec4(w,b,w,s),
	vec4(-w,b,-w,s),
	vec4(w,b,w,s),
	vec4(w,b,-w,s),
	vec4(-w,b,-w,s),
	//wquare top
	vec4(-w,h,w,s),
	vec4(w,h,w,s),
	vec4(-w,h,-w,s),
	vec4(w,h,w,s),
	vec4(w,h,-w,s),
	vec4(-w,h,-w,s),
	//back side
	vec4(w,h,-w,s),
	vec4(-w,h,-w,s),
	vec4(-w,b,-w,s),
	vec4(-w,b,-w,s),
	vec4(w,b,-w,s),
	vec4(w,h,-w,s),
	//front side
	vec4(w,h,w,s),
	vec4(-w,h,w,s),
	vec4(-w,b,w,s),
	vec4(-w,b,w,s),
	vec4(w,b,w,s),
	vec4(w,h,w,s),
	//right side
	vec4(-w,h,w,s),
	vec4(-w,h,-w,s),
	vec4(-w,b,w,s),
	vec4(-w,b,w,s),
	vec4(-w,b,-w,s),
	vec4(-w,h,-w,s),
	//left side
	vec4(w,h,w,s),
	vec4(w,h,-w,s),
	vec4(w,b,w,s),
	vec4(w,b,w,s),
	vec4(w,b,-w,s),
	vec4(w,h,-w,s)	
);

gl_Position = transformMatrix*vertices[gl_VertexID];

};



