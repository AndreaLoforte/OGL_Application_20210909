#ifndef SHADER_MAN
#define SHADER_MAN
#include<shaders.h>
#include<map>
#include<string>
#include<initializer_list>
#include<log.h>


namespace shaderManagerNS{

  class ShaderManager{
   std::map<std::string,shaderNS::Shader> vshadersMAP;
    std::map<std::string,shaderNS::Shader> fshadersMAP;    
    

    //NO DEFAULT CONSTRUCTOR
    ShaderManager(ShaderManager const &);//NO COPY CONSTRUCTOR
  public:
  ShaderManager(){}
    ShaderManager(std::string vs_path, std::string fs_path)
      {
	    setVShader(vs_path);
	    setFShader(fs_path);
      }
    
    //const char** getShaderSource(std::string);    
    const char** getVShaderSource(int);
    const char** getFShaderSource(int);
    

    inline shaderNS::Shader getShader(std::string shpath)
    {//questa funzione è univoca per fragment e vertex shader.
	//controlla se lo shaderPath inserito è presente nella mappa dei vertex shader
		//se si ritorna lo shader altrimenti assegno all'iteratore quello che trova nel fragment shader (ATTENZIONE!!)

		if (vshadersMAP.find(shpath) != vshadersMAP.end())
			return vshadersMAP.find(shpath)->second;

		  
		if (fshadersMAP.find(shpath) != fshadersMAP.end())
			return fshadersMAP.find(shpath)->second;

		 logNS::Logger::writeLog("shadermanager.h::getShader() : could not find ", shpath);
		  return shaderNS::Shader();
    }	
    
    inline void setVShader(std::string shPath)
    {
      shaderNS::Shader sh(shPath);
      vshadersMAP.insert({shPath,sh});
    }

    inline void setFShader(std::string shPath)
    {
      shaderNS::Shader sh(shPath);
      fshadersMAP.insert({shPath,sh});
    }

    
    //  shaderNS::Shader unifyShaders(shaderNS::Shader *, int);
  };

}//namespace

#endif
