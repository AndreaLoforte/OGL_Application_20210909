#pragma once
#include<applicationDerivedObject.h>
#include<baseObject.h>
#include<physics.h>
#include<text.h>
#include<array>

namespace myobjectNS {

	class BoxAABB final :public ObjectAABB, public BaseObject{
		friend class myphysicsNS::CollisorePolimorfo;
		 GLuint VAO, buffer;
		static const  int N = 36;
		vmath::vec4 vertices[N];
		
	public:
		BoxAABB(std::string sh_prog_name, GLfloat w = 5, GLfloat h = 10, GLfloat d = 8) :
			ObjectAABB(sh_prog_name,w,h,d), BaseObject(sh_prog_name) {}

	

		void render(const fpcameraNS::Transformation&) override;
		void setPosition(const std::array<float,3>&);
		void setRigidBodyParameters();
		void setParameters()override;
		void create()override;
		void update(const float&)override;
		void reset()override {
			setRigidBodyParameters();
		}
		BoxAABB* getNewInstance()override {
			BoxAABB *b(new BoxAABB("boxAABB"));
			return b; 
		}

		

	};






}//NS