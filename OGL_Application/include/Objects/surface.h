 #ifndef SURFACE_OBJ
#define SURFACE_OBJ

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<physics.h>
#include<array>
#include<objectCollector.h>
class CollisionPlane;

namespace myobjectNS{

	class Surface :public ObjectPlane, public BaseObject{
		friend class myphysicsNS::CollisorePolimorfo;
		GLuint VAO, VBO;
		string objectName = "Surface";
		static unsigned instanceCounter;
		unsigned instanceNumber;

		
	public:
		Surface(std::string sh_prog_name, GLfloat l = 100):
			ObjectPlane(sh_prog_name,100,0,100),
			BaseObject(sh_prog_name) 
		{

			CollisionFinitePlane::size[0] = l;
			CollisionFinitePlane::size[1] = 0;
			CollisionFinitePlane::size[2] = l;

			instanceNumber = instanceCounter++;
			body->RBobjectName = objectName;
			
		}



		void clean() {}
		void render(const fpcameraNS::Transformation&) override;
		void renderSurface();
		void renderCollisionPrimitive();
		void update(const float&) override;
		void setColor(float, float, float, float);
		void create()override;
		void AOsetShaders() override { setShaders(); }
		void setRigidBodyParameters();
		void setParameters()override;
		Surface* getNewInstance()override {
			Surface*s(new Surface("surface"));
			return s; 
		}
		int getCollisorID() override { return AOCollisorID; }

	

	};
 






}//NS
#endif
