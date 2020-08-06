#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<buttonfunctionLoader.h>
namespace uiNS {

	buttonFunctiosLoader::PmouseButton1 buttonFunctiosLoader::fp1;
	buttonFunctiosLoader::PmouseCursor1 buttonFunctiosLoader::fp2;
	buttonFunctiosLoader::PkeyCallback1 buttonFunctiosLoader::fpkey1;
	buttonFunctiosLoader::PmouseScroll1 buttonFunctiosLoader::fpscroll1;
	buttonFunctiosLoader::PmouseButton2 buttonFunctiosLoader::fpMbutton2;
	buttonFunctiosLoader::PkeyCallback2 buttonFunctiosLoader::fpkey2;
	buttonFunctiosLoader::PCallbackII   buttonFunctiosLoader::fpii;
	buttonFunctiosLoader::PCallbackII   buttonFunctiosLoader::fpii2;



	void buttonFunctiosLoader::setMouseButtonCallback(PmouseButton2 f)
	{
		fpMbutton2 = f;

		auto L_MouseButton_callback = [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(w))->fpMbutton2();
		};
		glfwSetMouseButtonCallback(Application::window, L_MouseButton_callback);
		//fp1(Application::window, 0, 0, 0);
	}






	void buttonFunctiosLoader::setMouseButtonCallback(PmouseButton1 f)
	{
		fp1 = f;

		auto L_MouseButton_callback = [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(w))->fp1(w, button, action, mods);
		};
		glfwSetMouseButtonCallback(Application::window, L_MouseButton_callback);
		//fp1(Application::window, 0, 0, 0);
	}

	void buttonFunctiosLoader::setMouseButtonCallback(PCallbackII f)
	{
		fpii = f;

		auto L_MouseButton_callback = [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(w))->fpii( button, action);
		};
		glfwSetMouseButtonCallback(Application::window, L_MouseButton_callback);
		//fp1(Application::window, 0, 0, 0);
	}

	

	void buttonFunctiosLoader::setMouseCursorCallback(PmouseCursor1 f)
	{
		fp2 = f;
		auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
		{			
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(w))->fp2(w, d1, d2);
		};
		glfwSetCursorPosCallback(Application::window, L_cursor_callback);
		//fp2(Application::window, 0, 0);
	}


	void buttonFunctiosLoader::setKeyCallback(PkeyCallback1 f)
	{
		fpkey1 = f;
		auto L_key_callbackControl = [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(w))->fpkey1(w, key, scancode, action, mods);
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);
		//fpkey1(Application::window, 0, 0, 0, 0);
	}

	void buttonFunctiosLoader::setKeyCallback(PkeyCallback2 f)
	{
		fpkey2 = f;
		auto L_key_callbackControl = [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(w))->fpkey2();
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);
		//fpkey2();
	}


	void buttonFunctiosLoader::setKeyCallback(PCallbackII f)
	{
		fpii2 = f;
		auto L_key_callbackControl = [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(w))->fpii2(key,action);
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);
	}

	void buttonFunctiosLoader::setMouseScrollCallback(PmouseScroll1 f)
	{

		fpscroll1 = f;

		auto L_mouse_scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset)
		{
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(window))->fpscroll1(window, xoffset, yoffset);
		};
		glfwSetScrollCallback(Application::window, L_mouse_scroll_callback);

	}


	void buttonFunctiosLoader::setCursorCallback(PmouseButton2 f)
	{
		fpMbutton2 = f;

		auto L_mouse_cursor_callback = [](GLFWwindow* window, double xoffset, double yoffset)
		{
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(window))->fpMbutton2();
		};
		glfwSetCursorPosCallback(Application::window, L_mouse_cursor_callback);

	}



	void  buttonFunctiosLoader::unsetKeyCallbackFunc(){};

	void buttonFunctiosLoader::unsetKeyCallback()
	{
		auto L_key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(window))->unsetKeyCallbackFunc();
		};
		glfwSetKeyCallback(Application::window, L_key_callback);

	}


	void buttonFunctiosLoader::unsetCursorCallbackFunc() {};

	void buttonFunctiosLoader::unsetCursorCallback()
	{
		auto L_cursor_callback = [](GLFWwindow* window, double x, double y)
		{
			static_cast<buttonFunctiosLoader*>(glfwGetWindowUserPointer(window))->unsetCursorCallbackFunc();
		};
		glfwSetCursorPosCallback(Application::window, L_cursor_callback);

	}


}