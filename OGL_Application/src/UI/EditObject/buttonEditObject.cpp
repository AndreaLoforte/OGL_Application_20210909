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
		UserInterface::bfl.setMouseButtonCallback(cursorButtonCallBack_clusters);

	}


	void EditObjectModeButton::goToEditObject()
	{
		UserInterface::printExistingObjects(ButtonMap::EDITOBJECTMODEBUTTON);
		UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, ButtonMap::BACKBUTTON);
		UserInterface::bfl.setMouseButtonCallback(EditObjectModeButton::selectObject);
		UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack_highlightOnly);
		//selectObject();
	}


	void EditObjectModeButton::cursorButtonCallBack_clusters(GLFWwindow* w, int button, int action, int mode)
	{
		UserInterface::setFlags(false, true, true);
		if (action == GLFW_RELEASE) return;
			/*3 case : 
			1) do not click anything
			2) do click a NonButton
			3) do click a Button*/
			std::string buttonID{ UserInterface::cursorVStext() };
			if (UserInterface::cursorPointing(NonButtonMap::SELECTOBJECT))
			{
				//UserInterface::clickButton(buttonID);
				UserInterface::bfl.setMouseButtonCallback(selectObject);
				
				
			}

			if (buttonID == NonButtonMap::CLUSTERLIST)
			{
				clusterNS::ClusterManager::printClusterList();
			}


			if (buttonID == NonButtonMap::SELECTCLUSTER)
			{				
				UserInterface::bfl.setMouseButtonCallback(insertInCluster);
				return;
			}
			
	}





	

	void EditObjectModeButton::editObjectMenu(GLFWwindow* w, double x, double y)
	{


		//UserInterface::cursor_x = x;
		//UserInterface::cursor_y = y;



		//std::string buttonID{ UserInterface::cursorVStext() };
		//if (buttonID == NonButtonMap::NOBUTTON)
		//{
		//	//UserInterface::phc.hideDropDownMenu();
		//	return;
		//}

		//ButtonInterface* b = UserInterface::getButtonFromList(buttonID);
		//UserInterface::highlightButton(b);




	}





	void EditObjectModeButton::selectObject(GLFWwindow* window, int button,int action,int mods)
	{

		if (action == GLFW_RELEASE) return;
		string buttonID{ UserInterface::cursorVStext() };
		/*if it is not a button means that user chose an object*/

			/*check if the buttonID is an objectID we can set as editable object*/
		

		if(UserInterface::cursorPointing(NonButtonMap::NOBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
			UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
			StartButton::mainMenu(Application::window, 0, 0, 0);
			StartButton::cursorButtonCallBack(Application::window, 0, 0, 0);
		}

		if (myobjectNS::ApplicationObjectManager::setEditableObject(buttonID))
		{
			UserInterface::bfl.setMouseButtonCallback(cursorButtonCallback_editObject);
			//cursorButtonCallback_editObject(Application::window, 0, 0, 0);
			UserInterface::phc.showDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,
				{ "Editing Object " + myobjectNS::ApplicationObjectManager::getEditableObjectName(),
				NonButtonMap::ADJUSTSIZE,NonButtonMap::ADJUSTCOLOR,
				NonButtonMap::OBJECTPOSITION,NonButtonMap::OBJECTSWITCH,
				ButtonMap::BACKBUTTON });

		}


		if (UserInterface::cursorPointing(ButtonMap::BACKBUTTON))
		{
			UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
			UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
			StartButton::mainMenu(Application::window, 0, 0, 0);
			StartButton::cursorButtonCallBack(Application::window, 0, 0, 0);
		}
	
		
	}


	



	void EditObjectModeButton::cursorButtonCallback_editObject(GLFWwindow* w, int button, int action, int mods)
	{
		UserInterface::phc.showDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,
			{ "Editing Object " + myobjectNS::ApplicationObjectManager::getEditableObjectName(),
			NonButtonMap::ADJUSTSIZE,NonButtonMap::ADJUSTCOLOR,
			NonButtonMap::OBJECTPOSITION,NonButtonMap::OBJECTSWITCH,
			ButtonMap::BACKBUTTON });
		
		if (action == GLFW_RELEASE) return;
		

		if (UserInterface::cursorPointing(NonButtonMap::ADJUSTSIZE))
		{
			UserInterface::phc.hideDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON, 5);
			UserInterface::bfl.setKeyCallback(key_callbackEditSize);
			key_callbackEditSize(Application::window,0,0,0,0);
			return;
		}

		if (UserInterface::cursorPointing(NonButtonMap::ADJUSTCOLOR))
		{
			UserInterface::phc.hideDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON,5);
			UserInterface::bfl.setKeyCallback(key_callbackEditColor);
			key_callbackEditColor(Application::window, 0, 0, 1, 0);
			return;
		}

		if (UserInterface::cursorPointing(NonButtonMap::OBJECTSWITCH))
		{
			UserInterface::phc.hideDropDownMenu(ButtonMap::EDITOBJECTMODEBUTTON, 5);
			ObjectSwitch(myobjectNS::ApplicationObjectManager::getEditableCollector());
			return;
		}

	

		if (UserInterface::cursorPointing(NonButtonMap::OBJECTPOSITION))
		{
			editPosition();
			
			return;
		}

		if (UserInterface::cursorPointing(ButtonMap::BACKBUTTON))
		{
			goToEditObject();
		}

		if (UserInterface::cursorPointing(NonButtonMap::QUITBUTTON))
			glfwSetWindowShouldClose(Application::window, GLFW_TRUE);


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



