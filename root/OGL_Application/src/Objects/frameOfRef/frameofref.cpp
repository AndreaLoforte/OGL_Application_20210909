#include<frameofref.h>



namespace myobjectNS{


  void FrameOfRef::render(const fpcameraNS::Transformation& cam)
  {
	 
	  glBindVertexArray(VAO);
	  glUseProgram(shader_prog);
	  glUniformMatrix4fv(10, 1, GL_FALSE, cam.getPlayerCamera());
	  /*glUniform1f(11,length);*/
	  glLineWidth(5);
	  glDrawArrays(GL_LINES, 0, 6);
	  glBindVertexArray(-1);


  }

  void FrameOfRef::create() {

	 setShaders();
	 glCreateVertexArrays(1, &VAO);
  }


  void FrameOfRef::setPosition(float x, float y, float z) {

	/*  BaseObject::offset[0] = x;
	  BaseObject::offset[1] = y;
	  BaseObject::offset[2] = z;
	  BaseObject::offset[3] = 1.0;*/
	  

  }

  FrameOfRef* FrameOfRef::getNewInstance() {
	  FrameOfRef *f(new FrameOfRef("frameOfRef"));
	  return f;

  }

}

