#pragma once
#include<applicationDerivedObject.h>
#include<baseObject.h>
#include<physics.h>
#include<array>

namespace myobjectNS {

	class Build_b final :public ObjectBox, public BaseObject{
		friend class myphysicsNS::CollisorePolimorfo;
		 GLuint VAO, buffer;
		static const  int N = 36;
		vmath::vec4 vertices[N];
		
	public:
		Build_b(std::string sh_prog_name, GLfloat w = 5, GLfloat h = 10, GLfloat d = 8) :
			ObjectBox(sh_prog_name,w,h,d), BaseObject(sh_prog_name) {}

	

		void render(const fpcameraNS::Transformation&) override;
		void setPosition(const std::array<float,3>&);
		void setRigidBodyParameters();
		void setParameters()override;
		void create()override;
		void update(const float&)override;
		void reset()override {
			setRigidBodyParameters();
		}
		Build_b* getNewInstance()override { 
			Build_b *b(new Build_b("build"));
			return b; 
		}

		

	};






}//NS