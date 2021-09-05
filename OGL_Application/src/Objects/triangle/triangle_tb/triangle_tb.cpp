#include<triangle/triangle_tb/triangle_tb.h>

namespace myobjectNS {


	void Triangle_tb::render(const fpcameraNS::Transformation& cam)
	{

		glUseProgram(shader_prog);
		static GLuint va_location = glGetAttribLocation(shader_prog, "triangle");
		static GLuint modelview_attrib_location = glGetUniformLocation(shader_prog, "modelviewMatrix");
		static GLuint AOTrMatrix_attrib_location = glGetUniformLocation(shader_prog, "AOTrMatrix");
		static GLuint sampler_location = glGetUniformLocation(shader_prog, "s");

		glBindVertexArray(triangle_vao);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnableVertexArrayAttrib(triangle_vao, va_location);
		
		glUniform1i(sampler_location, 0);
		glUniformMatrix4fv(modelview_attrib_location, 1, GL_FALSE, cam.getPlayerCamera());
		glUniformMatrix4fv(AOTrMatrix_attrib_location, 1, GL_FALSE, AOTrMatrix);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexArrayAttrib(triangle_vao, va_location);
		glBindVertexArray(-1);
	}

	void Triangle_tb::create() {

		setShaders();
		

		GLfloat x = 20.0f, y = 20.0f, z = 0.0;
		AOscale = 1 / AOscale;
		GLfloat triangle_vertex[] =
		{
		  x,0.0,z,AOscale,
		  -x,0.0,z,AOscale,
		  x,y,z,AOscale
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
		

		string stem = "/OGL_Application/textures/Crater_Cluster.png";
		stem = Application::application_root_dir.c_str() + stem;

		texture = SOIL_load_OGL_texture
		(
			stem.c_str(),
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



