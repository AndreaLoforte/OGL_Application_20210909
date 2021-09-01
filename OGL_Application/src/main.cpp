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
