#version 450 core
in vec2 TexCoords; //data from vertex

uniform int iteration_count_uniform;
uniform float char_advance; //fattore che va moltiplicato per circa 100000
uniform sampler2D textSampler;//data from openGL
uniform vec4 textColor;//data from openGL (colore da dare al testo)
uniform vec4 textFrameColor;
uniform float main_scale;
uniform vec2 xy_offset;
out vec4 color;


void main()
{    
	
	int y_shift = +1000; // + shift up
	//creo una coordinata che trasforma le coordinate del vertex array nelle coordinate dove la texture è non nulla.
	ivec2 vertCoordToTexCoord =
		ivec2((TexCoords.x + xy_offset.x - char_advance) * 10000 / main_scale,
			-(TexCoords.y + xy_offset.y)*10000 / main_scale + y_shift);
		
		ivec2 fragCoord = ivec2(vertCoordToTexCoord);

		/*font texture has a colored simbol on a black background.
		Therefore i can locate and change font color by "measuring" 
		where the texture color is <= (0.0,0.0,0.0,1.0) (Here is the background)
		and >= ... (here is the symbol)*/
		color = texelFetch(textSampler, fragCoord, 0);
		if (all(lessThanEqual(color, vec4(0.0, 0.0, 0.0, 1.0))))
			color = textFrameColor;
		else {

			//if (iteration_count_uniform == 0)
			color = textColor ;//vec4(.0, 1.0, 0.0, 1.0);
		/*	else
				color = textColor;*/
		}
	

}  