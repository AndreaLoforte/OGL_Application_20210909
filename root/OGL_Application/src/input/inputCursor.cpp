#include<inputs.h>
#include<app.h>
#include<gun.h>
#include<applicationDerivedObject.h>
#include<playerCharacter.h>

namespace InputsNS{

	
	void Controls::setButtonCallback(GLFWwindow* window)
	{
		auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		{
			static_cast<Controls*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, i1, i2, i3);
		};
		glfwSetMouseButtonCallback(window, L_mouse_button_callback);

	}

	void Controls::setCursorCallback(GLFWwindow* window)
	{
		auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
		{
			static_cast<Controls*>(glfwGetWindowUserPointer(w))->cursor_callback(w, d1, d2);
		};
		glfwSetCursorPosCallback(window, L_cursor_callback);

	}

	void Controls::setScrollCallback(GLFWwindow* window)
	{
		auto L_scroll_callback = [](GLFWwindow* w, double xoffset, double yoffset)
		{
			static_cast<Controls*>(glfwGetWindowUserPointer(w))->scroll_callback(w, xoffset, yoffset);
		};

		glfwSetScrollCallback(window, L_scroll_callback);
	}





	


	void Controls::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (playerIsOn && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			player->shoot();
		}
	}
	void Controls::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		//default function
		if (scrollCallbackCallerID == 0)
		{
			if (playerIsOn)
				player->changeFirepower(yoffset);
		}
		if (scrollCallbackCallerID == 1)
		{
			fpcameraNS::CameraManager::changeCameraMovementSpeed(yoffset);
			scrollCallbackCallerID = 0;
		}
		
	}




	void Controls::cursor_callback(GLFWwindow* window, double xpos, double ypos)
	{
		
		fpcameraNS::CameraManager::getActiveCameraLH().rotXcw(ypos / 10);
		fpcameraNS::CameraManager::getActiveCameraLH().rotYcw(xpos / 10);


	}//Controls::cursor_callback










    
}//InputsNS