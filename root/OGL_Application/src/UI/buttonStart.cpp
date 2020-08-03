#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<userInterface.h>
namespace uiNS {
	bool StartButton::nogoback;
	

	void StartButton::menu()
	{
		//glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//UserInterface::phc.showButton(NonButtonMap::FILE, NonButtonMap::FILE, NonButtonMap::FILE,0);
		//UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON,0);
		//UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON,0);
		//UserInterface::phc.showButton(ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON,0);


		//if (UserInterface::clicked(NonButtonMap::PROGRAMINFOS))
		//{
		//	static size_t i;
		//	UserInterface::phc.hideDropDownMenu();

		//	UserInterface::phc.showDropDownMenu(NonButtonMap::FILE,
		//		{ "This program has been developed using the following libraries :",
		//		"- OpenGL (graphics)",
		//		"- GLEW (OpenGL extension Wrangler)",
		//		"- GLFW (inputs and windows management)",
		//		"- FreeType (fonts)",
		//		"- Cyclone (physics integrator and basic collision detection)",
		//		"- Irrklang (free release of the audio library)",
		//		"","","","","","Andrea Loforte" });
		//	
		//}



		//if (UserInterface::clicked(NonButtonMap::LOADPROJECT))
		//{
		//	//UserInterface::clickButton(NonButtonMap::LOADPROJECT);
		//	UserInterface::bfl.setMouseButtonCallback(load);
		//	load();
		//}


		//if (UserInterface::clicked("NEW PROJECT"))
		//{
		//	UserInterface::bfl.setMouseButtonCallback(newProject);
		//	UserInterface::bfl.setKeyCallback(newProject);
		//	newProject(0, 0);
		//}
		//	

		//if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		//{
		//	UserInterface::phc.hideDropDownMenu();
		//	//UserInterface::back();
		//	//UserInterface::phc.showButton(NonButtonMap::FILE, NonButtonMap::FILE, NonButtonMap::FILE);
		//	
		//}
		
	}


	void StartButton::load(GLFWwindow*w,int button,int action,int mods)
	{

		if (action == GLFW_RELEASE) return;
		
		

		App::projectDataFileName =  UserInterface::cursorVStext() ;

		if (App::loadProjectData(App::projectDataFileName))
		{
			myobjectNS::ApplicationObjectManager::setupObjectsParameters();
			UserInterface::phc.hideDropDownMenu();
			UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
		}
		else
		{
			UserInterface::phc.showButton(NonButtonMap::FILE, "COULDN'T LOAD THIS FILE");
		}

		//UserInterface::ShowBackButton();
		/*if (UserInterface::clicked(ButtonMap::BACKBUTTON))
			UserInterface::back();*/


			
	}

	void StartButton::newProject(int key,int action)
	{
		App::projectDataFileName = UserInterface::typer.stringInsertion(key, action);
		if (!UserInterface::typer.completed_total)
			UserInterface::phc.showButton(NonButtonMap::FILE, "TYPEPROJECTNAME", "ENTER PROJECT NAME " + App::projectDataFileName);
		else
		{
			App::loadProjectData(App::projectDataFileName);
			UserInterface::start->start();
		}
			
			
		//UserInterface::ShowBackButton();
		if (UserInterface::clicked(ButtonMap::BACKBUTTON))
		{
			UserInterface::back();
			nogoback = true;
		}
			
		


	}




	void StartButton::action()
	{
		/*UserInterface::deleteAllButtons();*/
		menu();
	}


	void StartButton::start()
	{
		
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
				NonButtonMap::PROGRAMINFOS });
			
		}

		if (UserInterface::clicked(ButtonMap::CONTROLMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::CONTROLMODEBUTTON, { "ENTER CONTROL MODE" });	
		}


		if (UserInterface::clicked(ButtonMap::EDITGAMEMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(
				ButtonMap::EDITGAMEMODEBUTTON,{ ButtonMap::CREATEBUTTON,ButtonMap::DELETEBUTTON,ButtonMap::SAVEBUTTON });
		}


		if (UserInterface::clicked(ButtonMap::EDITOBJECTMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(
				ButtonMap::EDITOBJECTMODEBUTTON, { NonButtonMap::SELECTOBJECT,NonButtonMap::SELECTCLUSTER,NonButtonMap::EDITCLUSTER });

		}

			

	}

	void   StartButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{

		if (action == GLFW_RELEASE) return;
		

		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		UserInterface::phc.showButton(NonButtonMap::FILE, NonButtonMap::FILE, NonButtonMap::FILE, 0);
		UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON, ButtonMap::CONTROLMODEBUTTON, 0);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::EDITOBJECTMODEBUTTON, 0);
		UserInterface::phc.showButton(ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON, ButtonMap::EDITGAMEMODEBUTTON, 0);


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



		if (UserInterface::clicked(NonButtonMap::LOADPROJECT))
		{
			UserInterface::phc.hideDropDownMenu();
			UserInterface::phc.showButton(NonButtonMap::FILE, "SELECT PROJECT DATA TO LOAD", "SELECT PROJECT DATA TO LOAD");
			vector<string> fileNames;
			logNS::Logger::exploreFolder(logNS::Logger::STOREDDATADIR, fileNames);

			for (int i = 0; i < fileNames.size(); i++)
				UserInterface::phc.showButton(NonButtonMap::FILE, fileNames[i], fileNames[i]);



			//UserInterface::clickButton(NonButtonMap::LOADPROJECT);
			UserInterface::bfl.setMouseButtonCallback(load);
			
		}


		if (UserInterface::clicked("NEW PROJECT"))
		{
			UserInterface::bfl.setMouseButtonCallback(newProject);
			UserInterface::bfl.setKeyCallback(newProject);
			newProject(0, 0);
		}


		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			UserInterface::phc.hideDropDownMenu();
			//UserInterface::back();
			//UserInterface::phc.showButton(NonButtonMap::FILE, NonButtonMap::FILE, NonButtonMap::FILE);

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
//			UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::BACKBUTTON);
			UserInterface::bfl.setMouseButtonCallback(EditObjectModeButton::selectObject);
			UserInterface::bfl.setMouseCursorCallback(EditObjectModeButton::cursorPositionCallBack);
			/*UserInterface::bfl.setMouseButtonCallback(EditObjectModeButton::cursorButtonCallBack);
			EditObjectModeButton::cursorButtonCallBack(Application::window, 0, 1, 0);*/
		
		}
		/*
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
		}*/






	}


	void StartButton::keyCallBack_startMenu(GLFWwindow* w, int key, int scancode, int action, int mode)
	{
		

	}

	void StartButton::selectObject(GLFWwindow* w, int button, int action, int mode) {}

}