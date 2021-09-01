#ifndef TRIANGLE_OBJ
#define TRIANGLE_OBJ

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<assert.h>
//#include<collide_fine.h>
#include<objectCollector.h>
namespace myobjectNS {

	class Triangle final :public ApplicationObject, public ShaderObject{
		GLuint triangle_vao;
		GLuint triangle_buffer;
		const unsigned vai = 0;
		const int vbbi = 0;
	public:
		Triangle(std::string sh_prog_name) :
			ApplicationObject(sh_prog_name),
			ShaderObject(sh_prog_name) {
		
		}
		~Triangle() {

		}
		void clean() {}
		
		void update(const float &)override;
		void render(const fpcameraNS::Transformation&)override;
		void create()override;
		Triangle* getNewInstance()override {
			Triangle *t(new Triangle("triangle"));
			return t;
		}
		

	};







}//NS
#endif
