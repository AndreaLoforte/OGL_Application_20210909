#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<buttonfunctionlist.h>
namespace uiNS {


	void StartButton::action()
	{
		/*UserInterface::parentFlow.clear();
		UserInterface::parentFlow.push_back(new StartButton());*/

		UserInterface::paused = true;
		//UserInterface::deleteAllButtons();

		UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
		UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


		UserInterface::showButton(ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON);
		UserInterface::showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON);
		UserInterface::showButton(ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON);
		UserInterface::showButton(ButtonMap::ESCAPEBUTTON, ButtonMap::ESCAPEBUTTON);


	}


	void StartButton::cursorPositionCallBack(GLFWwindow* w, double x, double y)
	{
		UserInterface::cursor_x = x;
		UserInterface::cursor_y = y;
		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };
		if (buttonID == NonButtonMap::NOBUTTON)
		{
			UserInterface::turnOffAllButtons();
			return;
		}

		ButtonInterface* b = UserInterface::getButtonFromList(buttonID);
		UserInterface::highlightButton(b);

	}

	void   StartButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{
		

		if (action == GLFW_RELEASE) return;

		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };

		if (buttonID == NonButtonMap::NOBUTTON) return;

		if (buttonID == ButtonMap::CONTROLMODEBUTTON)
		{
			UserInterface::clickButton(buttonID);
			ControlModeButton b;
			b.action();
		}

		if (buttonID == ButtonMap::EDITOBJECTMODEBUTTON)
		{
			UserInterface::clickButton(buttonID);
			EditObjectModeButton b;
			b.action();
		}

		if (buttonID == ButtonMap::EDITGAMEMODEBUTTON)
		{
			UserInterface::clickButton(buttonID);
			EditGameButton b;
			b.action();
		}
		if (buttonID == ButtonMap::ESCAPEBUTTON)
		{
			UserInterface::clickButton(buttonID);
			QuitButton b;
			b.action();
		}
	}


	void StartButton::keyCallBack_startMenu(GLFWwindow* w, int key, int scancode, int action, int mode)
	{
		

	}

	void StartButton::selectObject(GLFWwindow* w, int button, int action, int mode) {}

}