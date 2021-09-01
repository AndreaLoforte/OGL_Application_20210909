#ifndef MYOBJECT
#define MYOBJECT
#include<physics.h>
#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<objectCollector.h>
namespace myobjectNS{

  class Build final :public ApplicationObject, public ShaderObject{
	  friend class myphysicsNS::CollisorePolimorfo;
     
 public:
  Build(std::string sh_prog_name):
	  ApplicationObject(sh_prog_name),
	  ShaderObject(sh_prog_name){}
   
   void render(const fpcameraNS::Transformation&)override;
   void create() override { setShaders(); }
   Build* getNewInstance()override {
	   Build *b(new Build("object1"));
	   return b; 
   }

 };






}//NS
#endif
