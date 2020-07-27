#include<point.h>

namespace myobjectNS {


	void Point::render(const fpcameraNS::Transformation& cam)
	{

		glUseProgram(shader_prog);
		create();
		glUniformMatrix4fv(glGetUniformLocation(shader_prog, "transformMatrix"), 1, GL_FALSE, cam.getPlayerCamera());

		glPointSize(30);
		glDrawArrays(GL_POINTS, 0, 1);

	}

	void Point::create() {
	
		setShaders();
		GLfloat x = 0.0, y = 0.0, z = 0.0, scale = 1.0;
		const static GLfloat vertices[] =
		{
			x,y,z,scale
		};


		glCreateBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		/*glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices),
			vertices, GL_DYNAMIC_STORAGE_BIT);*/
		glNamedBufferStorage(buffer, sizeof(vertices), NULL, GL_DYNAMIC_STORAGE_BIT);

		static GLuint attribIndex = glGetAttribLocation(shader_prog, "vertices"),
			bindingIndex = 0, offset = 0, stride = sizeof(vertices), num_coord_per_vert = 4;

		glNamedBufferSubData(buffer, 0, sizeof(vertices), vertices);

		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glVertexArrayAttribBinding(VAO, attribIndex, bindingIndex);
		glVertexArrayVertexBuffer(VAO, bindingIndex, buffer, offset, sizeof(GLfloat));
		glVertexArrayAttribFormat(VAO, attribIndex, num_coord_per_vert, GL_FLOAT, GL_FALSE, 0);
		/*glEnableVertexAttribArray(attribIndex);*/
		glEnableVertexArrayAttrib(VAO, attribIndex);

	}



	void Point::update(const float & duration) {

	


	}


}



