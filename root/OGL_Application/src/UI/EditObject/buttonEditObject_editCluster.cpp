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



	void EditObjectModeButton::insertInCluster(GLFWwindow* w, int button, int action_, int mods)
	{
		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };

		/*tentatively looking for an object of ID buttonID*/
		collectorNS::ApplicationObjectCollector* obj = ApplicationObjectManager::getCollector(buttonID);

		/*check it pointer has a proper value*/
		if (obj)
		{
			cluster.group.push_back(obj);
			UserInterface::mapButtonOnParentBranch(obj->collectorID, obj->collectorID + " was added to the cluster");
		}

		if (buttonID == NonButtonMap::EDITCLUSTER)
		{
			UserInterface::deleteAllButtons();
			UserInterface::mapButtonOnParentBranch(NonButtonMap::CLUSTERCOLOR, NonButtonMap::CLUSTERCOLOR);
			UserInterface::mapButtonOnParentBranch(NonButtonMap::CLUSTERPOSITION, NonButtonMap::CLUSTERPOSITION);
			UserInterface::mapButtonOnParentBranch(NonButtonMap::CLUSTERSWITCH, NonButtonMap::CLUSTERSWITCH);
			UserInterface::mapButtonOnParentBranch(NonButtonMap::SAVECLUSTER, NonButtonMap::SAVECLUSTER);

			UserInterface::setButton(ButtonMap::BACKBUTTON);

			auto L_mouse_button_callback = [](GLFWwindow* w, int button, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->editCluster(w, button, action, mods);
			};

			glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);

		}


		

	}



	void EditObjectModeButton::editCluster(GLFWwindow* w, int button, int action_, int mods)
	{

		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };

		if (buttonID == NonButtonMap::CLUSTERSWITCH)
		{
			auto L_clusterSwitch = [](GLFWwindow* w, int button, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				//casto w a puntatore alla funzione key_callback di Controls
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->clusterSwitch();// w, key, scancode, action, mods);
			};
			glfwSetMouseButtonCallback(w, L_clusterSwitch);
			clusterSwitch();
			return;
		}

		if (buttonID == NonButtonMap::CLUSTERPOSITION)
		{
			auto L_clusterPosition = [](GLFWwindow* w, int key, int scancode, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				//casto w a puntatore alla funzione key_callback di Controls
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->key_callbackMoveCluster(w, key, scancode, action, mods);// w, key, scancode, action, mods);
			};
			glfwSetKeyCallback(w, L_clusterPosition);
			key_callbackMoveCluster(w, 0, 0, 0, 0);
			return;
		}


		if (buttonID == NonButtonMap::CLUSTERCOLOR)
		{
			auto L_clusterColor = [](GLFWwindow* w, int key, int scancode, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				//casto w a puntatore alla funzione key_callback di Controls
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->key_callbackClusterColor(w, key, scancode, action, mods);// w, key, scancode, action, mods);
			};
			glfwSetKeyCallback(w, L_clusterColor);
			key_callbackClusterColor(w, 0, 0, 0, 0);
			return;
		}



		if (buttonID == NonButtonMap::SAVECLUSTER)
		{
			std::string clusterName = "cluster_" + std::to_string(clusterNS::ClusterManager::clusterMap.size());
			clusterNS::ClusterManager::clusterMap.insert
			({clusterName, cluster });
			UserInterface::mapButtonOnParentBranch(clusterName,"Cluster " + clusterName + " saved");
			return;
		}

		UserInterface::enableBack(buttonID);

	}



	void EditObjectModeButton::clusterSwitch()
	{

		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };


		UserInterface::mapButtonOnParentBranch("SWITCH GROUP OFF", "SWITCH GROUP OFF");
		UserInterface::mapButtonOnParentBranch("SWITCH GROUP ON", "SWITCH GROUP ON");
		UserInterface::enableBack(buttonID);



		if (buttonID == "SWITCH GROUP OFF")
		{
			for (int i = 0; i < cluster.group.size(); i++)
			{
				cluster.group[i]->canSleep(true);
				UserInterface::mapButtonOnParentBranch(cluster.group[i]->collectorID, cluster.group[i]->collectorID + " turned off");
			}
		}

		if (buttonID == "SWITCH GROUP ON")
		{
			for (int i = 0; i < cluster.group.size(); i++)
			{
				cluster.group[i]->canSleep(false);
				UserInterface::mapButtonOnParentBranch(cluster.group[i]->collectorID, cluster.group[i]->collectorID + " turned on");
			}
		}
	}





	void EditObjectModeButton::key_callbackClusterColor(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			//controls.setScrollCallback(window);
			//myobjectNS::TextRenderer::clearEditMenuString();
			UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
			//controls.setAllCallbackFunction(window);

			return;
		}

		UserInterface::mapButtonOnParentBranch
		(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Enter the color components r,g,b,a in range [0,100]");

		static vector<float> color;

		if (UserInterface::typer.NInsertion(key, action, 4, color))
		{
			mymathlibNS::stdVectorProdFloat(color, 0.01);
			for (int i = 0; i < cluster.group.size(); i++)
			{
				static_cast<myobjectNS::ApplicationObject*>(cluster.group[i]->getBody())->changeColor(color);
				UserInterface::mapButtonOnParentBranch(cluster.group[i]->collectorID, "Changed color of " + cluster.group[i]->collectorID);
			}

			//static_cast<myobjectNS::ApplicationObject*>(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeColor(color);
		}
	}


	void EditObjectModeButton::key_callbackMoveCluster(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		UserInterface::mapButtonOnParentBranch("MOVECLUSTER", "Move the cluster using A,S,D,W,1,2 and diectional arrows");

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
				cluster.group[i]->AOtrX(-1);
			break;
		case GLFW_KEY_A:
			for (int i = 0; i < cluster.group.size(); i++)
				cluster.group[i]->AOtrX(1);
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



