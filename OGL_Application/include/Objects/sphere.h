#ifndef SPHERE_OBJ
#define SPHERE_OBJ

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<assert.h>
#include<physics.h>
#include<objectCollector.h>
namespace myobjectNS {

	class Sphere final :public ObjectSphere, public ShaderObject{
		friend class myphysicsNS::CollisorePolimorfo;
		GLuint VAO, VBO;
		static int instanceCounter;
		/*static constexpr GLuint puntiSfera = 5000;*/
		static constexpr GLuint N = 100, M = 50;/* 0.3*puntiSfera;*/
		GLfloat sphere[M][N][4];
		static constexpr GLfloat theta_stride = 360 / N;// 2 * 3.1415926535 / N;
		static constexpr GLfloat phi_stride = 360 / M;// 2 * 3.1415926535 / M;

	public:
		Sphere(std::string sh_prog_name) :
			ObjectSphere(sh_prog_name),
			ShaderObject(sh_prog_name) {
			
			//body = new RigidBody();
		}
		~Sphere() {

		}
		void clean() {}
		void update(const float&) override;
		
		void create()override;
		void render(const fpcameraNS::Transformation&) override;
		void render();
		void setRigidBodyParameters();
		void reset() override {
			setRigidBodyParameters();
		}
		//Sphere* getClassTypePointer()override { return this; }
		void setParameters() override;
		Sphere* getNewInstance() override { 
			instanceCounter++;
			Sphere *s(new Sphere("sphere"));
			s->AOinstanceNumber = instanceCounter;
			return s; 
		}



	};







}//NS
#endif
