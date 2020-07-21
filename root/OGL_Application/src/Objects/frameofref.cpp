#include<frameofref.h>



namespace myobjectNS{


  void FrameOfRef::render(const fpcameraNS::Transformation& cam)
  {
	  
    glUseProgram(shader_prog);
    glUniformMatrix4fv(10,1,GL_FALSE,cam.getPlayerCamera());
    /*glUniform1f(11,length);*/
	glLineWidth(5);
    glDrawArrays(GL_LINES,0,6);
	
	
  }


  void FrameOfRef::render()
  {

  }

  void FrameOfRef::create() {

	 setShaders();
  }


  void FrameOfRef::setPosition(float x, float y, float z) {

	/*  BaseObject::offset[0] = x;
	  BaseObject::offset[1] = y;
	  BaseObject::offset[2] = z;
	  BaseObject::offset[3] = 1.0;*/
	  

  }
}

