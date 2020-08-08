#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>


namespace uiNS {

	Button::Button(const string& bID, const string& bName,
		const float& x, const float& y, const unsigned& buttonLVL, const float& s) :
		x_min(x),
		y_min(y),
		y_min_frame(y),
		y_max(y),
		textScale(s),
		buttonID(bID),
		buttonName(bName),
		buttonLevel(buttonLVL)
	{
		x_max = x_min + textScale * bName.length()*0.06;
		
		/*height is non linear function of text scale!*/
		//below my best guess as far : 
		constexpr float f1 = 0.05;
		
		float f2 = f1 * (8- textScale*.9);/*5 per 0.3 e 2, 8 per 0.6-1.3*/
		height = (f1*textScale + pow(f1*textScale, 1.0-textScale*f2)); 
		y_min -= height;
		
		/*frames have impact only in the 
		interaction with the cursor*/
		y_min_frame = y_min+0.03;
		y_max_frame = y_max+0.06;

	}


	void ButtonInterface::Highligt()
	{
		frameColor[0] = 1.0;
		frameColor[1] = 1.0;
		frameColor[2] = 1.0;
		frameColor[3] = 1.0;

		isHighligted = true;
	}

	void ButtonInterface::turnOff()
	{

		frameColor[3] = 0.5;
		isHighligted = false;
	}






	void EditGameButton::action()
	{
		UserInterface::setFlags(false, false, false);
		/*UserInterface::deleteAllButtons();*/
		
		/*UserInterface::showButton(ButtonMap::DELETEBUTTON, "Delete an Object");
		UserInterface::showButton(ButtonMap::CREATEBUTTON, "Create an Object");
		UserInterface::showButton(ButtonMap::SAVEBUTTON, "Save project");
		UserInterface::showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);*/
		
		UserInterface::bfl.setMouseButtonCallback(setControls);
		return;

	}

	
	void EditGameButton::setControls()
	{
		std::string buttonID{ UserInterface::cursorVStext() };
		//UserInterface::enableBack(buttonID);

		if (buttonID == NonButtonMap::NOBUTTON) return;

		if (buttonID == ButtonMap::DELETEBUTTON)
		{
			//UserInterface::printExistingObjects();

			UserInterface::bfl.setMouseButtonCallback(DeleteObjectButton::selectObject);

		}

		if (buttonID == ButtonMap::CREATEBUTTON)
		{
		
			//UserInterface::printAssetObjectsList();
			UserInterface::bfl.setMouseButtonCallback(CreateObjectButton::selectObject);

		}

		if (buttonID == ButtonMap::SAVEBUTTON)
		{

		}
		if (buttonID == ButtonMap::BACKBUTTON)
		{

		}




	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////


	void CreateObjectButton::action(){}

	void CreateObjectButton::selectObject(GLFWwindow*, int button, int action, int mod)
	{
		if (action == GLFW_RELEASE) return;

		string buttonID = UserInterface::cursorVStext();

		if (buttonID == NonButtonMap::NOBUTTON) return;
		
		myobjectNS::ApplicationObjectManager::createNewObject(buttonID);

	}

	
	void BackButton::action()
	{
		//UserInterface::phc.resetPosition();

		/*UserInterface::deleteButtonsByBranch(UserInterface::getParentButton()->getButtonID());
		UserInterface::deleteButtonsByBranch(UserInterface::getParentButton()->getButtonID());*/
	
		if (UserInterface::buttonFlow.size() == 0)
			UserInterface::buttonFlow.push_back(UserInterface::start);
		UserInterface::buttonFlow.back()->action();
		UserInterface::buttonFlow.back()->setControls();
		
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	void DeleteObjectButton::action(){}


	


	void DeleteObjectButton::selectObject(GLFWwindow* w,int button, int action, int mode)
	{
		if (action == GLFW_RELEASE) return;
		

		string buttonID = UserInterface::cursorVStext();
		
		if (buttonID == ButtonMap::BACKBUTTON);/*UserInterface::back();*/
		if (buttonID == NonButtonMap::NOBUTTON) return;
		if (myobjectNS::ApplicationObjectManager::deleteObject(buttonID))
		{
			//UserInterface::printExistingObjects();
			/*UserInterface::showButton("DELETED", buttonID + " deleted");
			UserInterface::showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);*/
		}
			
		//DeleteObjectButton:action();
		
	}


	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////


	void ControlModeButton::action()
	{
		//UserInterface::deleteAllButtons();
		//UserInterface::setFlags(false, true, true);
		////UserInterface::showButton("CONTROLMODEINFO", "CTRL+E to exit Control Mode");
		//glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);
		//UserInterface::bfl.setMouseCursorCallback(InputsNS::Controls::cursor_callback);
		//UserInterface::bfl.setMouseButtonCallback(InputsNS::Controls::mouse_button_callback);
		//UserInterface::bfl.setMouseScrollCallback(InputsNS::Controls::scroll_callback);
	}

	void ControlModeButton::setControls()
	{
		//UserInterface::deleteAllButtons();
		UserInterface::setFlags(false, true, true);
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);
		UserInterface::bfl.setMouseCursorCallback(InputsNS::Controls::cursor_callback);
		UserInterface::bfl.setMouseButtonCallback(InputsNS::Controls::mouse_button_callback);
		UserInterface::bfl.setMouseScrollCallback(InputsNS::Controls::scroll_callback);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	void QuitButton::action()
	{
		showMenu();
	}

	void QuitButton::showMenu()
	{

		
		UserInterface::phc.showDropDownMenu(NonButtonMap::QUITBUTTON,
			{ ButtonMap::QUITANDSAVE,ButtonMap::QUITNOSAVE, ButtonMap::BACKBUTTON });


		if (UserInterface::clicked(ButtonMap::QUITANDSAVE))
		{
			App::SaveProjectData(App::projectDataFileName);
			glfwSetWindowShouldClose(Application::window, GLFW_TRUE);
		}

		if(UserInterface::clicked(ButtonMap::QUITNOSAVE))
			glfwSetWindowShouldClose(Application::window, GLFW_TRUE);

		
		if (UserInterface::clicked(ButtonMap::BACKBUTTON))
			;/*UserInterface::back();*/


	}


}