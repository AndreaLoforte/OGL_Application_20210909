#include<frameofref.h>



namespace myobjectNS{


  void FrameOfRef::render(const fpcameraNS::Transformation& cam)
  {
	 
	  glBindVertexArray(VAO);
	  glUseProgram(shader_prog);
	  

	  static GLuint modelviewMAttribLocation = glGetUniformLocation(shader_prog, "modelviewM");
	  glUniformMatrix4fv(modelviewMAttribLocation, 1, GL_FALSE, cam.getPlayerCamera());

	  static GLuint transfMAttribLocation = glGetUniformLocation(shader_prog, "transfM");
	  glUniformMatrix4fv(transfMAttribLocation, 1, GL_FALSE, AOTrMatrix);

	  /*glUniform1f(11,length);*/
	  glLineWidth(5);
	  glDrawArrays(GL_LINES, 0, 6);
	  glBindVertexArray(-1);


  }

  void FrameOfRef::create() {

	 setShaders();
	 glCreateVertexArrays(1, &VAO);
  }

 /* void FrameOfRef::setParameters() {

	  body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
	  body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
	  body->_calculateTransformMatrix(body->transformMatrix, body->position, body->orientation);
	  body->getGLTransform(AOTrMatrix);
  }*/



  FrameOfRef* FrameOfRef::getNewInstance() {
	  FrameOfRef *f(new FrameOfRef("frameOfRef"));
	  return f;

  }




  /*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

  FrameOfRefOC::FrameOfRefOC(const string& collName) :
	  ApplicationObjectCollector(collName, ApplicationObjectCollector::collectorCounter++, &frofr_container)
  {
	  frofr_container.push_back(&frofr);
	  //Ground::addSurface(this);
  }

  FrameOfRefOC::FrameOfRefOC(const string& collName, const unsigned& collNumber) :
	  ApplicationObjectCollector(collName, collNumber, &frofr_container)
  {
	  frofr_container.push_back(&frofr);
	  //Ground::addSurface(this);
  }


  FrameOfRefOC* FrameOfRefOC::OCgetNewInstance()
  {
	  FrameOfRefOC* coll{ new FrameOfRefOC("FrameOfRef") };
	  return coll;

  }

  FrameOfRefOC* FrameOfRefOC::OCloadInstance(const unsigned& collNumber)
  {
	  FrameOfRefOC* coll{ new FrameOfRefOC("FrameOfRef", collNumber) };
	  return coll;

  }


  void FrameOfRefOC::OCcreateObject()
  {
	  //Ground::addSurface(this);
	  frofr.create();
  }







}

