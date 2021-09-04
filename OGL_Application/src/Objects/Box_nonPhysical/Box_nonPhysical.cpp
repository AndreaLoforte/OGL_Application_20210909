#include<Box_nonPhysical.h>


namespace myobjectNS {


	void Box_nonPhysical::render(const fpcameraNS::Transformation& cam)
	{
		glUseProgram(shader_prog);
		glBindVertexArray(VAO);

		GLuint modelviewT_attrib_loc = glGetUniformLocation(shader_prog, "modelviewT");
		GLuint AOTrMatrix_attrib_loc = glGetUniformLocation(shader_prog, "AOTrMatrix");


		glUniform4fv(0, 1, AOcolor);
		glUniformMatrix4fv(AOTrMatrix_attrib_loc, 1, GL_FALSE, AOTrMatrix);
		glUniformMatrix4fv(modelviewT_attrib_loc, 1, GL_FALSE, cam.getPlayerCamera());


		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(-1);//unbind current vao



	}

	

}
 


