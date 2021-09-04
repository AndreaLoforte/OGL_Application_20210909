#ifndef TEXTURED_BUFFERED_TRIANGLE_OBJ
#define TEXTURED_BUFFERED_TRIANGLE_OBJ

#include<shaderObject.h>
#include<applicationDerivedObject.h>
#include<assert.h>
#include<objectCollector.h>

namespace myobjectNS {

	class Triangle_tb final :public ApplicationObject, public ShaderObject {
		GLuint triangle_vao;
		GLuint triangle_buffer;
		GLuint texture;
		const unsigned vai = 0;
		const int vbbi = 0;
	public:
		Triangle_tb(std::string sh_prog_name) :
			ApplicationObject(sh_prog_name),
			ShaderObject(sh_prog_name) {

		}
		~Triangle_tb() {

		}
		void clean() {}
		void update(double duration) {}
		void render(const fpcameraNS::Transformation&) override;
		Triangle_tb* getNewInstance()override { 
			Triangle_tb *t(new Triangle_tb("triangle_tb"));
			return t; 
		}
		void create();


	};







}//NS
#endif
