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
		UserInterface::setFlags(false, false, false);
		
		/*UserInterface::showButton(NonButtonMap::SELECTOBJECT, NonButtonMap::SELECTOBJECT);
		UserInterface::showButton(NonButtonMap::SELECTCLUSTER, NonButtonMap::SELECTCLUSTER);
		UserInterface::showButton(NonButtonMap::CLUSTERLIST, NonButtonMap::CLUSTERLIST);
		UserInterface::showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);*/
		UserInterface::bfl.setMouseButtonCallback(ccursorButtonCallBack_clusters);

	}


	void EditObjectModeButton::ccursorButtonCallBack_clusters(GLFWwindow* w, int button, int action, int mode)
	{

		/*UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, NonButtonMap::SELECTOBJECT);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, NonButtonMap::SELECTCLUSTER);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, NonButtonMap::CLUSTERLIST);*/


		if (action == GLFW_RELEASE) return;
			/*3 case : 
			1) do not click anything
			2) do click a NonButton
			3) do click a Button*/
			std::string buttonID{ UserInterface::cursorVStext() };
			//if (buttonID == NonButtonMap::NOBUTTON) return;
			if (UserInterface::clicked(NonButtonMap::SELECTOBJECT))
			{
				//UserInterface::clickButton(buttonID);
				UserInterface::bfl.setMouseButtonCallback(selectObject);
				UserInterface::printExistingObjects(ButtonMap::EDITOBJECTMODEBUTTON);
				
			}

			if (buttonID == NonButtonMap::CLUSTERLIST)
			{
				UserInterface::clickButton(buttonID);
				clusterNS::ClusterManager::printClusterList();
			}


			if (buttonID == NonButtonMap::SELECTCLUSTER)
			{
				
				UserInterface::clickButton(buttonID);
				/*UserInterface::showButton(NonButtonMap::SELECTCLUSTER+"_", "SELECT CLUSTER ELEMENTS");
				UserInterface::printExistingObjects();
				UserInterface::showButton(NonButtonMap::EDITCLUSTER, NonButtonMap::EDITCLUSTER);*/
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
			UserInterface::phc.hideDropDownMenu();
			UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, buttonID, "Editing Object " + buttonID);
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,
				{ NonButtonMap::ADJUSTSIZE,NonButtonMap::ADJUSTCOLOR,NonButtonMap::OBJECTPOSITION,NonButtonMap::OBJECTSWITCH });

			UserInterface::bfl.setMouseButtonCallback(cursorButtonCallback_editObject);
			//editObject(Application::window, 0, 1, 0);
			
			return;
		}

		else
		{
			UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
			UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
			StartButton::cursorButtonCallBack(Application::window, 1, 1, 0);
		}

		
	}



	void EditObjectModeButton::cursorPositionCallBack(GLFWwindow* w, double x, double y)
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
	}


	void EditObjectModeButton::editObjectMenu(GLFWwindow* w, double x, double y)
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


	

	}





	void EditObjectModeButton::cursorButtonCallback_editObject(GLFWwindow* w, int button, int action, int mods)
	{
		
		//UserInterface::deleteNonButtonsByBranch(NonButtonMap::OBJECTPOSITION);

		//std::string buttonID{ UserInterface::cursorVStext() };

		if (UserInterface::clicked(NonButtonMap::ADJUSTSIZE))
		{
			UserInterface::phc.hideDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON, 5);
			UserInterface::bfl.setKeyCallback(key_callbackEditSize);
			return;
		}

		if (UserInterface::clicked(NonButtonMap::ADJUSTCOLOR))
		{
			UserInterface::phc.hideDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,5);
			UserInterface::bfl.setKeyCallback(key_callbackEditColor);
			key_callbackEditColor(Application::window, 0, 0, 1, 0);
			return;
		}

		if (UserInterface::clicked(NonButtonMap::OBJECTSWITCH))
		{
			UserInterface::phc.hideDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON, 5);
			ObjectSwitch(myobjectNS::ApplicationObjectManager::getEditableCollector());
			return;
		}

	

		if (UserInterface::clicked(NonButtonMap::OBJECTPOSITION))
		{
			UserInterface::phc.hideDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,5);
			UserInterface::bfl.setKeyCallback(key_callbackMove);
			//UserInterface::bfl.setMouseButtonCallback(cursor_callbackMoveObject);
			key_callbackMove(Application::window, 0, 0, 1, 0);
			return;
		}


		if (UserInterface::clicked(NonButtonMap::TYPEPOSITION))
		{
			typeRotation = false;
			typePosition = true;
			key_callbackMove(Application::window, 0, 0, 1, 0);
			return;
		}
		if (UserInterface::clicked(NonButtonMap::TYPEROTATION))
		{
			typePosition = false;
			typeRotation = true;
			key_callbackMove(Application::window, 0, 0, 1, 0);
			return;
		}

		if (UserInterface::clicked(NonButtonMap::NOBUTTON))
		{
			typePosition = false;
			typeRotation = false;
			key_callbackMove(Application::window, 0, 0, 1, 0);
			return;
		}


		//UserInterface::enableBack(buttonID);
			

	}



	
	
	const string STRINGEDITID = "EDITOBJECTID";


	void EditObjectModeButton::ObjectSwitch(collectorNS::ApplicationObjectCollector* obj)
	{

			if (obj->isOn)
			{
				obj->canSleep(true);
				UserInterface::phc.showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, STRINGEDITID,"OBJECT OFF");


			}
			else
			{
				obj->canSleep(false);
				UserInterface::phc.showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, STRINGEDITID,"OBJECT ON");
			}

	}



	




	void EditObjectModeButton::key_callbackEditColor(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			//UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
			return;
		}

		collectorNS::ApplicationObjectCollector* objcoll = myobjectNS::ApplicationObjectManager::getEditableCollector();

		/*UserInterface::showButton
		("EDITCOLOR",objcoll->collectorID + " color : " + tostringNS::vmathTostring::vec4Tostring(objcoll->getBody()->AOcolor));*/

		

		static vector<float> color;
		UserInterface::phc.showButton(
			ButtonMap::EDITOBJECTMODEBUTTON, STRINGEDITID,
			"Enter the color components r,g,b,a in range [0,100]  : " + UserInterface::typer.NInsertion2(key, action, 4, color));

		if (UserInterface::typer.completed_total)
		{
			mymathlibNS::stdVectorProdFloat(color, 0.01);
			static_cast<myobjectNS::ApplicationObject*>(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeColor(color);

			UserInterface::phc.showButton
			(ButtonMap::EDITOBJECTMODEBUTTON, STRINGEDITID,
				objcoll->collectorID + " color : " + tostringNS::vmathTostring::vec4Tostring(objcoll->getBody()->AOcolor));
		}

		
	}
	




}



