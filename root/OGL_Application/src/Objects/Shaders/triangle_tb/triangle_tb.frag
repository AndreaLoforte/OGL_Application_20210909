#version 450 core
uniform sampler2D s;
out vec4 color;

in vec2 tex_coords;

void main(void)
{

	
	//color = texelFetch(s,ivec2(gl_FragCoord.xy),0);
	color = texture(s,tex_coords*0.1);

}