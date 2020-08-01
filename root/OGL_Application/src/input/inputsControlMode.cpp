#include<inputs.h>
#include<app.h>
#include<gun.h>
#include<applicationDerivedObject.h>
#include<sound.h>
#include<buttons.h>
namespace InputsNS{

	using namespace textRendererNS;

	void Controls::key_callbackControl(GLFWwindow* window, int key, int scancode, int action, int mods)
	{		
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			/*primo ESC pulisco la stringa statica, 
				secondo ESC vado in modalita ESC*/
				/*ph.eraseFromMap("CONTROLMODE");*/
				mode = 3;
				setAllCallbackFunction(window);
			
		}



		static bool H = false;
		if (key == GLFW_KEY_H && action == GLFW_PRESS)
		{
			if (!H)
			{
				ph.mapNewString("CONTROLMODE",
					NEWLINE + NEWLINE + "CONTROL MODE COMMANDS :" +
					NEWLINE + "CTRL +  E to enter Edit Mode" +
					NEWLINE + "Ins to work on a selected object" +
					NEWLINE + "Esc to quit the program" +
					NEWLINE + "C to switch from Ground Camera to Flying Camera" +
					NEWLINE + "I to show the Model-View Matrix" +
					NEWLINE + "Move around with W,S,A,D, 1,2,Up,Down, Left,Right, and the mouse" +
					NEWLINE + "left CTRL + Scroll to change movement velocity" +
					NEWLINE + "left CTRL + S to save project status "+
					NEWLINE + "P to pause");
				H = true;
			}
			else
			{
				H = false;
				ph.eraseFromMap("CONTROLMODE");
			}
			return;

		}


		/*imposta un parametro che mi permette premendo CTRL
		di alterare la mia velocità di spostamento (eg la velocità della camera)
		attraverso lo scroll del mouse*/
		if (mods == GLFW_MOD_CONTROL)
			setScrollCallbackCallerID(1);

		if (key == GLFW_KEY_V)
		 {
			soundNS::soundMap::startSounds();
		}

		
		if (mods == GLFW_MOD_CONTROL)
		if (key == GLFW_KEY_E)
			userInterface->start->action();
		

		
		if (mods == GLFW_MOD_CONTROL)
		if (key == GLFW_KEY_S)
		{
			UserInterface::mapButtonOnParentBranch(UserInterface::getParentButton()->getButtonID(),"SAVED");
			App::SaveProjectData(App::projectDataFileName);
			return;
		}

	
		switch (key) 
		{
		case GLFW_KEY_INSERT:
		{
			ph.eraseFromMap("CONTROLMODE");
			mode = 1;
			setAllCallbackFunction(Application::window);
		}
		break;
		case GLFW_KEY_P:
			UserInterface::pause();
			break;
		case GLFW_KEY_W:
			fpcameraNS::CameraManager::getActiveCameraLH().moveFw();
			break;
		case GLFW_KEY_C:
			fpcameraNS::CameraManager::switchCamera();
			break;
		case GLFW_KEY_S:
			fpcameraNS::CameraManager::getActiveCameraLH().moveBw();
			break;
		case GLFW_KEY_D:
			fpcameraNS::CameraManager::getActiveCameraLH().moveRt();
			break;
		case GLFW_KEY_A:
			fpcameraNS::CameraManager::getActiveCameraLH().moveLt();
			break;

		case GLFW_KEY_UP:
			fpcameraNS::CameraManager::getActiveCameraLH().rotXccw();
			break;
		case GLFW_KEY_DOWN:
			fpcameraNS::CameraManager::getActiveCameraLH().rotXcw();
			break;
		case GLFW_KEY_RIGHT:
			fpcameraNS::CameraManager::getActiveCameraLH().rotYcw();
			break;
		case GLFW_KEY_LEFT:
			fpcameraNS::CameraManager::getActiveCameraLH().rotYccw();
			break;
		case GLFW_KEY_1:
			fpcameraNS::CameraManager::getActiveCameraLH().moveUp();
			break;
		case GLFW_KEY_2:
			fpcameraNS::CameraManager::getActiveCameraLH().moveDown();
			break;
		case GLFW_KEY_R:
			app_pt->resetAll();
			break;
		case GLFW_KEY_I:
			fpcameraNS::CameraManager::switchPrintInfos();
			break;

		}//switch

	}//Controls::key_callback









    
}//InputsNS