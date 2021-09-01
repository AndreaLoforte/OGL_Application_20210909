#ifndef OBJCONTROLSINTERFACE_H
#define OBJCONTROLSINTERFACE_H

//#include<gl3w.h>
//#include<glfw3.h>
#include<inputs.h>
#include<printhelper.h>

namespace myobjectNS {
	class ApplicationObject;
}

//namespace InputsNS{
//	class Controls;
//}

namespace objectControlsNS {

	//Object controls interface
	class ObjectControlsI {
		InputsNS::Controls controls;
		bool mustPrintEditSize = true;
		bool mustPrintEditColor = true;
		static printHelperNS::PrintHelper ph;
	public:
		/*void key_callbackEditSize(GLFWwindow*, int, int, int, int);
		void key_callbackEditColor(GLFWwindow*, int, int, int, int);
		static void setKeyCallbackEditSize(GLFWwindow * window);
		static void setKeyCallbackEditColor(GLFWwindow * window);
		static void setScrollCallback(GLFWwindow*);
		static void ObjectPhysicsSwitcher(myobjectNS::ApplicationObject*);
		static void ObjectSwitch(collectorNS::ApplicationObjectCollector*);
		void scroll_callback(GLFWwindow*, double, double);*/
		static bool mustPrint;
		
		
	};



}












#endif