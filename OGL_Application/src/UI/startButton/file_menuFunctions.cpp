#include<buttons.h>
#include<applicationObjectManager.h>
#include<activeCharacterManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<userInterface.h>
#include<ground.h>
namespace uiNS {

	void exploreFolder()
	{
		vector<string> v;
		logNS::Logger::exploreFolder(logNS::Logger::STOREDDATADIR, v);
		UserInterface::phc.showDropDownMenu(NonButtonMap::FILE, v);
		UserInterface::phc.showButton(NonButtonMap::FILE, ButtonMap::BACKBUTTON);
		
	}

	vector<string> exploreFolder_noprint()
	{
		vector<string> v;
		logNS::Logger::exploreFolder(logNS::Logger::STOREDDATADIR, v);
		return v;
	}



	void StartButton::load(GLFWwindow* w, int button, int action, int mods)
	{

		if (action == GLFW_RELEASE) return;

		App::projectDataFileName = UserInterface::cursorVStext();

		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
			UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack);
			mainMenu(Application::window, 0, 0, 0);
			return;
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


	void StartButton::deleteProjectData(GLFWwindow* w, int button, int action, int mods)
	{


		string projectName = UserInterface::cursorVStext();


		if (UserInterface::clicked(ButtonMap::BACKBUTTON) || UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			setControls();
			mainMenu(Application::window, 0, 0, 0);
			return;
		}
		
		
		if (logNS::Logger::deleteProjectData(projectName))
		{
			StartButton::showProjectsList();
			UserInterface::phc.showButton(NonButtonMap::FILE, projectName + " data file deleted");
			logNS::Logger::updateProjectsListFile();
		}
		else {
			//UserInterface::phc.hideDropDownMenu();
			UserInterface::phc.showButton(NonButtonMap::FILE, "could not delete project file " + projectName);
			//setControls();
		}

	}

	


	void StartButton::cursorCallbackNewProject(GLFWwindow* w, double x, double y)
	{
		UserInterface::cursor_x = x;
		UserInterface::cursor_y = y;
		std::string buttonID{ UserInterface::cursorVStext() };
		ButtonInterface* b = UserInterface::getButtonFromList(buttonID);
		UserInterface::highlightButton(b);
	}

	void StartButton::newProjectMouseButton(int key, int action)
	{
		if (UserInterface::clicked(NonButtonMap::NOBUTTON) || UserInterface::clicked(ButtonMap::BACKBUTTON))
		{
			UserInterface::typer.textTyper.reset();
			mainMenu(Application::window, 0, 1, 0);
			setControls();
		}
	}

	void StartButton::newProjectKey(int key, int action)
	{
		UserInterface::phc.showButton(NonButtonMap::FILE, "TYPEPROJECTNAME", "ENTER PROJECT NAME :" + UserInterface::typer.textTyper.stringInsertion(key, action));
		UserInterface::phc.showButton(NonButtonMap::FILE, ButtonMap::BACKBUTTON);
		if (UserInterface::typer.textTyper.completed_total)
		{
			UserInterface::phc.hideDropDownMenu();
			UserInterface::phc.showButton(NonButtonMap::FILE, "NEWPROJECTCONFIRM", "NEW PROJECT CREATED");
			UserInterface::phc.showButton(NonButtonMap::FILE, "NEWPROJECTHINT", "Use Edit Project to create new objects, and start creating your world", 1, 0.2);
			App::projectDataFileName = UserInterface::typer.textTyper.text;
			App::loadProjectData(App::projectDataFileName);
			setControls();
		}

	}



}