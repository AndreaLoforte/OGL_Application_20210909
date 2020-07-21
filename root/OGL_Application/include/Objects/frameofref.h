#ifndef FOR_OBJ
#define FOR_OBJ

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<physics.h>
namespace myobjectNS{

  class FrameOfRef :public ApplicationObject,public BaseObject{
    //GLuint VAO;
	  friend class myphysicsNS::CollisorePolimorfo;
   GLfloat length = 10.0f;
   
 public:
	 FrameOfRef(std::string sh_prog_name) :
		 ApplicationObject(sh_prog_name),
		 BaseObject(sh_prog_name){}

   void render(const fpcameraNS::Transformation&) override;
   void render();
   void setPosition(float, float, float);
   void create()override;
   FrameOfRef* getNewInstance()override { 
	   FrameOfRef *f(new FrameOfRef("frameOfRef"));
	   return f;

   }
 };


 






}//NS
#endif
