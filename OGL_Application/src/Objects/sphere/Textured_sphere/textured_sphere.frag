#version 450 core
uniform sampler2D s;
out vec4 color;

in VS_OUT
{
	vec2 tc;
}fs_in;

void main(void)
{

	
	//color = texelFetch(s,ivec2(gl_FragCoord.xy),0);
	color = texture(s,fs_in.tc);

}