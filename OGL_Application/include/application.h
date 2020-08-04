#ifndef APPLICATION_H
#define APPLICATION_H
#include<gl3w.h>
#include<glfw3.h>//gl3w.h MUST COMES FIRST!
#include<stdio.h>
#include<iostream>
#include<vector>
#include<vmath.h>
#include<fstream>
#include<string>
#include<ctime>
#include<log.h>


class Application{
	friend class Logger;
public : 
	static std::string application_root_dir;
  
public:
	Application() {
	}
	~Application() {
		
	}
  static GLFWwindow* window;
  static GLint window_width;
  static GLint window_height;
  static GLfloat aspect;
  
  static int init();
  //static void startup();
  static void shutdown();
  //static void key_callback(GLFWwindow*,int,int,int,int);
  static void glInfo(GLboolean);
  static void onResize(GLFWwindow*,GLint,GLint);
  static std::string getApplicationRootDir();
};

#endif