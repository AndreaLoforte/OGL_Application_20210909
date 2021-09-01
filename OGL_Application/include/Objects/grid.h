 #ifndef GROUND_OBJ
#define GROUND_OBJ

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<physics.h>
#include<objectCollector.h>
class CollisionPlane;

namespace myobjectNS{

	class Grid final :public ObjectPlane, public ShaderObject {
		friend class myphysicsNS::CollisorePolimorfo;
		static unsigned instanceCounter;
		GLuint groundTex;
		//GLuint VAO;
	public:
		Grid(std::string sh_prog_name):
			ObjectPlane(sh_prog_name,100,0,100),
			ShaderObject(sh_prog_name){

			instanceNumber = instanceCounter++;
			body->RBobjectName = sh_prog_name;
		
			create();
		}
		void clean() {}
		void create()override;
		void AOsetShaders()override { setShaders(); }
		void render(const fpcameraNS::Transformation&) override;
		//Ground* getClassTypePointer()override { return this; }
		void render();
		void setPosition(float, float, float);
		void setParameters() override;
		void setRigidBodyParameters();
		Grid* getNewInstance()override
		{ 
			Grid *newInstance(new Grid(shader_prog_name));
			newInstance->AOinstanceNumber = instanceCounter;
			instanceCounter++;
			return newInstance;
			
		}
		int getCollisorID() override { return AOCollisorID; }
	};
 






}//NS
#endif
