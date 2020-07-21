#include<shaders.h>

namespace shaderNS{

  int Shader::getShaderSize(std::string shaderPath)
  {
      //aggiungere un controllo che verifichi che la prima riga non sia vuota
    std::ifstream temp_ss(shaderPath,std::ifstream::in);
	if (!temp_ss.good()) 
		throw exceptionNS::TestClass("shaders.cpp | Shader::getShaderSize() | shader input file opening state = 0 : failed to open shader input file");
	
    /*if(temp_ss.is_open())*/
	else
      {
	char c;
	int size = 0;
	while(temp_ss.get(c))
	  size++;
	temp_ss.close();

	temp_ss.close();
	return size;
	
      }

	/*else {
		logNS::Logger::writeLog("shader.cpp::getShaderSize() :could not open the file");
		return -1;
	}*/
  }
    

  

 const char* Shader::loadShader(std::string shaderPath)
  {
    std::ifstream temp_ss(shaderPath,std::ifstream::in);
    if(temp_ss)
      {
		 char c;
		char *ss = new char[shader_size];
	
		unsigned i = 0 ;
		while(temp_ss.get(c))
		  {
	  
		  ss[i++] = c;
		  }

		//SHADERS MUST BE NULL TERMINATED!
		ss[shader_size++] = '\0';

		return ss;

	}
	else {
		logNS::Logger::writeLog("shader.cpp::loadShader() : ERROR ::: no shaders found at path : ", shaderPath, "shadersLog.txt");
		logNS::Logger::exploreFolder(shaderPath.c_str());
		return nullptr;
	}
  }


  
 
  


}//namespace
