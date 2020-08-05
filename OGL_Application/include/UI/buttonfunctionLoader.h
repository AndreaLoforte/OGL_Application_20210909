#pragma once
#include<buttons.h>

namespace uiNS {


	struct buttonFunctiosLoader {
		typedef void (*PmouseButton1)(GLFWwindow* w, int button, int action, int mods);
		typedef void (*PmouseButton2)();
		typedef void (*PmouseCursor1)(GLFWwindow* w, double, double);
		typedef void (*PkeyCallback1)(GLFWwindow*, int, int, int, int);
		typedef void (*PkeyCallback2)();
		typedef void (*PCallbackII)(int,int);
		typedef void (*PmouseScroll1)(GLFWwindow*, double, double);

		static PmouseButton1 fp1;
		static PmouseButton2 fpMbutton2;
		static PmouseCursor1 fp2;
		static PkeyCallback1 fpkey1;
		static PkeyCallback2 fpkey2;
		static PCallbackII   fpii;
		static PmouseScroll1 fpscroll1;


		void setMouseButtonCallback(PmouseButton1);
		void setMouseButtonCallback(PmouseButton2);
		void setMouseButtonCallback(PCallbackII);
		void setMouseCursorCallback(PmouseCursor1);
		void setKeyCallback(PkeyCallback1);
		void setKeyCallback(PkeyCallback2 f);
		void setKeyCallback(PCallbackII f);
		void setMouseScrollCallback(PmouseScroll1);
		void setCursorCallback(PmouseButton2);
		void unsetKeyCallback();


		static void  unsetKeyCallbackFunc();

	};




	
}