#ifndef FOR_OBJ
#define FOR_OBJ

#include<shaderObject.h>
#include<applicationDerivedObject.h>
#include<physics.h>
#include<objectCollector.h>
namespace myobjectNS{


	/*perchè FrameOFRef dovrebbe essere un oggetto sferico?
	Non lo è! mi serve appioppargli la fisica per poterlo spostare
	come tutti gli altri oggetti. Lo assimilo quindi ad una sfera minuscola
	centrata nell'origine degli assi*/
  class FrameOfRef :public ApplicationObject, public ShaderObject{
	  friend class myphysicsNS::CollisorePolimorfo;
	  float length = 10.0f;
   
 public:
	 FrameOfRef(std::string sh_prog_name = "frameOfRef") :
		 ApplicationObject(sh_prog_name),
		 ShaderObject(sh_prog_name)
	 {
		 create();
	 }

   void render(const fpcameraNS::Transformation&) override;
   //void setParameters();
   void create()override;
   FrameOfRef* getNewInstance();
   
 };


  class FrameOfRefOC : public collectorNS::ApplicationObjectCollector {

	  collectorNS::AOcontainer frofr_container;
	  FrameOfRef frofr;
  public:
	  FrameOfRefOC(const string& collName);
	  FrameOfRefOC(const string& collName, const unsigned& collNumber);

	  FrameOfRefOC* OCgetNewInstance() override;
	  FrameOfRefOC* OCloadInstance(const unsigned& collNumber) override;
	  void OCcreateObject() override;

 };






}//NS
#endif
