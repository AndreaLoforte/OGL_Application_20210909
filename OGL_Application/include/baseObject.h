#ifndef OBJECT_H
#define OBJECT_H

#include<gl3w.h>
#include<string.h>
#include<shaders.h>
#include<shadermanager.h>
//#include<sb7ktx.h>
#include<SOIL2.h>
#include<application.h>
#include<initializer_list>
#include<fpcamera.h>
#include<vector>
#include<log.h>




namespace myobjectNS{

	static const string SHADERSROOTDIR = "/OGL_Application/src/Objects/";
	static const string VERTEXSHADERSEXT = ".vert";
	static const string FRAGMENTSHADERSEXT = ".frag";

	class BaseObject {
	public:
		GLuint VAO;
		GLuint VBO;
		GLuint shader_prog;
		std::string shader_prog_name;
		shaderManagerNS::ShaderManager smanager;
		std::string vpath;
		std::string fpath;
		std::string fullpath;
  
	   std::string vshaders;
	   std::string fshaders;
	   /*parametro settato a true se ci sono tutte 
	   le condizioni per renderizzare l'ogetto 
	   (ad esempio sono stati compilati correttamente gli shaders)*/
	   bool readyToDraw = false;

  public:
	  BaseObject(){}
	  BaseObject(std::string sh_prog_name,std::string shadersDir) {
		  fullpath = Application::getApplicationRootDir();
		  fullpath += SHADERSROOTDIR;
		  shader_prog_name = sh_prog_name;
		  vpath = fullpath+shadersDir +sh_prog_name+ VERTEXSHADERSEXT;
		  fpath = fullpath+shadersDir +sh_prog_name+ FRAGMENTSHADERSEXT;
		  smanager.setVShader(vpath);
		  smanager.setFShader(fpath);
		  

	  }

    BaseObject(std::string sh_prog_name){
		fullpath = Application::getApplicationRootDir();
		fullpath += SHADERSROOTDIR;
		shader_prog_name = sh_prog_name;
		vpath = fullpath + shader_prog_name + "/" + shader_prog_name + ".vert";
		fpath = fullpath + shader_prog_name + "/" + shader_prog_name + ".frag";
		smanager.setVShader(vpath);
		smanager.setFShader(fpath);
		
		
    }

	
    void clean();
	void setShaders();
    void setTextures();
    void printShaderLinkState(const GLint&,const GLchar *);
    void printVShaderLog(const char *);
    void printFShaderLog(const char*);
  };


}


#endif
