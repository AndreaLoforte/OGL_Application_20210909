#version 450 core

out vec4 frag_color;

flat in int index;

void main() {
	const vec4 colors[6] =
		vec4[6](
			//asse x rosso
			vec4(1.0, 1.0, 0.0, 1.0),
			vec4(1.0, 1.0, 0.0, 1.0),
			//asse y verde
			vec4(0.0, 1.0, 1.0, 1.0),
			vec4(0.0, 1.0, 1.0, 1.0),
			//asse z blu
			vec4(1.0, 0.0, 1.0, 1.0),
			vec4(1.0, 0.0, 1.0, 1.0));



	frag_color = colors[index+2];
};
