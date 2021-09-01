#include<viewfinder.h>



namespace myobjectNS {


	void ViewFinder::render(const fpcameraNS::Transformation& cam)
	{

		glUseProgram(shader_prog);
		
		glUniformMatrix4fv(11, 1, GL_FALSE, cam.inverseM);
		glUniformMatrix4fv(10, 1, GL_FALSE, cam.getPlayerCamera());
		/*glUniform1f(11,length);*/
		glLineWidth(2);
		glDrawArrays(GL_LINES, 0, 4);


	}


	void ViewFinder::render()
	{

	}

	void ViewFinder::setPosition(float x, float y, float z) {

		/*  ShaderObject::offset[0] = x;
		  ShaderObject::offset[1] = y;
		  ShaderObject::offset[2] = z;
		  ShaderObject::offset[3] = 1.0;*/


	}
}

