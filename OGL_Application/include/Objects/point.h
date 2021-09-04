#pragma once

#include<shaderObject.h>
#include<applicationDerivedObject.h>
namespace myobjectNS {

	class Point final :public ApplicationObject, public ShaderObject {
		GLuint VAO, buffer;

	public:
		Point(std::string sh_prog_name) :
			ApplicationObject(sh_prog_name),
			ShaderObject(sh_prog_name) {


		}

		void render(const fpcameraNS::Transformation&)override;
		void create()override;
		void update(const float&)override;
		Point* getNewInstance()override { return new Point("point"); }
	};






}//NS