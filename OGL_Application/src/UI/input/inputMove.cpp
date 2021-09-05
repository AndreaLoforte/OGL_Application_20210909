#include<inputs.h>
#include<app.h>
#include<gun/gun.h>
#include<applicationDerivedObject.h>
#include<objectControlsInterface.h>

namespace InputsNS{

	using namespace textRendererNS;


void Controls::key_callbackMove(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//	if(action != GLFW_RELEASE)
//	{
//			ph.mapNewString("EDITABLEOBJECTNAME", myobjectNS::ApplicationObjectManager::getEditableObjectName());
//
//		if (key == GLFW_KEY_H && action == GLFW_PRESS)
//		{
//			ph.mapNewString("EDITABLEOBJECTNAME",
//				NEWLINE + NEWLINE + "OBJECT MODE COMMANDS : " +
//					NEWLINE + "Page Up or Page down to change selected object" +
//					NEWLINE + "Shift object with W,S,A,D. Rotate Object Up,Down,Left, Right" +
//					NEWLINE + "Alt + W,S,A,D to follow the object shift" +
//					NEWLINE + "Esc to go back in Control Mode" +
//					NEWLINE + "I to show object parameters" +
//					NEWLINE + "Left Shift + left/right to rotate along z axis" +
//					NEWLINE + "Ctrl + E to modify the size of the selected object" +
//					NEWLINE + "Ctrl + A to activate object physics"+
//					NEWLINE);
//			return;
//		}
//
//
//		if (key == GLFW_KEY_ESCAPE)
//		{
//			mode = 0;
//			setAllCallbackFunction(window);
//			ph.cascadeEraseFromMap("EDITABLEOBJECTNAME");
//			return;
//		}
//
//		static bool altpressed = false;
//		if (key == GLFW_KEY_LEFT_ALT)
//			altpressed = action == GLFW_PRESS;
//		if (altpressed) //con ALT premuto, voglio muovere sia me stesso che l'oggetto che edito
//			key_callbackControl(window, key, scancode, action, mods);
//
//
//
//		static bool leftshiftpressed = false;
//		if (key == GLFW_KEY_LEFT_SHIFT) leftshiftpressed = action == GLFW_PRESS;
//		if (leftshiftpressed)
//		{
//
//			if (key == GLFW_KEY_LEFT)
//			{
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotZ(-1);
//
//				return;
//			}
//			if (key == GLFW_KEY_RIGHT)
//			{
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotZ(1);
//
//				return;
//			}
//
//		}
//
//
//		//PER ANDARE IN MODALITA EDIT OBJECT
//		if(mods == GLFW_MOD_CONTROL && key == GLFW_KEY_E)
//		{
//			objectControlsNS::ObjectControlsI::setScrollCallback(window);
//			return;
//
//		}
//
//		//ATTIVA-DISATTIVA OGGETTO (fisica, ia, etc..)
//		if (mods == GLFW_MOD_CONTROL && key == GLFW_KEY_A)
//		{
//			objectControlsNS::ObjectControlsI::ObjectSwitch(myobjectNS::ApplicationObjectManager::getEditableCollector());
//			return;
//
//		}
//
//
//
//
//		if (action != GLFW_RELEASE)
//		{
//			switch (key) {
//			case GLFW_KEY_INSERT:
//			{
//				mode = 0;
////				myobjectNS::TextRenderer::clearEditableObjName();
//				setAllCallbackFunction(Application::window);
//			}
//			break;
//			case GLFW_KEY_PAGE_UP:
//				myobjectNS::ApplicationObjectManager::nextObject();
//				ph.mapNewString("EDITABLEOBJECTNAME",
//					"SELECTED OBJECT : "+ myobjectNS::ApplicationObjectManager::getEditableObjectName());
//				break;
//			case GLFW_KEY_PAGE_DOWN:
//				myobjectNS::ApplicationObjectManager::prevObject();
//				ph.mapNewString("EDITABLEOBJECTNAME",
//					"SELECTED OBJECT : " + myobjectNS::ApplicationObjectManager::getEditableObjectName());
//				break;
//			case GLFW_KEY_I:
//				textRendererNS::TextRenderer::printEditableObjectInfos();
//				break;
//			case GLFW_KEY_C:
//				fpcameraNS::CameraManager::switchCamera();
//				break;
//			case GLFW_KEY_W:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrZ(-1);
//				break;
//			case GLFW_KEY_S:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrZ(1);
//				break;
//			case GLFW_KEY_D:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrX(1);
//				break;
//			case GLFW_KEY_A:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrX(-1);
//				break;
//			case GLFW_KEY_1:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrY(-1);
//				break;
//			case GLFW_KEY_2:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrY(1);
//				break;
//
//			case GLFW_KEY_UP:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotX(1);
//				break;
//			case GLFW_KEY_DOWN:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotX(-1);
//				break;
//			case GLFW_KEY_RIGHT:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotY(-1);
//				break;
//			case GLFW_KEY_LEFT:
//				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotY(1);
//				break;
//			case GLFW_KEY_R:
//				fpcameraNS::CameraManager::resetAll();
//				app_pt->resetAll();
//				break;
//				//case GLFW_KEY_0:
//				////resetCamera();
//				//break;
//			case (GLFW_KEY_H):
//				if (hideCursor)
//				{
//					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//					hideCursor = false;
//				}
//				else
//				{
//					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//					hideCursor = false;
//				}
//				break;
//
//			}
//		}//switch
//	}//if(action != GLFW_RELEASE)

}//Controls::key_callback












    
}//InputsNS