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


	



	void StartButton::createObject()
	{
		string buttonID{ UserInterface::cursorVStext() };

		if (!myobjectNS::ApplicationObjectManager::createNewObject(buttonID) || UserInterface::clicked(NonButtonMap::NOBUTTON))
			resetCallbackFunc();			
	}

	void StartButton::deleteObject()
	{
		string buttonID{ UserInterface::cursorVStext() };

		if (!myobjectNS::ApplicationObjectManager::deleteObject(buttonID) || UserInterface::clicked(NonButtonMap::NOBUTTON))
			resetCallbackFunc();
		else
			UserInterface::printExistingObjects(ButtonMap::EDITGAMEMODEBUTTON);
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

		if (App::loadProjectData(App::projectDataFileName))
		{
			myobjectNS::ApplicationObjectManager::setupObjectsParameters();
			UserInterface::phc.hideDropDownMenu();
			UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
			UserInterface::phc.showButton(NonButtonMap::FILE, "LOADCONFIRM", "LOADED PROJECT " + App::projectDataFileName);
			return;
		}
		else {
			UserInterface::phc.showButton(NonButtonMap::FILE, "LOADWARN", "COULD NOT LOAD PROJECT " + App::projectDataFileName);
		}

		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
			cursorButtonCallBack(Application::window, 0, 1, 0);
		}
			

	}



	void StartButton::cursorPositionCallBack_highlightOnly(GLFWwindow* w, double x, double y)
	{
		UserInterface::cursor_x = x;
		UserInterface::cursor_y = y;



		std::string buttonID{ UserInterface::cursorVStext() };
		if (buttonID == NonButtonMap::NOBUTTON)
		{
			//UserInterface::phc.hideDropDownMenu();
			return;
		}

		ButtonInterface* b = UserInterface::getButtonFromList(buttonID);
		UserInterface::highlightButton(b);
	}






}