#include<buttons.h>
#include<applicationObjectManager.h>
#include<activeObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<buttonEditSounds.h>
#include<userInterface.h>
#include<ground.h>
namespace uiNS {

	const string SWITCHAI = "SWITCH AI ON/OFF";
	const string SWITCHPHYSICS = "SWITCH PHYSICS ON/OFF";
	
	void buttonCallback_activeCharacter();
	void exploreFolder();


	void StartButton::setControls_controlMode()
	{
		UserInterface::setFlags(false, true, true);
		glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);
		UserInterface::bfl.setMouseCursorCallback(InputsNS::Controls::cursor_callback);
		UserInterface::bfl.setMouseButtonCallback(InputsNS::Controls::mouse_button_callback);
		UserInterface::bfl.setMouseScrollCallback(InputsNS::Controls::scroll_callback);
	}


	void StartButton::showProjectsList()
	{
		vector<string> fileNames;
		std::string projectsListFile = logNS::Logger::PROJECTMAINDIR + App::defaultProjectFileName;
		std::ifstream in(projectsListFile);
		unsigned i = 0;
		string s;
		while (in.is_open() && !in.eof())
		{
			getline(in, s);
			fileNames.push_back(s);
		}

		UserInterface::phc.showDropDownMenu(NonButtonMap::FILE, fileNames);
	}

	
	/*QUANDO CLICCO COL MOUSE SU UNO DEI PULSANTI DEI MENU' A TENDINA VIENE RICHIAMATA
	QUESTA FUNZIONE. PER CAPIRE QUALE PULSANTE DELLA TENDINA HO CLICCATO USO SEMPRE LA FUNZIONE
	"CURSORPOINTING" E CHIAMO LA FUNZIONE OPPORTUNA*/
	void   StartButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{


		if (action == GLFW_RELEASE) return;
		if (UserInterface::cursorPointing(NonButtonMap::NOBUTTON))
			UserInterface::phc.hideDropDownMenu();

		//FILE DROP DOWN MENU
		{
			if (UserInterface::cursorPointing(NonButtonMap::LOADPROJECT))
			{
				UserInterface::phc.hideDropDownMenu();
				UserInterface::phc.showButton(NonButtonMap::FILE, "SELECT PROJECT DATA TO LOAD");
				showProjectsList();

				UserInterface::bfl.setMouseButtonCallback(load);
				UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack_highlightOnly);

			}

			if (UserInterface::cursorPointing(NonButtonMap::NEWPROJECT))
			{
				
				UserInterface::bfl.setMouseButtonCallback(newProjectMouseButton);
				UserInterface::bfl.setMouseCursorCallback(cursorCallbackNewProject);
				UserInterface::bfl.setKeyCallback(newProjectKey);
				newProjectKey(0, 1);
				newProjectMouseButton(0, 1);

			}

			if (UserInterface::cursorPointing(NonButtonMap::DELETEPROJECT))
			{
				showProjectsList();
				
				UserInterface::bfl.setMouseButtonCallback(deleteProjectData);
				UserInterface::bfl.setMouseCursorCallback(cursorPositionCallBack_highlightOnly);

			}


			if (UserInterface::cursorPointing(NonButtonMap::PROGRAMINFOS))
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

			if (UserInterface::cursorPointing(ButtonMap::SAVEBUTTON))
			{
				App::SaveProjectData(App::projectDataFileName);
				UserInterface::phc.showButton(NonButtonMap::FILE, "SAVECONFIRM", "SAVED");
			}


			if (UserInterface::cursorPointing(ButtonMap::QUITANDSAVE))
			{
				App::SaveProjectData(App::projectDataFileName);
				glfwSetWindowShouldClose(Application::window, GLFW_TRUE);
			}
			if (UserInterface::cursorPointing(ButtonMap::QUITNOSAVE))
				glfwSetWindowShouldClose(Application::window, GLFW_TRUE);


			if (UserInterface::cursorPointing(NonButtonMap::QUITBUTTON))
				glfwSetWindowShouldClose(Application::window, GLFW_TRUE);


		}


		/*CAMERA DROP DOWN MENU*/
		{


			if (UserInterface::cursorPointing(NonButtonMap::FLYINGCAMERA))
			{
				fpcameraNS::CameraManager::setActiveCameraIndex(fpcameraNS::FLYING_CAMERA_INDEX);
				UserInterface::phc.substituteButton(NonButtonMap::CAMERAVIEW, NonButtonMap::FLYINGCAMERA, NonButtonMap::FLYINGCAMERA, 0);
				UserInterface::phc.hideDropDownMenu(NonButtonMap::CAMERAVIEW, 0);
				UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, NonButtonMap::FLYINGCAMERA);

			}

			if (UserInterface::cursorPointing(NonButtonMap::GROUNDCAMERA))
			{
				fpcameraNS::CameraManager::setActiveCameraIndex(fpcameraNS::GROUND_CAMERA_INDEX);
				UserInterface::phc.substituteButton(NonButtonMap::CAMERAVIEW, NonButtonMap::GROUNDCAMERA, NonButtonMap::GROUNDCAMERA, 0);
				UserInterface::phc.hideDropDownMenu(NonButtonMap::CAMERAVIEW, 0);
				UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, NonButtonMap::GROUNDCAMERA);

			}

			if (UserInterface::cursorPointing(NonButtonMap::PANORAMICCAMERA))
			{
				fpcameraNS::CameraManager::setActiveCameraIndex(fpcameraNS::PANORAMIC_CAMERA_INDEX);
				UserInterface::phc.substituteButton(NonButtonMap::CAMERAVIEW, NonButtonMap::PANORAMICCAMERA, NonButtonMap::PANORAMICCAMERA, 0);
				UserInterface::phc.hideDropDownMenu(NonButtonMap::CAMERAVIEW, 0);
				UserInterface::phc.showButton(NonButtonMap::CAMERAVIEW, NonButtonMap::PANORAMICCAMERA);
			}



		}


		/*COTROL DROP DOWN MENU*/
		{
			if (UserInterface::cursorPointing("ENTER CONTROL MODE"))
			{
				UserInterface::phc.turnOffAllButtons();
				UserInterface::phc.showButton(ButtonMap::CONTROLMODEBUTTON, "CTRL + E to exit Control mode");
				setControls_controlMode();
			}

			if (UserInterface::cursorPointing(SWITCHAI))
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
			if (UserInterface::cursorPointing(SWITCHPHYSICS))
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
			if (UserInterface::cursorPointing(NonButtonMap::SELECTOBJECT))
				EditObjectModeButton::goToEditObject();


			if (UserInterface::cursorPointing(NonButtonMap::EDITCLUSTER))
				clusterNS::ClusterManager::printClusterList();
			if (UserInterface::cursorPointing(NonButtonMap::CREATECLUSTER))
			{
				EditObjectModeButton::createCluster(Application::window, 0, 1, 0);
			}


			if (UserInterface::cursorPointing(NonButtonMap::GROUND))
			{
				UserInterface::phc.showDropDownMenu(
					ButtonMap::EDITOBJECTMODEBUTTON, myobjectNS::Ground::getGroundList());
			}

			if (UserInterface::cursorPointing(NonButtonMap::ACTIVECHARACTER))
			{
				buttonCallback_activeCharacter();
			}

		}

		

		//EDIT GAME DROP DOWN MENU
		{
			if (UserInterface::cursorPointing(ButtonMap::CREATEBUTTON))
			{	
					/*if ( UserInterface::cursorPointing(ButtonMap::BACKBUTTON) || UserInterface::cursorPointing(NonButtonMap::NOBUTTON))
					{
						UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
						StartButton::mainMenu(Application::window, 0, 0, 0);
						return;
					}*/
					
					{
						UserInterface::printAssetObjectsList(ButtonMap::EDITGAMEMODEBUTTON);
						UserInterface::bfl.setMouseButtonCallback(StartButton::createObject);
					}	
				
			}

			if (UserInterface::cursorPointing(ButtonMap::DELETEBUTTON))
			{
				UserInterface::printExistingObjects(ButtonMap::EDITGAMEMODEBUTTON);
				UserInterface::bfl.setMouseButtonCallback(StartButton::deleteObject);
			}
		}




		//EDIT SOUND DROP DOWN MENU
		{
			if (UserInterface::cursorPointing("SWITCH ON/OFF"))
			{
				uiNS::EditSoundsButton::switchSoundsONOFF();

			}

		}


	}






	/*QUESTA FUNZIONE E' RESPONSABILE DELLA COMPARSA DEI MENU' A TENDINA.
	QUANDO IL CURSORE SI TROVA IN CORRISPONDENZA DI UN PULSANTE LA FUNZIONE "CLICKED" RITORNA 
	TRUE E LA FUNZIONE SHOWDROPDOWN MOSTRA I PULSANTI ELENCATI*/
	void StartButton::cursorPositionCallBack(GLFWwindow* w, double x, double y)
	{
		UserInterface::cursor_x = x;
		UserInterface::cursor_y = y;



		if (UserInterface::cursorPointing(NonButtonMap::NOBUTTON))
		{
			//resetCallbackFunc();
			return;
		}


		std::string buttonID{ UserInterface::cursorVStext() };
		ButtonInterface* b = UserInterface::getButtonFromList(buttonID);
		UserInterface::highlightButton(b);

		if (UserInterface::cursorPointing(NonButtonMap::FILE))
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

		if (UserInterface::cursorPointing(ButtonMap::CONTROLMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::CONTROLMODEBUTTON, 
				{ "ENTER CONTROL MODE", SWITCHPHYSICS,SWITCHAI });
		}


		if (UserInterface::cursorPointing(ButtonMap::EDITGAMEMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITGAMEMODEBUTTON,
				{ ButtonMap::CREATEBUTTON,ButtonMap::DELETEBUTTON });
		}

		if (UserInterface::cursorPointing(NonButtonMap::EDITSOUNDS))
		{
			UserInterface::phc.showDropDownMenu(NonButtonMap::EDITSOUNDS,{ "SWITCH ON/OFF"});
		}


		if (UserInterface::cursorPointing(ButtonMap::EDITOBJECTMODEBUTTON))
		{
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,
				{ NonButtonMap::SELECTOBJECT,
				NonButtonMap::CREATECLUSTER,
				NonButtonMap::SELECTCLUSTER,
				NonButtonMap::GROUND,
				NonButtonMap::ACTIVECHARACTER});

		}



		if (UserInterface::cursorPointing(UserInterface::phc.getPHbyID(NonButtonMap::CAMERAVIEW).getHeader()))
		{
			UserInterface::phc.showDropDownMenu(NonButtonMap::CAMERAVIEW,
				{ NonButtonMap::GROUNDCAMERA,NonButtonMap::FLYINGCAMERA,NonButtonMap::PANORAMICCAMERA });
		}

	}







}