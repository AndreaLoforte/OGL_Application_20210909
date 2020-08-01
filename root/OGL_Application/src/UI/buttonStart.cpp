#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<buttonfunctionlist.h>
namespace uiNS {

	void StartButton::menu()
	{
		UserInterface::deleteAllButtons();
		UserInterface::showButton("LOAD PROJECT", "LOAD PROJECT");
		UserInterface::showButton("NEW PROJECT", "NEW PROJECT");
		UserInterface::ShowBackButton();

		if (UserInterface::clicked("LOAD PROJECT"))
		{
			UserInterface::clickButton("LOAD PROJECT");
			UserInterface::bfl.setMouseButtonCallback(load);
			load();
		}


		if (UserInterface::clicked("NEW PROJECT"))
		{
			UserInterface::bfl.setMouseButtonCallback(newProject);
			UserInterface::bfl.setKeyCallback(newProject);
			newProject(0, 0);
		}
			



		if (UserInterface::clicked(ButtonMap::BACKBUTTON))
			UserInterface::back();
	}


	void StartButton::load()
	{
		UserInterface::deleteAllButtons();
		UserInterface::showButton("SELECT PROJECT DATA TO LOAD", "SELECT PROJECT DATA TO LOAD");
		vector<string> fileNames;
		logNS::Logger::exploreFolder(logNS::Logger::STOREDDATADIR, fileNames);

		for (int i = 0; i < fileNames.size(); i++)
			UserInterface::showButton(fileNames[i], fileNames[i]);

		string projectfilename{ UserInterface::cursorVStext() };


		if (App::loadProjectData(projectfilename))
		{
			/*we can't access load project using back!*/
			UserInterface::deleteAllButtons();
			UserInterface::buttonFlow.clear();
			UserInterface::buttonFlow.push_back(UserInterface::start);
			myobjectNS::ApplicationObjectManager::setupObjectsParameters();

			
			UserInterface::start->start();
		}

		
			
	}

	void StartButton::newProject(int key,int action)
	{
		string newFilename = UserInterface::typer.stringInsertion(key, action);
		if(!UserInterface::typer.completed_total)
			UserInterface::showButton("TYPEPROJECTNAME", " ENTER PROJECT NAME "+ newFilename);
		else
			
		UserInterface::ShowBackButton();
		if (UserInterface::clicked(ButtonMap::BACKBUTTON))
			UserInterface::back();
		


	}




	void StartButton::action()
	{
		UserInterface::deleteAllButtons();
		start();
	}


	void StartButton::start()
	{
		UserInterface::deleteAllButtons();
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		UserInterface::showButton(ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON);
		UserInterface::showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON);
		UserInterface::showButton(ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON);
		UserInterface::showButton(NonButtonMap::CHANGEPROJECT, NonButtonMap::CHANGEPROJECT);
		UserInterface::showButton(ButtonMap::ESCAPEBUTTON, ButtonMap::ESCAPEBUTTON);
		UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
		UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack);
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
			/*Control mode is not in the "normal flow" so we can't
			go back() to control */
			//UserInterface::clickButton(buttonID);
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
			UserInterface::bfl.setMouseButtonCallback(QuitButton::showMenu);
			QuitButton b;
			b.action();
		}
		if (UserInterface::clicked(NonButtonMap::CHANGEPROJECT))
		{
			UserInterface::bfl.setMouseButtonCallback(menu);
			UserInterface::clickButton(NonButtonMap::CHANGEPROJECT);
			menu();
		}






	}


	void StartButton::keyCallBack_startMenu(GLFWwindow* w, int key, int scancode, int action, int mode)
	{
		

	}

	void StartButton::selectObject(GLFWwindow* w, int button, int action, int mode) {}

}