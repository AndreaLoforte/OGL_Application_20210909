#version 450 core
//gun_for
layout(location = 10) uniform mat4 modelview_tr;
layout(location = 11) uniform mat4 offset_tr;


flat out int index;

void main() {

	float l = .02;

	const vec4 vertices[4] = vec4[4](
		//asse x
		vec4(-l, 0.0, 0.0, 1.0),
		vec4(l, 0.0, 0.0, 1.0),
		//asse y
		vec4(0.0, -l, 0.0, 1.0),
		vec4(0.0, l, 0.0, 1.0)
		//asse z
		);

	index = gl_VertexID;

	gl_Position = vertices[gl_VertexID];

}