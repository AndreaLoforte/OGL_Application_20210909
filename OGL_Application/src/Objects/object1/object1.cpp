#include<object1.h>


namespace myobjectNS {


	void Build::render(const fpcameraNS::Transformation& cam)
	{

		glUseProgram(shader_prog);
		
		glUniformMatrix4fv(10, 1, GL_FALSE, cam.getPlayerCamera());
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

	

}
 


