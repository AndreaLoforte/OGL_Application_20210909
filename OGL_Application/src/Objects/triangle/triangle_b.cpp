#include<triangle_b.h>

namespace myobjectNS {


	void Triangle::render(const fpcameraNS::Transformation& cam)
	{
		
		
		//glUseProgram(shader_prog);
		//glBindVertexArray(triangle_vao);//necessary at each render call
		//glEnableVertexArrayAttrib(triangle_vao, vai);//necessary at each render call
		//static GLuint transformMatrix_location = glGetUniformLocation(shader_prog, "transformMatrix");
		//glUniformMatrix4fv(transformMatrix_location, 1, GL_FALSE, cam.getPlayerCamera());
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		////glDisableVertexArrayAttrib(triangle_vao, vai);
		//glBindVertexArray(0);
	}

	void Triangle::update(const float & duration) {}

	void Triangle::create() {

		setShaders();


		GLfloat x = 3.0f, y = 3.0f, z = 0, scale = 1.0;
		static GLfloat triangle_vertex[] =
		{
		  x,0.0,z,scale,
		  -x,0.0,z,scale,
		  x,y,z,scale
		};

		glCreateBuffers(1, &triangle_buffer);
		//dico a openGL che sto creando un buffer per vertex data
		glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
		//alloco la memoria nel buffer
		glNamedBufferStorage(triangle_buffer, sizeof(triangle_vertex), triangle_vertex, GL_DYNAMIC_STORAGE_BIT);
		//metto dati in buffer
		//glNamedBufferSubData(triangle_buffer, 0, sizeof(triangle_vertex), triangle_vertex);

		//////////////////////////triangle_vao
		
		glCreateVertexArrays(1, &triangle_vao);
		//lego vao al va
		glVertexArrayAttribBinding(triangle_vao, vai, vbbi);

		//lego il buffer al vbbi
		glVertexArrayVertexBuffer(triangle_vao, vbbi, triangle_buffer, 0, sizeof(GLfloat)*4);
		glVertexArrayAttribFormat(triangle_vao, vai, 4, GL_FLOAT, GL_FALSE, 0);
	
	}



}



