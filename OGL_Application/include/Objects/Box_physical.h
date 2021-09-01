#pragma once
#include<applicationDerivedObject.h>
#include<baseObject.h>
#include<physics.h>
#include<array>

namespace myobjectNS {

	class Box_physical final :public ObjectBox, public ShaderObject{
		const string className = "Box_physical";
		friend class myphysicsNS::CollisorePolimorfo;
		 GLuint VAO, buffer;
		static const  int N = 36;
		vmath::vec4 vertices[N];
		
	public:
		Box_physical(std::string sh_prog_name, GLfloat w = 5, GLfloat h = 10, GLfloat d = 8) :
			ObjectBox(sh_prog_name,w,h,d), ShaderObject(sh_prog_name) 
		{
			create();
		}

	

		void render(const fpcameraNS::Transformation&) override;
		/*questa funzione setta i parametri fisici*/
		void setPosition(const std::array<float,3>&);
		/*questa funzione setta la matrice per il disegno*/
		void setRigidBodyParameters();
		void setParameters()override;
		void create()override;
		void update(const float&)override;
		void reset()override {
			setRigidBodyParameters();
		}
		Box_physical* getNewInstance()override { 
			Box_physical *b(new Box_physical(className));
			return b; 
		}

		

	};






}//NS