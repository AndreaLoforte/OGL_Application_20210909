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
	  
      app.update();
      app.render(glfwGetTime());
	  
      glfwPollEvents();
      glfwSwapBuffers(app.window);
	  
    }


  app.shutdown();
  

  
  return 0;
}
