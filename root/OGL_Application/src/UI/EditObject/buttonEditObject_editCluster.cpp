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
			UserInterface::showButton(obj->collectorID, obj->collectorID + " was added to the cluster");
		}

		if (buttonID == NonButtonMap::EDITCLUSTER)
		{
			UserInterface::deleteAllButtons();
			UserInterface::showButton(NonButtonMap::CLUSTERCOLOR, NonButtonMap::CLUSTERCOLOR);
			UserInterface::showButton(NonButtonMap::CLUSTERPOSITION, NonButtonMap::CLUSTERPOSITION);
			UserInterface::showButton(NonButtonMap::CLUSTERSWITCH, NonButtonMap::CLUSTERSWITCH);
			UserInterface::showButton(NonButtonMap::SAVECLUSTER, NonButtonMap::SAVECLUSTER);

			UserInterface::enableBack(buttonID);

			UserInterface::bfl.setMouseButtonCallback(editCluster);

		}

		UserInterface::enableBack(buttonID);
		

	}



	void EditObjectModeButton::editCluster(GLFWwindow* w, int button, int action_, int mods)
	{

		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };

		if (buttonID == NonButtonMap::CLUSTERSWITCH)
		{
			UserInterface::clickButton(buttonID);
			UserInterface::bfl.setMouseButtonCallback(clusterSwitch);
			clusterSwitch();
			return;
		}

		if (buttonID == NonButtonMap::CLUSTERPOSITION)
		{
			UserInterface::clickButton(buttonID);
			UserInterface::bfl.setKeyCallback(key_callbackMoveCluster);
			key_callbackMoveCluster(w, 0, 0, 0, 0);
			return;
		}


		if (buttonID == NonButtonMap::CLUSTERCOLOR)
		{
			UserInterface::clickButton(buttonID);
			UserInterface::bfl.setKeyCallback(key_callbackClusterColor);
			key_callbackClusterColor(w, 0, 0, 0, 0);
			return;
		}



		if (buttonID == NonButtonMap::SAVECLUSTER)
		{
			UserInterface::clickButton(buttonID);
			std::string clusterName = "cluster_" + std::to_string(clusterNS::ClusterManager::clusterMap.size());
			clusterNS::ClusterManager::clusterMap.insert({clusterName, cluster });
			UserInterface::showButton(clusterName,"Cluster " + clusterName + " saved");
			return;
		}

		UserInterface::enableBack(buttonID);

	}



	void EditObjectModeButton::clusterSwitch()
	{

		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };


		UserInterface::showButton("SWITCH GROUP OFF", "SWITCH GROUP OFF");
		UserInterface::showButton("SWITCH GROUP ON", "SWITCH GROUP ON");
	
		if (buttonID == "SWITCH GROUP OFF")
		{
			for (int i = 0; i < cluster.group.size(); i++)
			{
				cluster.group[i]->canSleep(true);
				UserInterface::showButton(cluster.group[i]->collectorID, cluster.group[i]->collectorID + " turned off");
			}
		}

		if (buttonID == "SWITCH GROUP ON")
		{
			for (int i = 0; i < cluster.group.size(); i++)
			{
				cluster.group[i]->canSleep(false);
				UserInterface::showButton(cluster.group[i]->collectorID, cluster.group[i]->collectorID + " turned on");
			}
		}


		UserInterface::enableBack(buttonID);

	}





	void EditObjectModeButton::key_callbackClusterColor(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
			return;
		}


		static vector<float> color;

		UserInterface::showButton(
			uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
			"Enter the color components r,g,b,a in range [0,100]   "+ 
			UserInterface::typer.NInsertion2(key, action, 4, color));

		if(UserInterface::typer.completed_total)
		{
			mymathlibNS::stdVectorProdFloat(color, 0.01);
			for (int i = 0; i < cluster.group.size(); i++)
			{
				static_cast<myobjectNS::ApplicationObject*>(cluster.group[i]->getBody())->changeColor(color);
				UserInterface::showButton(cluster.group[i]->collectorID, "Changed color of " + cluster.group[i]->collectorID);
			}
		}
	}


	void EditObjectModeButton::key_callbackMoveCluster(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		UserInterface::showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Move the cluster using A,S,D,W,1,2 and diectional arrows");

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



