#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<userInterface.h>
namespace uiNS {


	void StartButton::action()
	{
		/*UserInterface::deleteAllButtons();*/
	}


	void StartButton::start()
	{
		UserInterface::phc.hideDropDownMenu();
		UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack);
		UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
		UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);
	}





	void StartButton::mainMenu(GLFWwindow* w, int button, int action, int mode)
	{
		/*if (UserInterface::clicked(NonButtonMap::NOBUTTON))	*/
		UserInterface::setFlags(true, false, false);
		UserInterface::phc.hideDropDownMenu();
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		UserInterface::phc.showButton(NonButtonMap::FILE, NonButtonMap::FILE, NonButtonMap::FILE);
		UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON);
		UserInterface::phc.showButton(NonButtonMap::EDITSOUNDS, NonButtonMap::EDITSOUNDS);
		UserInterface::phc.showButton(ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON);
		UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, fpcameraNS::CameraManager::getActiveCameraType());
		UserInterface::phc.showButton(NonButtonMap::QUITBUTTON, NonButtonMap::QUITBUTTON);

	}


	void StartButton::setControls(){
		UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);

		UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
		//StartButton::cursorButtonCallBack(Application::window, 0, 1, 0);

		UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);
	}


	




	void StartButton::resetCallbackFunc()
	{
		UserInterface::phc.hideDropDownMenu();
		UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
		UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack);
		UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);
		cursorButtonCallBack(Application::window, 0, 1, 0);
	}



	void StartButton::load(GLFWwindow* w, int button, int action, int mods)
	{

		if (action == GLFW_RELEASE) return;

		App::projectDataFileName = UserInterface::cursorVStext();
		
		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
			cursorButtonCallBack(Application::window, 0, 1, 0);
		}



		if (App::loadProjectData(App::projectDataFileName))
		{
			
			UserInterface::phc.hideDropDownMenu();
			setControls();
			//UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
			UserInterface::phc.showButton(NonButtonMap::FILE, "LOADCONFIRM", "LOADED PROJECT " + App::projectDataFileName);
			return;
		}
		else {
			UserInterface::phc.showButton(NonButtonMap::FILE, "LOADWARN", "COULD NOT LOAD PROJECT " + App::projectDataFileName);
			setControls();
		}

		
			

	}

	void HightlightSelectedObject(const string& buttonID)
	{
		static bool turnOffNewColl = false;

		collectorNS::ApplicationObjectCollector* newcoll;
		static collectorNS::ApplicationObjectCollector* prevcoll = myobjectNS::ApplicationObjectManager::getObjectByCollectorID(buttonID);
		newcoll = myobjectNS::ApplicationObjectManager::getObjectByCollectorID(buttonID);
		if (newcoll)
		{
			/*light up the object only if i did not already*/
			if (newcoll != prevcoll)
			{
				newcoll->getBody()->AOcolor *= 1.7;
				if (prevcoll && turnOffNewColl)
					prevcoll->getBody()->AOcolor *= 1 / 1.7;
				prevcoll = newcoll;
				turnOffNewColl = true;
			}

		}
		else /*if now the cursor is pointing no object, turn off the last lighetd up object*/
		{
			if (turnOffNewColl)
			{
				prevcoll->getBody()->AOcolor *= 1 / 1.7;
				turnOffNewColl = false;
			}
					
		}
	}


	void StartButton::cursorPositionCallBack_highlightOnly(GLFWwindow* w, double x, double y)
	{
		UserInterface::cursor_x = x;
		UserInterface::cursor_y = y;



		std::string buttonID{ UserInterface::cursorVStext() };
		
		HightlightSelectedObject(buttonID);
		/*else
			prevcoll->getBody()->AOcolor *= 2.0 / 3.0;*/
			
		

		if (buttonID == NonButtonMap::NOBUTTON)
		{
			return;
		}

		ButtonInterface* b = UserInterface::getButtonFromList(buttonID);
		UserInterface::highlightButton(b);
	}








}