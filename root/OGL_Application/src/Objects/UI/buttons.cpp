#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>


namespace uiNS {

	Button::Button(const string& bID, const string& bName,
		const float& x, const float& y, const float& s) :
		x_min(x),
		y_min(y),
		y_min_frame(y),
		y_max(y),
		textScale(s),
		buttonID(bID),
		buttonName(bName)
	{
		x_max = x_min + textScale * bName.length()*0.06;
		
		/*height is non linear function of text scale!*/
		height = textScale*0.1 ;
		y_min = y_max - height;
		
		y_max = y_min + height;
		/*frames have impact only in the 
		interaction with the cursor*/
		y_min_frame = y_min+0.03;
		y_max_frame = y_max+0.06;// +textScale;

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


	void StartButton::action()
	{
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		auto L_key_callbackControl = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
		{
			static_cast<InputsNS::Controls*>(glfwGetWindowUserPointer(w))->key_callbackControl(w, i1, i2, i3, i4);
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);


		auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
		{
			static_cast<StartButton*>(glfwGetWindowUserPointer(w))->cursorPositionCallBack(w, d1, d2);
		};
		glfwSetCursorPosCallback(Application::window, L_cursor_callback);

		auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		{
			static_cast<StartButton*>(glfwGetWindowUserPointer(w))->cursorButtonCallBack(w, i1, i2, i3);
		};
		glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);

		glfwSetInputMode(Application::window, GLFW_STICKY_KEYS, 1);
		glfwSetWindowUserPointer(Application::window, this);

		using namespace textRendererNS;

		UserInterface::ph.resetPosition();
		UserInterface::setButton(ButtonMap::CONTROLMODEBUTTON);
		UserInterface::setButton(ButtonMap::EDITOBJECTMODEBUTTON);
		UserInterface::setButton( ButtonMap::EDITGAMEMODEBUTTON);
		UserInterface::setButton( ButtonMap::ESCAPEBUTTON);
	

	}


	void StartButton::cursorPositionCallBack(GLFWwindow* w, double x, double y)
	{
		UserInterface::cursor_x = x;
		UserInterface::cursor_y = y;
		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };
		if (buttonID == "CLICK_NO_BUTTON")
		{
			UserInterface::turnOffAllButtons();
			return;
		}
		
		ButtonInterface *b = UserInterface::getButtonFromList(buttonID);
		UserInterface::highlightButton(b);
		
	}

	void   StartButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{
		if (action != GLFW_RELEASE)
		{
			/*must use pointer to enable polymorphism*/
			std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };
			if (buttonID == "CLICK_NO_BUTTON") return;
			ButtonInterface *b = ButtonMap::getButtonByID({ buttonID });
			if (!b)
				return;
			UserInterface::buttonFlow.push_back(b);
			b->action();
		}
	}


	void StartButton::selectObject(GLFWwindow* w, int button, int action, int mode) {}
	
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	void EditGameButton::action()
	{
		using namespace textRendererNS;

		UserInterface::deleteAllButtons();
		
		
		//UserInterface::setButton(ButtonMap::STARTINGBUTTON, ButtonMap::CONTROLMODEBUTTON);
		UserInterface::setButton(ButtonMap::DELETEBUTTON, "Delete an Object");
		UserInterface::setButton(ButtonMap::CREATEBUTTON, "Create an Object");
		UserInterface::setButton(ButtonMap::SAVEBUTTON, "Save project");
		UserInterface::setButton(ButtonMap::BACKBUTTON, "Back");

		return;

	}

	
	void EditGameButton::setControls()
	{
		auto L_key_callbackControl = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
		{
			static_cast<InputsNS::Controls*>(glfwGetWindowUserPointer(w))->key_callbackControl(w, i1, i2, i3, i4);
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);


		auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
		{
			static_cast<StartButton*>(glfwGetWindowUserPointer(w))->cursorPositionCallBack(w, d1, d2);
		};
		glfwSetCursorPosCallback(Application::window, L_cursor_callback);

		auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		{
			static_cast<StartButton*>(glfwGetWindowUserPointer(w))->cursorButtonCallBack(w, i1, i2, i3);
		};
		glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);

		glfwSetInputMode(Application::window, GLFW_STICKY_KEYS, 1);
		glfwSetWindowUserPointer(Application::window, this);

	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	//CreateObjectButton::CreateObjectButton() :Button({ ButtonMap::CREATEBUTTON }){}

	void CreateObjectButton::action()
	{
		
		printAssetObjectList();
		UserInterface::setButton(ButtonMap::BACKBUTTON);

		auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		{
			static_cast<CreateObjectButton*>(glfwGetWindowUserPointer(w))->selectObject(w, i1, i2, i3);
		};
		glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);


		return;

	}


	void CreateObjectButton::printAssetObjectList()
	{

		UserInterface::deleteAllButtons();
		UserInterface::ph.resetPosition();

		std::map<std::string, int>* assetIndex = AssetNS::Assets::getAssetIndex();
		std::map<std::string, int>::iterator it = assetIndex->begin();


		for (it; it != assetIndex->end(); it++)
			UserInterface::ph.mapButtonOnBranch(
				UserInterface::getParentButton()->getButtonID(),
				it->first,
				it->first);

	}



	void CreateObjectButton::selectObject(GLFWwindow*, int button, int action, int mod)
	{
		if (action == GLFW_RELEASE) return;

		string buttonID = UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y);
		if (buttonID == ButtonMap::BACKBUTTON)
		{
			ButtonInterface*b = ButtonMap::getButtonByID({ buttonID });
			b->action();
		}
		else
			myobjectNS::ApplicationObjectManager::
			createNewObject(buttonID);

	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	//BackButton::BackButton() :Button({ ButtonMap::BACKBUTTON }) {}

	
	void BackButton::action()
	{
		UserInterface::ph.resetPosition();

		UserInterface::deleteButtonsByBranch(UserInterface::getParentButton()->getButtonID());
		UserInterface::deleteButtonsByBranch(UserInterface::getParentButton()->getButtonID());
	
		if (UserInterface::buttonFlow.size() == 0)
			UserInterface::buttonFlow.push_back(UserInterface::start);
		UserInterface::buttonFlow.back()->action();
		UserInterface::buttonFlow.back()->setControls();
		
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	void DeleteObjectButton::action()
	{
		printExistingObject();
		

		auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		{
			static_cast<DeleteObjectButton*>(glfwGetWindowUserPointer(w))->selectObject(w, i1, i2, i3);
		};
		glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);


		return;
	}


	void DeleteObjectButton::printExistingObject()
	{
		UserInterface::deleteAllButtons();
		UserInterface::ph.resetPosition();
		UserInterface::setButton(ButtonMap::BACKBUTTON);

		for (int i = 0; i < myobjectNS::ApplicationObjectManager::ApplicationCollectorList.size(); i++)
		{
			string s = 
				myobjectNS::ApplicationObjectManager::
				ApplicationCollectorList[i]->getCollectorID();//+"_"+std::to_string(i);

			UserInterface::ph.mapButtonOnBranch(
				UserInterface::getParentButton()->getButtonID(),
				s,
				s);
		}

		
	}



	void DeleteObjectButton::selectObject(GLFWwindow* w,int button, int action, int mode)
	{
		if (action == GLFW_RELEASE) return;
		

		string buttonID = UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y);
		if (buttonID == ButtonMap::BACKBUTTON)
		{
			ButtonInterface*b = ButtonMap::getButtonByID({ buttonID });
			b->action();
		}
		else
		{
			myobjectNS::ApplicationObjectManager::
				deleteObject(buttonID);
			DeleteObjectButton::action();
		}
	}


	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////


	void ControlModeButton::action()
	{
		UserInterface::deleteButtonsByBranch(ButtonMap::STARTINGBUTTON);
	
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		auto L_key_callbackControl = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
		{
			static_cast<InputsNS::Controls*>(glfwGetWindowUserPointer(w))->key_callbackControl(w, i1, i2, i3, i4);
		};
		glfwSetKeyCallback(Application::window, L_key_callbackControl);


		auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
		{
			static_cast<InputsNS::Controls*>(glfwGetWindowUserPointer(w))->cursor_callback(w, d1, d2);
		};
		glfwSetCursorPosCallback(Application::window, L_cursor_callback);

		auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		{
			static_cast<InputsNS::Controls*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, i1, i2, i3);
		};
		glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);

		auto L_mouse_scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset)
		{
			static_cast<InputsNS::Controls*>(glfwGetWindowUserPointer(window))->scroll_callback(window, xoffset,yoffset);
		};
		glfwSetScrollCallback(Application::window, L_mouse_scroll_callback);


		/*glfwSetInputMode(Application::window, GLFW_STICKY_KEYS, 1);
		glfwSetWindowUserPointer(Application::window, this);*/

	}

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////


	void SaveButton::action()
	{
		using namespace textRendererNS;
		UserInterface::ph.mapButtonOnBranch
		(UserInterface::getParentButton()->getButtonID(), UserInterface::buttonFlow.back()->getButtonID(), "SAVED");
		App::SaveProjectData(App::projectDataFileName);
	}

	void QuitButton::action()
	{
		
		UserInterface::deleteAllButtons();		
		UserInterface::setButton(ButtonMap::QUITANDSAVE);
		UserInterface::setButton(ButtonMap::QUITNOSAVE);
		UserInterface::setButton(ButtonMap::BACKBUTTON);
	}

	void QuitAndSaveButton::action()
	{
		App::SaveProjectData(App::projectDataFileName);
		glfwSetWindowShouldClose(Application::window, GLFW_TRUE);
	}

	void QuitNoSaveButton::action()
	{
		glfwSetWindowShouldClose(Application::window, GLFW_TRUE);
	}

	

}