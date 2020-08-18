#include<buttons.h>
#include<applicationObjectManager.h>
#include<activeCharacterManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<userInterface.h>
#include<ground.h>
namespace uiNS {

	const string SWITCHAI = "SWITCH AI ON/OFF";
	const string SWITCHPHYSICS = "SWITCH PHYSICS ON/OFF";
	
	void buttonCallback_activeCharacter();
	void exploreFolder();


	void StartButton::setControls_controlMode()
	{
		UserInterface::setFlags(true, true, true);
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);
		UserInterface::bfl.setMouseCursorCallback(InputsNS::Controls::cursor_callback);
		UserInterface::bfl.setMouseButtonCallback(InputsNS::Controls::mouse_button_callback);
		UserInterface::bfl.setMouseScrollCallback(InputsNS::Controls::scroll_callback);
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
				UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack_highlightOnly);

			}

			if (UserInterface::clicked(NonButtonMap::NEWPROJECT))
			{
				
				UserInterface::bfl.setMouseButtonCallback(newProjectMouseButton);
				UserInterface::bfl.setMouseCursorCallback(cursorCallbackNewProject);
				UserInterface::bfl.setKeyCallback(newProjectKey);
				newProjectKey(0, 1);
				newProjectMouseButton(0, 1);

			}

			if (UserInterface::clicked(NonButtonMap::DELETEPROJECT))
			{
				
				exploreFolder();
				
				UserInterface::bfl.setMouseButtonCallback(deleteProjectData);
				UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack_highlightOnly);
				/*UserInterface::bfl.setMouseCursorCallback(cursorCallbackNewProject);
				UserInterface::bfl.setKeyCallback(newProjectKey);
				newProjectKey(0, 1);
				newProjectMouseButton(0, 1);*/

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
				UserInterface::phc.showButton(NonButtonMap::FILE, "SAVECONFIRM", "SAVED");
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


		/*COTROL DROP DOWN MENU*/
		{
			if (UserInterface::clicked("ENTER CONTROL MODE"))
			{
				UserInterface::phc.turnOffAllButtons();
				UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CTRL + E to exit Control mode");
				setControls_controlMode();
			}

			if (UserInterface::clicked(SWITCHAI))
			{
				if (UserInterface::AIon)
				{
					UserInterface::AIon = false;
					UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CONFIRM", "AI off");
				}
					
				else
				{
					UserInterface::AIon = true;
					UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CONFIRM" ,"AI on");
				}
	
			}
			if (UserInterface::clicked(SWITCHPHYSICS))
			{
				if (UserInterface::physicsOn)
				{
					UserInterface::physicsOn = false;
					UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CONFIRM", "physics off");
				}
					
				else
				{
					UserInterface::physicsOn = true;
					UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CONFIRM", "physics on");
				}
					

			}

		}
		



		/*EDIT OBJECT MODE*/
		{
			if (UserInterface::clicked(NonButtonMap::SELECTOBJECT))
				EditObjectModeButton::goToEditObject();


			if (UserInterface::clicked(NonButtonMap::EDITCLUSTER))
				clusterNS::ClusterManager::printClusterList();
			if (UserInterface::clicked(NonButtonMap::CREATECLUSTER))
			{
				EditObjectModeButton::createCluster(Application::window, 0, 1, 0);
			}


			if (UserInterface::clicked(NonButtonMap::GROUND))
			{
				UserInterface::phc.showDropDownMenu(
					ButtonMap::EDITOBJECTMODEBUTTON, myobjectNS::Ground::getGroundList());
			}

			if (UserInterface::clicked(NonButtonMap::ACTIVECHARACTER))
			{
				buttonCallback_activeCharacter();
			}

		}

		
		

		//EDIT GAME DROP DOWN MENU
		{
			if (UserInterface::clicked(ButtonMap::CREATEBUTTON))
			{	
					if ( UserInterface::clicked(ButtonMap::BACKBUTTON) || UserInterface::clicked(NonButtonMap::NOBUTTON))
					{
						UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
						StartButton::mainMenu(Application::window, 0, 0, 0);
						return;
					}
					
					{
						UserInterface::printAssetObjectsList(ButtonMap::EDITGAMEMODEBUTTON);
						UserInterface::bfl.setMouseButtonCallback(StartButton::createObject);
					}	
				
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
				NonButtonMap::DELETEPROJECT,
				ButtonMap::SAVEBUTTON,
				ButtonMap::QUITANDSAVE,
				ButtonMap::QUITNOSAVE,
				NonButtonMap::PROGRAMINFOS });

		}

		if (UserInterface::clicked(ButtonMap::CONTROLMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::CONTROLMODEBUTTON, 
				{ "ENTER CONTROL MODE", SWITCHPHYSICS,SWITCHAI });
		}


		if (UserInterface::clicked(ButtonMap::EDITGAMEMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITGAMEMODEBUTTON,
				{ ButtonMap::CREATEBUTTON,ButtonMap::DELETEBUTTON });
		}


		if (UserInterface::clicked(ButtonMap::EDITOBJECTMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,
				{ NonButtonMap::SELECTOBJECT,
				NonButtonMap::CREATECLUSTER,
				NonButtonMap::SELECTCLUSTER,
				NonButtonMap::GROUND,
				NonButtonMap::ACTIVECHARACTER});

		}



		if (UserInterface::clicked(UserInterface::phc.getPHbyID(NonButtonMap::CAMERAVIEW).getHeader()))
		{
			UserInterface::phc.showDropDownMenu(NonButtonMap::CAMERAVIEW,
				{ NonButtonMap::GROUNDCAMERA,NonButtonMap::FLYINGCAMERA,NonButtonMap::PANORAMICCAMERA });
		}

	}







}