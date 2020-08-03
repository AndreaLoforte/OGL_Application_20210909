#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<buttonfunctionLoader.h>
namespace uiNS {

	buttonFunctiosList::PmouseButton1 buttonFunctiosList::fp1;
	buttonFunctiosList::PmouseCursor1 buttonFunctiosList::fp2;
	buttonFunctiosList::PkeyCallback1 buttonFunctiosList::fpkey1;
	buttonFunctiosList::PmouseScroll1 buttonFunctiosList::fpscroll1;
	buttonFunctiosList::PmouseButton2 buttonFunctiosList::fpMbutton2;
	buttonFunctiosList::PkeyCallback2 buttonFunctiosList::fpkey2;
	buttonFunctiosList::PCallbackII buttonFunctiosList::fpii;



	void buttonFunctiosList::setMouseButtonCallback(PmouseButton2 f)
	{
		fpMbutton2 = f;

		auto L_MouseButton_callback = [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(w))->fpMbutton2();
		};
		glfwSetMouseButtonCallback(Application::window, L_MouseButton_callback);
		//fp1(Application::window, 0, 0, 0);
	}






	void buttonFunctiosList::setMouseButtonCallback(PmouseButton1 f)
	{
		fp1 = f;

		auto L_MouseButton_callback = [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(w))->fp1(w, button, action, mods);
		};
		glfwSetMouseButtonCallback(Application::window, L_MouseButton_callback);
		//fp1(Application::window, 0, 0, 0);
	}

	void buttonFunctiosList::setMouseButtonCallback(PCallbackII f)
	{
		fpii = f;

		auto L_MouseButton_callback = [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(w))->fpii( button, action);
		};
		glfwSetMouseButtonCallback(Application::window, L_MouseButton_callback);
		//fp1(Application::window, 0, 0, 0);
	}

	void buttonFunctiosList::setMouseCursorCallback(PmouseCursor1 f)
	{
		fp2 = f;
		auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
		{			
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(w))->fp2(w, d1, d2);
		};
		glfwSetCursorPosCallback(Application::window, L_cursor_callback);
		fp2(Application::window, 0, 0);
	}


	void buttonFunctiosList::setKeyCallback(PkeyCallback1 f)
	{
		fpkey1 = f;
		auto L_key_callbackControl = [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(w))->fpkey1(w, key, scancode, action, mods);
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);
		fpkey1(Application::window, 0, 0, 0, 0);
	}

	void buttonFunctiosList::setKeyCallback(PkeyCallback2 f)
	{
		fpkey2 = f;
		auto L_key_callbackControl = [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(w))->fpkey2();
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);
		fpkey2();
	}


	void buttonFunctiosList::setKeyCallback(PCallbackII f)
	{
		fpii = f;
		auto L_key_callbackControl = [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(w))->fpii(key,action);
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);
	}

	void buttonFunctiosList::setMouseScrollCallback(PmouseScroll1 f)
	{

		fpscroll1 = f;

		auto L_mouse_scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset)
		{
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(window))->fpscroll1(window, xoffset, yoffset);
		};
		glfwSetScrollCallback(Application::window, L_mouse_scroll_callback);

	}


	void buttonFunctiosList::setCursorCallback(PmouseButton2 f)
	{
		fpMbutton2 = f;

		auto L_mouse_cursor_callback = [](GLFWwindow* window, double xoffset, double yoffset)
		{
			static_cast<buttonFunctiosList*>(glfwGetWindowUserPointer(window))->fpMbutton2();
		};
		glfwSetCursorPosCallback(Application::window, L_mouse_cursor_callback);

	}


}