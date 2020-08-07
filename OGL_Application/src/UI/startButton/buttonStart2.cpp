#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<userInterface.h>
namespace uiNS {


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
			App::projectDataFileName = UserInterface::typer.textTyper.text;
			App::loadProjectData(App::projectDataFileName);

			//	UserInterface::start->start();
		}

	}



	void   StartButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{


		if (action == GLFW_RELEASE) return;
		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
			UserInterface::phc.hideDropDownMenu();

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
				UserInterface::bfl.setMouseCursorCallback(cursorCallbackNewProject);
				UserInterface::bfl.setKeyCallback(newProjectKey);
				newProjectKey(0, 1);
				newProjectMouseButton(0, 1);

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
				glfwSetWindowShouldClose(Application::window, GLFW_TRUE);


			if (UserInterface::clicked(NonButtonMap::QUITBUTTON))
				glfwSetWindowShouldClose(Application::window, GLFW_TRUE);


		}


		/*CAMERA DROP DOWN MENU*/
		{


			if (UserInterface::clicked(NonButtonMap::FLYINGCAMERA))
			{
				fpcameraNS::CameraManager::setActiveCameraIndex(1);
				UserInterface::phc.substituteButton(NonButtonMap::CAMERAVIEW, NonButtonMap::FLYINGCAMERA, NonButtonMap::FLYINGCAMERA, 0);
				UserInterface::phc.hideDropDownMenu(NonButtonMap::CAMERAVIEW, 0);
				UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, NonButtonMap::FLYINGCAMERA);

			}

			if (UserInterface::clicked(NonButtonMap::GROUNDCAMERA))
			{
				fpcameraNS::CameraManager::setActiveCameraIndex(0);
				UserInterface::phc.substituteButton(NonButtonMap::CAMERAVIEW, NonButtonMap::GROUNDCAMERA, NonButtonMap::GROUNDCAMERA, 0);
				UserInterface::phc.hideDropDownMenu(NonButtonMap::CAMERAVIEW, 0);
				UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, NonButtonMap::GROUNDCAMERA);

			}

			if (UserInterface::clicked(NonButtonMap::PANORAMICCAMERA))
			{
				fpcameraNS::CameraManager::setActiveCameraIndex(2);
				UserInterface::phc.substituteButton(NonButtonMap::CAMERAVIEW, NonButtonMap::PANORAMICCAMERA, NonButtonMap::PANORAMICCAMERA, 0);
				UserInterface::phc.hideDropDownMenu(NonButtonMap::CAMERAVIEW, 0);
				UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, NonButtonMap::PANORAMICCAMERA);
			}



		}






		if (UserInterface::clicked("ENTER CONTROL MODE"))
		{
			UserInterface::phc.turnOffAllButtons();
			UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CTRL + E to exit Control mode");
			ControlModeButton::setControls();
		}



		/*EDIT OBJECT MODE*/
		{
			if (UserInterface::clicked(NonButtonMap::SELECTOBJECT))
				EditObjectModeButton::showObjectsList();


			if (UserInterface::clicked(NonButtonMap::EDITCLUSTER))
				clusterNS::ClusterManager::printClusterList();
			if (UserInterface::clicked(NonButtonMap::CREATECLUSTER))
			{
				EditObjectModeButton::createCluster(Application::window, 0, 1, 0);
			

			}
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

	}



	

	void StartButton::cursorPositionCallBack(GLFWwindow* w, double x, double y)
	{
		UserInterface::cursor_x = x;
		UserInterface::cursor_y = y;



		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			//resetCallbackFunc();
			return;
		}


		std::string buttonID{ UserInterface::cursorVStext() };
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
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITGAMEMODEBUTTON,
				{ ButtonMap::CREATEBUTTON,ButtonMap::DELETEBUTTON });
		}


		if (UserInterface::clicked(ButtonMap::EDITOBJECTMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,
				{ NonButtonMap::SELECTOBJECT,NonButtonMap::CREATECLUSTER,NonButtonMap::SELECTCLUSTER});

		}



		if (UserInterface::clicked(UserInterface::phc.getPHbyID(NonButtonMap::CAMERAVIEW).getHeader()))
		{
			UserInterface::phc.showDropDownMenu(NonButtonMap::CAMERAVIEW,
				{ NonButtonMap::GROUNDCAMERA,NonButtonMap::FLYINGCAMERA,NonButtonMap::PANORAMICCAMERA });
		}

	}





}