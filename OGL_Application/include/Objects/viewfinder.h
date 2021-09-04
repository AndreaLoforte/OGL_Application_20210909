#ifndef VIEWFINDER_OBJ
#define VIEWFINDER_OBJ

#include<shaderObject.h>
#include<applicationDerivedObject.h>

namespace myobjectNS {

	class ViewFinder :public ApplicationObject, public ShaderObject {
		//GLuint VAO;

		GLfloat length = 10.0f;

	public:
		ViewFinder():ViewFinder("viewfinder"){}
		ViewFinder(std::string sh_prog_name) :
			ApplicationObject(sh_prog_name),
			ShaderObject(sh_prog_name) {}

		void render(const fpcameraNS::Transformation&) override;
		void render();
		void setPosition(float, float, float);
		ViewFinder* getNewInstance()override 
		{ 
			return new ViewFinder("viewfinder"); 
		}
		void create()override { setShaders(); }
	};









}//NS
#endif
