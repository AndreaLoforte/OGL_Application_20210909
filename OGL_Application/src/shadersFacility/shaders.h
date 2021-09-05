#ifndef SHADER_H
#define SHADER_H
#include<string>
#include<fstream>
#include<iostream>
#include<memory>
#include<log.h>
#include<stdexcept>
namespace shaderNS{

class Shader{
  std::string shaderPath;
  int shader_size;
  const char * shader_source;  
  std::shared_ptr<const char*> ss_owner;


 public:
	 Shader() {
		logNS::Logger::writeLog("shaders.h | Shader() | default constructor has no shader path", "shadersLog.txt");
	 }
 Shader(std::string sPath):shaderPath(sPath)
    {
	 try {  shader_size = getShaderSize(sPath);  }
	 catch (const exceptionNS::TestClass& e)
	 { 
		 logNS::Logger::writeLog("shaders.h|shaders.cpp | Shader::getShaderSize() | shader input file "+sPath+" opening state = 0 : failed to open shader input file", "shadersLog.txt");
		 throw exceptionNS::TestClass(e.what());
	 }

      shader_source = loadShader(sPath);//ok: il puntatore non è costante!
      ss_owner = std::make_shared<const char*>(shader_source);
  }

  Shader(Shader const & obj)
    {
      shaderPath = obj.shaderPath;
      shader_size = obj.shader_size;
      shader_source = obj.shader_source;
      ss_owner = obj.ss_owner;
    }

  Shader(char * ss,int sh_size)
    {
      shaderPath = "NONE";
      shader_size = sh_size;
      shader_source = ss;
      ss_owner = std::make_shared<const char*>(ss);
    }

  const char* loadShader(std::string);

  inline void setShader(std::string shaderPath)
  {
     shaderPath = shaderPath;
     shader_source = loadShader(shaderPath);
  }
  
  inline void printShader()
  {
    std::clog<<"Shader::printShader::shader_size is: "<<shader_size<<std::endl;
    for(int i = 0; i < shader_size; i++)
      std::cout<<shader_source[i];

    //    std::cout<<std::endl;
  }

  
  inline std::string getShaderPath(){ return shaderPath;}

  inline const  char** getShaderSource()
  {
    return &shader_source;
  }

  int getShaderSize(std::string);
  inline int getShaderSize(){ return shader_size;}
  inline char getShaderSource(int &i){ return shader_source[i];}
  
};



 }//namespace 
#endif

