#ifndef MYOBJECT
#define MYOBJECT
#include<physics.h>
#include<shaderObject.h>
#include<applicationDerivedObject.h>
#include<objectCollector.h>
#include<mymathlib.h>
namespace myobjectNS{

  class Box_nonPhysical final :public ApplicationObject, public ShaderObject{
	  /*friend class myphysicsNS::CollisorePolimorfo;*/
     
 public:
	 Box_nonPhysical(std::string sh_prog_name):
	  ApplicationObject(sh_prog_name),
	  ShaderObject(sh_prog_name){}
   
   void render(const fpcameraNS::Transformation&)override;
 
   void create() override { setShaders(); }
   Box_nonPhysical* getNewInstance()override {
	   Box_nonPhysical*b(new Box_nonPhysical("Box_nonPhysical"));
	   return b; 
   }

 };






}//NS
#endif
