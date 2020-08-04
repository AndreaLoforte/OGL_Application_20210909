#include <baseObject.h>

namespace myobjectNS
{


void BaseObject::clean() {}
void BaseObject::setTextures() {}





void BaseObject::printShaderLinkState(const GLint &status, const GLchar *log)
{
  if (!status)
  {
	  logNS::Logger::writeLog("baseObject.cpp : printShaderLinkState : failed to link shader_prog ",shader_prog_name);
	  logNS::Logger::writeLog("baseObject.cpp : printShaderLinkState : SHADER LOG : ",log, shader_prog_name);
  }
}

 
void BaseObject::printVShaderLog(const char *log)
{
	logNS::Logger::writeLog("baseObject.cpp : printVShaderLog : vshader for shader_program did not compile", shader_prog_name);
	logNS::Logger::writeLog("baseObject.cpp : printVShaderLog : VERTEX LOG IS : ",log, shader_prog_name);
 }	




void BaseObject::printFShaderLog(const char *log)
{
	logNS::Logger::writeLog("baseObject.cpp : printFShaderLog : fshader for shader_program did not compile", shader_prog_name);
	logNS::Logger::writeLog("baseObject.cpp : printFShaderLog : FRAGMENT LOG IS : ",log, shader_prog_name);
}








void BaseObject::setShaders()
{
  shader_prog = glCreateProgram();

  GLchar const *vss[] =
      {
          *smanager.getVShaderSource(0)
      };

   
  
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, vss, NULL);
  glCompileShader(vs);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, smanager.getFShaderSource(0), NULL);
  glCompileShader(fs);

  GLint vs_status;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_status);

  GLint fs_status;
  glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_status);



  if (vs_status == 0 || fs_status == 0)
  {
    if (vs_status == 0)
    {
		logNS::Logger::writeLog("baseObject.cpp : setShaders : vertex shader status = 0 (bad)", shader_prog_name);
      GLint log_length;
      glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &log_length);
      char * log =  new char[log_length];
      glGetShaderInfoLog(vs, log_length, NULL, log);
      printVShaderLog(log);
	  delete[] log;
    }

    if (fs_status == 0)
    {
		logNS::Logger::writeLog("baseObject.cpp : setShaders : fragment shader status = 0 (bad)",shader_prog_name);
		GLint log_length;
      glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &log_length);
	  char * log = new char[log_length];
      glGetShaderInfoLog(fs, log_length, NULL, log);
      printFShaderLog(log);
	  delete[] log;
    }
  }
  else
  {
	 

    glAttachShader(shader_prog, vs);
    glAttachShader(shader_prog, fs);
    glLinkProgram(shader_prog);

    GLint param = 0;
    glGetProgramiv(shader_prog, GL_LINK_STATUS, &param);
	/*params returns GL_TRUE if the last link 
	operation on program was successful, 
	and GL_FALSE otherwise.*/
    if (param)		
    {
		readyToDraw = true;
      //printShaderLinkState(param, NULL);
    }
    else
    {
		logNS::Logger::writeLog("baseObject.cpp : setShaders : linking failed", shader_prog_name); 
			GLint logLength = 0;
			glGetProgramiv(shader_prog, GL_INFO_LOG_LENGTH, &logLength);
			logNS::Logger::writeLog("logLength is : ", logLength, "shadersLog.txt");
			char * log = new char[logLength];
			glGetProgramInfoLog(shader_prog, logLength, NULL, log);
			printShaderLinkState(param, log);
			delete[] log;
		
    }
  }
	
  glDeleteShader(vs);
  glDeleteShader(fs);
}

std::string cleanString(std::string path) {
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == '\\')
			path[i] = '/';

	}
	/*std::cout << "new path is " << path;*/
	return path;
}


} // namespace myobjectNS
