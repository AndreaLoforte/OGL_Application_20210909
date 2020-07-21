/** @file */ 
#include<iostream>
#include<fstream>
#include<iostream>
#include<string>
#include<app.h>
#include<log.h>


int main(){

	logNS::Logger::initLogger();
  
 App app;
  
  if(!app.init())
    {
      std::cout<<"main.cpp : ERROR : app.init() return error"<<std::endl;
      return -1;
    }
    else
    {
      std::cout<<"main.cpp : app.init() completed"<<std::endl;
    }
    
    
  app.startup();



  
  while(!glfwWindowShouldClose(app.window))
    {
	  
      app.render(glfwGetTime());
	  app.update();
      glfwPollEvents();
      glfwSwapBuffers(app.window);
	  
    }


  app.shutdown();
  

  
  return 0;
}
