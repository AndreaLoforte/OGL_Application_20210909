#include<inputs.h>
#include<app.h>
#include<gun.h>
#include<applicationDerivedObject.h>


namespace InputsNS{

	using namespace textRendererNS;

	void Controls::key_callbackEdit(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		

		//static bool menu = false;
		//static bool objectlist = true;
		//static bool chooseCreate = false;
		//static bool chooseDelete = false;

		//

		//if (key == GLFW_KEY_H && action == GLFW_PRESS)
		//{
		//	ph.mapNewString("EDITMODE", "EDIT MODE COMMANDS : " +
		//			NEWLINE + "Esc to go back in Control Mode");
		//	return;
		//}

		//

		//if (key == GLFW_KEY_ESCAPE)
		//{
		//	mode = 0;
		//	ph.cascadeEraseFromMap("EDITMODE");
		//	menu = false;
		//	objectlist = false;
		//	chooseCreate = false;
		//	chooseDelete = false;
		//	setAllCallbackFunction(window);
		//	return;
		//}


		//if (!menu)
		//{

		//	ph.mapNewString("DELETE", "1 to delete an Object");
		//	ph.mapNewString("CREATE", "2 to create an Object");
		//	ph.mapNewString("ESC", "ESC to go back in Control Mode");

		//	menu = true;
		//	objectlist = false;
		//}

		//if (action == GLFW_RELEASE) return;

		//if (!objectlist)
		//{
		//	if (key == GLFW_KEY_1)
		//	{
		//		UserInterface::printExistingObjects();
		//		objectlist = true;
		//		chooseDelete = true;
		//		return;

		//	}
		//	if (key == GLFW_KEY_2)
		//	{
		//		UserInterface::printAssetObjectsList();
		//		objectlist = true;
		//		chooseCreate = true;
		//		return;
		//	}
		//}

		//if(key == GLFW_KEY_C)
		//	fpcameraNS::CameraManager::switchCamera();

		//if (chooseCreate)
		//{

		//	int N = chooseObject(key);
		//	if (N == -1 || N == -2)
		//		return;
		//	else
		//		myobjectNS::ApplicationObjectManager::createNewObject(N);
		//	
		//	return;
		//}

		//if (chooseDelete)
		//{

		//	int N = chooseObject(key);
		//	if (N == -1)
		//	{//ERROR
		//		menu = false;
		//		objectlist = true;
		//		chooseCreate = false;
		//		chooseDelete = false;
		//		return;
		//	}

		//	if (N >= 0)
		//	{//VALID CHOICE
		//		myobjectNS::ApplicationObjectManager::deleteObject(N);
		//		menu = false;
		//		objectlist = true;
		//		chooseDelete = false;
		//		return;
		//	}

		//}

	}



	//////////////CURSOR
#include<userInterface.h>

	static  float xpos_, ypos_;

	void Controls::cursor_callback_editMode(GLFWwindow* window, double xpos, double ypos)
	{

		xpos_ = xpos;
		ypos_ = ypos;

	}//Controls::cursor_callback


	void Controls::mouse_button_callback_editMode(GLFWwindow* window, int button, int action, int mods)
	{
		/*want to call the function only for press actions*/
		if(action != GLFW_RELEASE)
		userInterface->cursorVStext(xpos_, ypos_);

	}


    
}//InputsNS