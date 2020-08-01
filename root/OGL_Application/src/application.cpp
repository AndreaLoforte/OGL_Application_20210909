#include<application.h>
#include<inputs.h>

GLFWwindow* Application::window;
GLint Application::window_width = 1400;
GLint Application::window_height = 800;
GLfloat Application::aspect =  Application::window_width/(float)Application::window_height;
std::string Application::application_root_dir{ Application::getApplicationRootDir() };





int Application::init()
{

  if(!glfwInit())
    return 0;
  
  //talvolta le hint sono utili talvolta limitano l'estensione
  /* glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4); */
	//glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE); 
 // glfwWindowHint(GLFW_STEREO,GL_FALSE);
 // glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
  
	//  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
  ///glfwSetWindowOpacity(Application::window, 0.5f);

  //ANTIALIASING
  glfwWindowHint(GLFW_SAMPLES, 4);
  

    window=glfwCreateWindow(window_width,window_height,"Example",NULL,NULL);
  
	if (!window)
	{
		glfwTerminate();
		return 0;
	}

 
	//glEnable(GL_MULTISAMPLE);
	glfwSetInputMode(window, GLFW_MOD_CONTROL, GLFW_TRUE);
    glfwSetWindowSizeCallback(window,onResize);
    glfwMakeContextCurrent(window);
	 glfwSwapInterval(1);
   

    gl3wInit();

    glInfo(true);
    return 1;
}  



void Application::shutdown()
{
	
}



void Application::glInfo(GLboolean flag = false)
{

  if(flag)
    {
      const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
      const GLubyte* version = glGetString(GL_VERSION); // version as a string
      printf("Renderer: %s\n", renderer);
      printf("OpenGL version supported %s\n", version);

      GLint numExtension;
      glGetIntegerv(GL_NUM_EXTENSIONS,&numExtension);
      printf("Number of extensions supported %i\n",numExtension);

	  GLint maxVertexAttribs;
	  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
	  std::cout << "GL_MAX_VERTEX_ATTRIBUTES :" << maxVertexAttribs << std::endl;

      GLint numBinaryFormat;
      glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS,&numBinaryFormat);
      std::cerr<<"Number of binary formats supported is : "<<numBinaryFormat<<std::endl;

	  GLint version_maj;
	  GLint version_min;
	  glGetIntegerv(GL_MAJOR_VERSION, &version_maj);
	  std::cerr << "GL_MAJOR_VERSION : " << version_maj << std::endl;
	  glGetIntegerv(GL_MINOR_VERSION, &version_min);
	  std::cerr << "GL_MINOR_VERSION : " << version_min << std::endl;

      
      const GLubyte* extension;
      for(int i = 0; i < numExtension; i++)
	{
	  extension = glGetStringi(GL_EXTENSIONS,i);
	  printf("OpenGL available extension : %s \n",extension);
	}
    }//if wants info

}

std::string cleanString(std::string path) {
	//sostituisce il carattere '\' con '/'
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == '\\')
			path[i] = '/';
		
	}
	/*std::cout << "new path is " << path;*/
	return path;
}

std::string Application::getApplicationRootDir() {
	char* buffer;

	// Get the current working directory:
	if ((buffer = _getcwd(NULL, 0)) == NULL)
	{
		perror("_getcwd error");
		return nullptr;
	}
	else
	{
		/*std::cerr << "Application::getApplicationRootDir " << std::endl;
		printf("%s \nLength: %zu\n", buffer, strlen(buffer));*/
		std::string path{ buffer };
		path = cleanString(path);
		logNS::Logger::writeLog("application.cpp | Application::getApplicationRootDir() | Application rootPath is :" , path);

		free(buffer);
		return path;
		
		
	}	

}









void Application::onResize(GLFWwindow* window,GLint width,GLint height)
{
  window_width = width;
  window_height = height;
  aspect = (float)width/(float)height;
  
  vmath::mat4 proj_matrix = vmath::perspective(50.0f,aspect,.1f,1000.0f);

  std::clog<<"new width :"<<window_width<<std::endl;
  std::clog<<"new height :"<<window_height<<std::endl;

}

