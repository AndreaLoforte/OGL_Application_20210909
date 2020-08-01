#pragma once
#include<buttons.h>

namespace uiNS {


	struct buttonFunctiosList {
		typedef void (*PmouseButton1)(GLFWwindow* w, int button, int action, int mods);
		typedef void (*PmouseButton2)();
		typedef void (*PmouseCursor1)(GLFWwindow* w, double, double);
		typedef void (*PkeyCallback1)(GLFWwindow*, int, int, int, int);
		typedef void (*PmouseScroll1)(GLFWwindow*, double, double);

		static PmouseButton1 fp1;
		static PmouseButton2 fpMbutton2;
		static PmouseCursor1 fp2;
		static PkeyCallback1 fpkey1;
		static PmouseScroll1 fpscroll1;

		void setMouseButtonCallback(PmouseButton1);
		void setMouseButtonCallback(PmouseButton2);
		void setMouseCursorCallback(PmouseCursor1);
		void setKeyCallback(PkeyCallback1);
		void setMouseScrollCallback(PmouseScroll1);
		

	};




	
}