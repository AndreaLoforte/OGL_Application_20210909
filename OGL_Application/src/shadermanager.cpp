#include<shadermanager.h>

namespace shaderManagerNS{

const char** ShaderManager::getFShaderSource(int i)
{  
  std::map<std::string,shaderNS::Shader>::iterator it = fshadersMAP.begin();
  bool outOfRange = false;
  for(int j = 0; j < i ; i++,it++)
      if(it == fshadersMAP.end())
	{
		  logNS::Logger::writeLog("shadermanager.cpp::ERROR : this object has only ", i , " fragment shaders", "shadersLog.txt");
		  outOfRange = true;
	}

  if(!outOfRange){
				return it->second.getShaderSource();
  }else{
			logNS::Logger::writeLog("shadermanager.cpp : getFshaderSource : returning NULL", "shadersLog.txt");
			return NULL;
		}
}




const char** ShaderManager::getVShaderSource(int i){

		  std::map<std::string,shaderNS::Shader>::iterator it = vshadersMAP.begin();
		  if (it == vshadersMAP.end())
		  {
			  logNS::Logger::writeLog("there are no shaders for this object", "shadersLog.txt");
			  return nullptr;
		  }

		  bool outOfRange = false;
		  for(int j = 0; j < i ; j++,it++)//forse mettere <= 
			  if(it == vshadersMAP.end())
			{
				logNS::Logger::writeLog("shadermanager.cpp::ERROR : this object has only ", i + 1, " fragment shaders","shadersLog.txt");
				outOfRange = true;
			}

		  if(!outOfRange){
		
				return it->second.getShaderSource();
		  }
		  else{
			  logNS::Logger::writeLog("shadermanager.cpp : getVshaderSource : returning NULL", "shadersLog.txt");
			return NULL;
		  }
}
  
  
}//NS
