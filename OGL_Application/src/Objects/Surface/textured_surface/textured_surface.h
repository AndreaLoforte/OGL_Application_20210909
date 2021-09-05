 #ifndef TX_SURFACE_OBJ
#define TX_SURFACE_OBJ

#include<shaderObject.h>
#include<applicationDerivedObject.h>
#include<physics.h>
#include<array>
#include<objectCollector.h>
class CollisionPlane;

namespace myobjectNS{

	class Tx_surface :public ObjectPlane, public ShaderObject{
		friend class myphysicsNS::CollisorePolimorfo;
		GLuint VAO, VBO;
		GLuint texture;
		string objectName = "Tx_surface";
		static unsigned instanceCounter;
		unsigned instanceNumber;

		
	public:
		Tx_surface(std::string sh_prog_name, GLfloat l = 100):
			ObjectPlane(sh_prog_name,100,0,100),
			ShaderObject(sh_prog_name,"surface/textured_surface/")
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
		Tx_surface* getNewInstance()override {
			Tx_surface*s(new Tx_surface("textured_surface"));
			return s; 
		}
		int getCollisorID() override { return AOCollisorID; }

	

	};
 






}//NS
#endif
