#include<buttonEditObject.h>
#include<userInterface.h>
#include<applicationDerivedObject.h>
#include<applicationObjectManager.h>
#include<objectControlsInterface.h>
#include<inputs.h>
#include<app.h>
#include<AI.h>
#include<cluster.h>

using namespace myobjectNS;

namespace uiNS
{
	clusterNS::Cluster EditObjectModeButton::cluster;



	void EditObjectModeButton::createCluster(GLFWwindow* w, int button, int action_, int mods)
	{
		cluster.group.clear();
		UserInterface::printExistingObjects(ButtonMap::EDITOBJECTMODEBUTTON);
		UserInterface::bfl.setMouseButtonCallback(EditObjectModeButton::insertInCluster);
		UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack_highlightOnly);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON,NonButtonMap::EDITCLUSTER);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::BACKBUTTON);
	}



	void EditObjectModeButton::insertInCluster(GLFWwindow* w, int button, int action_, int mods)
	{
		std::string buttonID{ UserInterface::cursorVStext() };

		/*tentatively looking for an object of ID buttonID*/
		collectorNS::ApplicationObjectCollector* obj = ApplicationObjectManager::getObjectByCollectorID(buttonID);

		if (obj)
		{
			cluster.group.push_back(obj);
			UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON,
				obj->collectorID, obj->collectorID + " was added to the cluster");
		}

		if (UserInterface::clicked(NonButtonMap::EDITCLUSTER))
			editClusterMenu(Application::window, 0, 1, 0);


		if (UserInterface::clicked(ButtonMap::BACKBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
			UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
			StartButton::mainMenu(Application::window, 0, 0, 0);
		}
		

	}

	void EditObjectModeButton::editClusterMenu(GLFWwindow* w, int button, int action_, int mods)
	{
		UserInterface::phc.showDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,
			{
				NonButtonMap::CLUSTERCOLOR,
				NonButtonMap::CLUSTERPOSITION,
				NonButtonMap::CLUSTERSWITCH,
				 NonButtonMap::SAVECLUSTER,
				 ButtonMap::BACKBUTTON
			});

		UserInterface::bfl.setMouseButtonCallback(mouseButtonCallback_editCluster);
		UserInterface::bfl.setKeyCallback(InputsNS::Controls::key_callbackControl);

	}




	void EditObjectModeButton::mouseButtonCallback_editCluster(GLFWwindow* w, int button, int action_, int mods)
	{

		if (UserInterface::clicked(NonButtonMap::CLUSTERSWITCH))
		{
			UserInterface::bfl.setMouseButtonCallback(clusterSwitch);
			clusterSwitch();
			return;
		}

		if (UserInterface::clicked(NonButtonMap::CLUSTERPOSITION))
		{
			UserInterface::bfl.setKeyCallback(key_callbackMoveCluster);
			UserInterface::bfl.setMouseButtonCallback(mouseButtonCallback_editClusterLVL2);
			key_callbackMoveCluster(w, 0, 0, 0, 0);
			return;
		}


		if (UserInterface::clicked(NonButtonMap::CLUSTERCOLOR))
		{
			UserInterface::bfl.setKeyCallback(key_callbackClusterColor);
			UserInterface::bfl.setMouseButtonCallback(mouseButtonCallback_editClusterLVL2);
			key_callbackClusterColor(w, 0, 0, 0, 0);
			return;
		}



		if (UserInterface::clicked(NonButtonMap::SAVECLUSTER))
		{
			std::string clusterName = "cluster_" + std::to_string(clusterNS::ClusterManager::clusterMap.size());
			clusterNS::ClusterManager::clusterMap.insert({clusterName, cluster });
			UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON,
				clusterName,"Cluster " + clusterName + " saved");
			return;
		}

		if (UserInterface::clicked(ButtonMap::BACKBUTTON))
			createCluster(Application::window, 0, 1, 0);
			
		if (UserInterface::clicked(NonButtonMap::QUITBUTTON))
			UserInterface::bfl.setMouseButtonCallback(QuitButton::showMenu);


	}

	void EditObjectModeButton::mouseButtonCallback_editClusterLVL2()
	{

		if (UserInterface::clicked(ButtonMap::BACKBUTTON))
			editClusterMenu(Application::window, 0, 1, 0);
			
		if (UserInterface::clicked(NonButtonMap::QUITBUTTON))
			UserInterface::bfl.setMouseButtonCallback(QuitButton::showMenu);

	}



	void EditObjectModeButton::clusterSwitch()
	{

		UserInterface::phc.showDropDownMenu(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
			{"SWITCH GROUP OFF" ,"SWITCH GROUP ON" ,ButtonMap::BACKBUTTON});
	
		if (UserInterface::clicked("SWITCH GROUP OFF"))
		{
			for (int i = 0; i < cluster.group.size(); i++)
			{
				cluster.group[i]->canSleep(true);
				UserInterface::phc.showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,cluster.group[i]->collectorID, cluster.group[i]->collectorID + " turned off");
			}
		}

		if (UserInterface::clicked("SWITCH GROUP ON"))
		{
			for (int i = 0; i < cluster.group.size(); i++)
			{
				cluster.group[i]->canSleep(false);
				UserInterface::phc.showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,cluster.group[i]->collectorID, cluster.group[i]->collectorID + " turned on");
			}
		}

		if(UserInterface::clicked(ButtonMap::BACKBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(mouseButtonCallback_editCluster);
			mouseButtonCallback_editCluster(Application::window, 0, 1, 0);
		}



	}





	void EditObjectModeButton::key_callbackClusterColor(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			//UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
			return;
		}


		static vector<float> color;

		UserInterface::phc.showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
			"EDITCLUSTERCOLOR",
			"Enter the color components r,g,b,a in range [0,100]   "+ 
			UserInterface::typer.NInsertion2(key, action, 4, color));

		if(UserInterface::typer.completed_total)
		{
			mymathlibNS::stdVectorProdFloat(color, 0.01);
			for (int i = 0; i < cluster.group.size(); i++)
			{
				static_cast<myobjectNS::ApplicationObject*>(cluster.group[i]->getBody())->changeColor(color);
				//UserInterface::showButton(cluster.group[i]->collectorID, "Changed color of " + cluster.group[i]->collectorID);
			}
		}
	}


	void EditObjectModeButton::key_callbackMoveCluster(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON,
			"MOVECLUSTER", "Move the cluster using A,S,D,W,1,2 and diectional arrows");

		if (action == GLFW_RELEASE) return;
		if (mods == GLFW_MOD_CONTROL)
		{

			if (key == GLFW_KEY_LEFT)
			{
				for (int i = 0; i < cluster.group.size(); i++)
					cluster.group[i]->AOrotZ(-1);


				return;
			}
			if (key == GLFW_KEY_RIGHT)
			{
				for (int i = 0; i < cluster.group.size(); i++)
					cluster.group[i]->AOrotZ(1);

				return;
			}

		}

		switch (key) {
		case GLFW_KEY_I:
			textRendererNS::TextRenderer::printEditableObjectInfos();
			break;
		case GLFW_KEY_C:
			fpcameraNS::CameraManager::switchCamera();
			break;
		case GLFW_KEY_W:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOtrZ(-1);
			break;
		case GLFW_KEY_S:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOtrZ(1);
			break;
		case GLFW_KEY_D:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOtrX(1);
			break;
		case GLFW_KEY_A:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOtrX(-1);
			break;
		case GLFW_KEY_1:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOtrY(-1);
			break;
		case GLFW_KEY_2:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOtrY(1);
			break;

		case GLFW_KEY_UP:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOrotX(1);
			break;
		case GLFW_KEY_DOWN:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOrotX(-1);
			break;
		case GLFW_KEY_RIGHT:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOrotY(-1);
			break;
		case GLFW_KEY_LEFT:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOrotY(1);
			break;
		case GLFW_KEY_R:
			fpcameraNS::CameraManager::resetAll();
			UserInterface::control->app_pt->resetAll();
			break;

		}
	}







}



