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
		UserInterface::bfl.unsetKeyCallback();
	}




	void   StartButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{

		if (action == GLFW_RELEASE) return;
		if (UserInterface::clicked(NonButtonMap::NOBUTTON))	UserInterface::phc.hideDropDownMenu();


		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		UserInterface::phc.showButton(NonButtonMap::FILE, NonButtonMap::FILE, NonButtonMap::FILE);
		UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON);
		UserInterface::phc.showButton(NonButtonMap::EDITSOUNDS, NonButtonMap::EDITSOUNDS);
		UserInterface::phc.showButton(ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON);
		UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, NonButtonMap::CAMERAVIEW);


		

		//FILE DROP DOWN MENU
		{
			if (UserInterface::clicked(NonButtonMap::LOADPROJECT))
			{
				UserInterface::phc.hideDropDownMenu();
				UserInterface::phc.showButton(NonButtonMap::FILE, "SELECT PROJECT DATA TO LOAD");

				vector<string> fileNames;
				logNS::Logger::exploreFolder(logNS::Logger::STOREDDATADIR, fileNames);

				UserInterface::phc.showDropDownMenu(NonButtonMap::FILE, fileNames);

				UserInterface::bfl.setMouseButtonCallback(load);

			}

			if (UserInterface::clicked(NonButtonMap::NEWPROJECT))
			{
				UserInterface::bfl.setMouseButtonCallback(newProjectMouseButton);
				UserInterface::bfl.setKeyCallback(newProjectKey);
				newProjectMouseButton(0, 1);
				newProjectKey(0, 1);
			}


			if (UserInterface::clicked(NonButtonMap::PROGRAMINFOS))
			{
				static size_t i;
				UserInterface::phc.hideDropDownMenu();

				UserInterface::phc.showDropDownMenu(NonButtonMap::FILE,
					{ "This program has been developed using the following libraries :",
					"- OpenGL (graphics)",
					"- GLEW (OpenGL extension Wrangler)",
					"- GLFW (inputs and windows management)",
					"- FreeType (fonts)",
					"- Cyclone (physics integrator and basic collision detection)",
					"- Irrklang (free release of the audio library)",
					"","","","","","Andrea Loforte" });

			}

			if (UserInterface::clicked(ButtonMap::SAVEBUTTON))
			{
				App::SaveProjectData(App::projectDataFileName);
			}


			if (UserInterface::clicked(ButtonMap::QUITANDSAVE))
			{
				App::SaveProjectData(App::projectDataFileName);
				glfwSetWindowShouldClose(Application::window, GLFW_TRUE);
			}
			if (UserInterface::clicked(ButtonMap::QUITNOSAVE))
			{
				glfwSetWindowShouldClose(Application::window, GLFW_TRUE);
			}

		}


		if (UserInterface::clicked("ENTER CONTROL MODE"))
		{
			UserInterface::phc.turnOffAllButtons();
			UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CTRL + E to exit Control mode");
			ControlModeButton::setControls();
		}

		if (UserInterface::clicked(NonButtonMap::SELECTOBJECT))
		{

			UserInterface::printExistingObjects(ButtonMap::EDITOBJECTMODEBUTTON);
			UserInterface::bfl.setMouseButtonCallback(EditObjectModeButton::selectObject);
			UserInterface::bfl.setMouseCursorCallback(EditObjectModeButton::cursorPositionCallBack);


		}

		//EDIT GAME DROP DOWN MENU
		{
			if (UserInterface::clicked(ButtonMap::CREATEBUTTON))
			{
				UserInterface::printAssetObjectsList(ButtonMap::EDITGAMEMODEBUTTON);
				UserInterface::bfl.setMouseButtonCallback(StartButton::createObject);
			}

			if (UserInterface::clicked(ButtonMap::DELETEBUTTON))
			{
				UserInterface::printExistingObjects(ButtonMap::EDITGAMEMODEBUTTON);
				UserInterface::bfl.setMouseButtonCallback(StartButton::deleteObject);
			}
		}


		//CAMERAVIEW DROP DOWN MENU
		{
			if (UserInterface::clicked(NonButtonMap::GROUNDCAMERA));
			if (UserInterface::clicked(NonButtonMap::FLYINGCAMERA));
			if (UserInterface::clicked(NonButtonMap::PANORAMICCAMERA));

		}
		



	}


	



	void StartButton::cursorPositionCallBack(GLFWwindow* w, double x, double y)
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
		if (UserInterface::clicked(NonButtonMap::FILE))
		{

			UserInterface::phc.showDropDownMenu(
				NonButtonMap::FILE,
				{ NonButtonMap::LOADPROJECT,
				NonButtonMap::NEWPROJECT,
				ButtonMap::SAVEBUTTON,
				ButtonMap::QUITANDSAVE,
				ButtonMap::QUITNOSAVE,
				NonButtonMap::PROGRAMINFOS });
			
		}

		if (UserInterface::clicked(ButtonMap::CONTROLMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::CONTROLMODEBUTTON, { "ENTER CONTROL MODE" });	
		}


		if (UserInterface::clicked(ButtonMap::EDITGAMEMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(
				ButtonMap::EDITGAMEMODEBUTTON,{ ButtonMap::CREATEBUTTON,ButtonMap::DELETEBUTTON });
		}


		if (UserInterface::clicked(ButtonMap::EDITOBJECTMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(
				ButtonMap::EDITOBJECTMODEBUTTON, { NonButtonMap::SELECTOBJECT,NonButtonMap::SELECTCLUSTER,NonButtonMap::EDITCLUSTER });

		}

		if (UserInterface::clicked(NonButtonMap::CAMERAVIEW))
		{
			UserInterface::phc.showDropDownMenu(NonButtonMap::CAMERAVIEW,
				{ NonButtonMap::GROUNDCAMERA,NonButtonMap::FLYINGCAMERA,NonButtonMap::PANORAMICCAMERA });
		}

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
		UserInterface::bfl.unsetKeyCallback();
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
		}

		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);
			cursorButtonCallBack(Application::window, 0, 1, 0);
		}
			

	}

	void StartButton::newProjectMouseButton(int key, int action)
	{
		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
			resetCallbackFunc();

	}

	void StartButton::newProjectKey(int key, int action)
	{
		UserInterface::phc.showButton(NonButtonMap::FILE, "TYPEPROJECTNAME", "ENTER PROJECT NAME :" + UserInterface::typer.textTyper.stringInsertion(key, action));
		if (UserInterface::typer.textTyper.completed_total)
		{
			App::projectDataFileName = UserInterface::typer.textTyper.text;
			App::loadProjectData(App::projectDataFileName);

			UserInterface::start->start();
		}

	}



}