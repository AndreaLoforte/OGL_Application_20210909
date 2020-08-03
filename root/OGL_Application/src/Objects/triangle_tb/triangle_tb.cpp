#include<triangle_tb.h>

namespace myobjectNS {


	void Triangle_tb::render(fpcameraNS::Transformation& cam)
	{

		glUseProgram(shader_prog);
		static GLuint va_location = glGetAttribLocation(shader_prog, "triangle");
		static GLuint transformMatrix_Location = glGetUniformLocation(shader_prog, "transformMatrix");
		static GLuint sampler_location = glGetUniformLocation(shader_prog, "s");

		glBindVertexArray(triangle_vao);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnableVertexArrayAttrib(triangle_vao, va_location);
		
		glUniform1i(sampler_location, 0);
		glUniformMatrix4fv(transformMatrix_Location, 1, GL_FALSE, cam.getPlayerCamera());
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexArrayAttrib(triangle_vao, va_location);

	}

	void Triangle_tb::create() {

		setShaders();
		

		GLfloat x = 20.0f, y = 20.0f, z = 5.0, scale = 1.0;
		static GLfloat triangle_vertex[] =
		{
		  x,0.0,z,scale,
		  -x,0.0,z,scale,
		  x,y,z,scale
		};

		glCreateBuffers(1, &triangle_buffer);
		//alloco la memoria e inserisco i dati nel buffer
		glNamedBufferStorage(triangle_buffer, sizeof(triangle_vertex), triangle_vertex, GL_DYNAMIC_STORAGE_BIT);
		
		///////////SETTING UP VERTEX ARRAY OBJECT
		glCreateVertexArrays(1, &triangle_vao);
		glVertexArrayAttribBinding(triangle_vao, vai, vbbi);
		glVertexArrayVertexBuffer(triangle_vao, vbbi, triangle_buffer, 0, sizeof(vmath::vec4));
		glVertexArrayAttribFormat(triangle_vao, vai, 4 /*elements per vertice*/, GL_FLOAT, GL_FALSE, 0 /*relative offset*/);
		

		/////////SETTING UP TEXTURE
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		glTextureStorage2D(texture, 1, GL_RGBA32F, 256, 256);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		texture = SOIL_load_OGL_texture
		(
			"C:/Users/lofor/Source/Repos/OGL_Application-master/root/OGL_Application/Textures/2016-12-24-PHOTO-00003910.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
			
		

		/* check for an error during the load process */
		if (0 == texture)
		{
			printf("SOIL loading error: '%s'/n", SOIL_last_result());
		}


	}



}



