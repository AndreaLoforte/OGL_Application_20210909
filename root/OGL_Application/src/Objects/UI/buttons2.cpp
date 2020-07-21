#include<buttons.h>
#include<userInterface.h>
#include<applicationObjectManager.h>
#include<objectControlsInterface.h>

namespace uiNS
{



	void EditObjectModeButton::action()
	{
		UserInterface::deleteAllButtons();

		UserInterface::ph.mapButtonOnBranch(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);
		UserInterface::ph.mapButtonOnBranch(ButtonMap::EDITOBJECTMODEBUTTON, NonButtonMap::SELECTOBJECT, NonButtonMap::SELECTOBJECT);
		
		auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		{
			static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->cursorButtonCallBack(w, i1, i2, i3);
		};
		glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);

	}


	void EditObjectModeButton::cursorPositionCallBack(GLFWwindow* w, double x, double y)
	{
		
		
	}
	void EditObjectModeButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{

		if (action != GLFW_RELEASE)
		{
			/*3 case : 
			1) do not click anything
			2) do click a NonButton
			3) do click a Button*/
			std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };
			if (buttonID == "CLICK_NO_BUTTON") return;
			if (buttonID == NonButtonMap::SELECTOBJECT)
			{
				DeleteObjectButton::printExistingObject();
			}
			else
			{
				ButtonInterface *b = ButtonMap::getButtonByID({ buttonID });
				if (!b)
				{
					if (myobjectNS::ApplicationObjectManager::
						setEditableObject(buttonID))
					{
						UserInterface::deleteAllButtons();
						UserInterface::setButton(ButtonMap::BACKBUTTON);
						UserInterface::ph.mapButtonOnBranch(ButtonMap::EDITOBJECTMODEBUTTON, buttonID, "Editing Object "+buttonID,2.0);
						UserInterface::ph.mapButtonOnBranch(ButtonMap::EDITOBJECTMODEBUTTON, NonButtonMap::ADJUSTSIZE, NonButtonMap::ADJUSTSIZE);
						UserInterface::ph.mapButtonOnBranch(ButtonMap::EDITOBJECTMODEBUTTON, NonButtonMap::ADJUSTCOLOR, NonButtonMap::ADJUSTCOLOR);
						UserInterface::ph.mapButtonOnBranch(ButtonMap::EDITOBJECTMODEBUTTON, NonButtonMap::OBJECTSWITCH, NonButtonMap::OBJECTSWITCH);
					}
					
					return;
				}
					
				UserInterface::buttonFlow.push_back(b);
				b->action();
			}
			
		}
		
	}





}


