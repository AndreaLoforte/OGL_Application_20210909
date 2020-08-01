#include<buttonEditObject.h>
#include<userInterface.h>
#include<applicationDerivedObject.h>
#include<applicationObjectManager.h>
#include<objectControlsInterface.h>
#include<inputs.h>
#include<app.h>
#include<AI.h>
#include<cluster.h>
#include<toStringLib.h>

using namespace myobjectNS;

namespace uiNS
{

	bool EditObjectModeButton::typePosition = false;
	bool EditObjectModeButton::typeRotation = false;



	void EditObjectModeButton::action()
	{
		UserInterface::deleteAllButtons();
		UserInterface::setFlags(false, false, false);
		
		UserInterface::showButton(NonButtonMap::SELECTOBJECT, NonButtonMap::SELECTOBJECT);
		UserInterface::showButton(NonButtonMap::SELECTCLUSTER, NonButtonMap::SELECTCLUSTER);
		UserInterface::showButton(NonButtonMap::CLUSTERLIST, NonButtonMap::CLUSTERLIST);
		UserInterface::showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);
		UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack);

	}


	void EditObjectModeButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{
		if (action == GLFW_RELEASE) return;
			/*3 case : 
			1) do not click anything
			2) do click a NonButton
			3) do click a Button*/
			std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };
			if (buttonID == NonButtonMap::NOBUTTON) return;
			if (buttonID == NonButtonMap::SELECTOBJECT)
			{
				UserInterface::clickButton(buttonID);
				UserInterface::bfl.setMouseButtonCallback(selectObject);
				UserInterface::printExistingObjects();
				
			}

			if (buttonID == NonButtonMap::CLUSTERLIST)
			{
				UserInterface::clickButton(buttonID);
				clusterNS::ClusterManager::printClusterList();
			}


			if (buttonID == NonButtonMap::SELECTCLUSTER)
			{
				
				UserInterface::clickButton(buttonID);
				UserInterface::deleteAllButtons();
				UserInterface::showButton(NonButtonMap::SELECTCLUSTER+"_", "SELECT CLUSTER ELEMENTS");
				UserInterface::printExistingObjects();
				UserInterface::showButton(NonButtonMap::EDITCLUSTER, NonButtonMap::EDITCLUSTER);
				UserInterface::bfl.setMouseButtonCallback(insertInCluster);
				return;
			}
			UserInterface::enableBack(buttonID);
			
	}



	void EditObjectModeButton::selectObject()
	{
		string buttonID{ UserInterface::cursorVStext() };


		//ButtonInterface* b = ButtonMap::getButtonByID({ buttonID });
		/*if it is not a button means that user chose an object*/

			/*check if the buttonID is an objectID we can set as editable object*/
		if (myobjectNS::ApplicationObjectManager::setEditableObject(buttonID))
		{
			UserInterface::deleteAllButtons();
			UserInterface::showButton(buttonID, "Editing Object " + buttonID, 0.5);
			UserInterface::showButton(NonButtonMap::ADJUSTSIZE, NonButtonMap::ADJUSTSIZE);
			UserInterface::showButton(NonButtonMap::ADJUSTCOLOR, NonButtonMap::ADJUSTCOLOR);
			UserInterface::showButton(NonButtonMap::OBJECTPOSITION, NonButtonMap::OBJECTPOSITION);
			UserInterface::showButton(NonButtonMap::OBJECTSWITCH, NonButtonMap::OBJECTSWITCH);
			UserInterface::enableBack(buttonID);
			UserInterface::bfl.setMouseButtonCallback(editObject);
			return;
		}

		UserInterface::enableBack(buttonID);

		
	}



	void EditObjectModeButton::editObject(GLFWwindow* w, int button, int action, int mods)
	{
		
		//UserInterface::deleteNonButtonsByBranch(NonButtonMap::OBJECTPOSITION);

		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };

		if (buttonID == NonButtonMap::ADJUSTSIZE)
		{
			UserInterface::clickButton(buttonID);
			UserInterface::bfl.setKeyCallback(key_callbackEditSize);
			return;
		}

		if (buttonID == NonButtonMap::ADJUSTCOLOR)
		{
			UserInterface::clickButton(buttonID);
			UserInterface::bfl.setKeyCallback(key_callbackEditColor);
			return;
		}

		if (buttonID == NonButtonMap::OBJECTSWITCH)
		{
			UserInterface::clickButton(buttonID);
			ObjectSwitch(myobjectNS::ApplicationObjectManager::getEditableCollector());
			return;
		}

	

		if (buttonID == NonButtonMap::OBJECTPOSITION)
		{
			UserInterface::clickButton(buttonID);
			UserInterface::bfl.setKeyCallback(key_callbackMove);
			UserInterface::bfl.setMouseButtonCallback(cursor_callbackMoveObject);
			return;
		}


		UserInterface::enableBack(buttonID);
			

	}




	
	


	void EditObjectModeButton::ObjectSwitch(collectorNS::ApplicationObjectCollector* obj)
	{
		
			if (obj->isOn)
			{
				obj->canSleep(true);
				UserInterface::showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "OBJECT OFF");


			}
			else
			{
				obj->canSleep(false);
				UserInterface::showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "OBJECT ON");
			}

	}








	void EditObjectModeButton::key_callbackEditColor(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
			return;
		}

		collectorNS::ApplicationObjectCollector* objcoll = myobjectNS::ApplicationObjectManager::getEditableCollector();

		UserInterface::showButton
		("EDITCOLOR",objcoll->collectorID + " color : " + tostringNS::vmathTostring::vec4Tostring(objcoll->getBody()->AOcolor));

		

		static vector<float> color;
		UserInterface::showButton
		("EDITCOLOR", "Enter the color components r,g,b,a in range [0,100]  : " + UserInterface::typer.NInsertion2(key, action, 4, color));

		if (UserInterface::typer.completed_total)
		{
			mymathlibNS::stdVectorProdFloat(color, 0.01);
			static_cast<myobjectNS::ApplicationObject*>(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeColor(color);

			UserInterface::showButton
			("EDITCOLOR",objcoll->collectorID + " color : " + tostringNS::vmathTostring::vec4Tostring(objcoll->getBody()->AOcolor));
		}

		
	}
	




}



