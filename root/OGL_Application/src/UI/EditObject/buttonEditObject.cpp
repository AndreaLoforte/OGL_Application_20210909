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



	void EditObjectModeButton::action()
	{
		UserInterface::deleteAllButtons();
		UserInterface::setFlags(false, false, false);
		UserInterface::mapButtonOnParentBranch(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);
		UserInterface::mapButtonOnParentBranch(NonButtonMap::SELECTOBJECT, NonButtonMap::SELECTOBJECT);
		UserInterface::mapButtonOnParentBranch(NonButtonMap::SELECTCLUSTER, NonButtonMap::SELECTCLUSTER);

		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };
		if (buttonID == "CLICK_NO_BUTTON") return;
		if (buttonID == ButtonMap::BACKBUTTON)
		{
			//UserInterface::buttonFlow.back()->action();
			UserInterface::back();
			//UserInterface::start->action();
			return;
		}
		auto L_mouse_button_callbackEOM = [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE) return;
			static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->cursorButtonCallBack(w, button, action, mods);
		};
		glfwSetMouseButtonCallback(Application::window, L_mouse_button_callbackEOM);


	}


	void EditObjectModeButton::cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode)
	{
			/*3 case : 
			1) do not click anything
			2) do click a NonButton
			3) do click a Button*/
			std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };
			if (buttonID == "CLICK_NO_BUTTON") return;
			if (buttonID == NonButtonMap::SELECTOBJECT)
			{
				UserInterface::printExistingObjects();
			}
			if (buttonID == NonButtonMap::SELECTCLUSTER)
			{
				UserInterface::deleteAllButtons();
				UserInterface::mapButtonOnParentBranch(NonButtonMap::SELECTCLUSTER, "SELECT CLUSTER ELEMENTS");
				UserInterface::printExistingObjects();
				UserInterface::mapButtonOnParentBranch(NonButtonMap::EDITCLUSTER, NonButtonMap::EDITCLUSTER);
				auto L_mouse_button_callback = [](GLFWwindow* w, int button, int action, int mods)
				{
					if (action == GLFW_RELEASE) return;
					static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->insertInCluster(w, button, action, mods);
				};

				glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);
			}
			else
			{
				ButtonInterface *b = ButtonMap::getButtonByID({ buttonID });
				/*if it is not a button means that user chose an object*/
				if (!b)
				{
					/*check if the buttonID is an objectID we can set as editable object*/
					if (myobjectNS::ApplicationObjectManager::setEditableObject(buttonID))
					{
						UserInterface::deleteAllButtons();
						UserInterface::mapButtonOnParentBranch(buttonID, "Editing Object " + buttonID, 0.5);
						UserInterface::mapButtonOnParentBranch( NonButtonMap::ADJUSTSIZE, NonButtonMap::ADJUSTSIZE);
						UserInterface::mapButtonOnParentBranch( NonButtonMap::ADJUSTCOLOR, NonButtonMap::ADJUSTCOLOR);
						UserInterface::mapButtonOnParentBranch( NonButtonMap::OBJECTPOSITION, NonButtonMap::OBJECTPOSITION);
						UserInterface::mapButtonOnParentBranch( NonButtonMap::OBJECTSWITCH, NonButtonMap::OBJECTSWITCH);
						UserInterface::ShowBackButton();

					
						auto L_mouse_button_callback = [](GLFWwindow* w, int button, int action, int mods)
						{
							if (action == GLFW_RELEASE) return;
							static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->editObject(w, button, action, mods);	
						};

						glfwSetMouseButtonCallback(Application::window, L_mouse_button_callback);
						
					}					
					return;
				}
						
			}
		
			UserInterface::enableBack(buttonID);
	}


	void EditObjectModeButton::editObject(GLFWwindow* w, int button, int action, int mods)
	{
		
		std::string buttonID{ UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y) };

		if (buttonID == NonButtonMap::ADJUSTSIZE)
		{
			auto l_key_callbackeditsize = [](GLFWwindow* w, int key, int scancode, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				//casto w a puntatore alla funzione key_callback di controls
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->key_callbackEditSize(w, key, scancode, action, mods);
			};

			glfwSetKeyCallback(Application::window, l_key_callbackeditsize);
			/*static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(Application::window))->*/
				key_callbackEditSize(Application::window, 0, 0, 0, 0);
			return;

		}

		if (buttonID == NonButtonMap::ADJUSTCOLOR)
		{
			auto L_key_callbackEditColor = [](GLFWwindow* w, int key, int scancode, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				//casto w a puntatore alla funzione key_callback di Controls
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->key_callbackEditColor(w, key, scancode, action, mods);
			};
			glfwSetKeyCallback(Application::window, L_key_callbackEditColor);
			/*static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(Application::window))->*/
				key_callbackEditColor(Application::window, 0, 0, 0, 0);
			return;
		}

		if (buttonID == NonButtonMap::OBJECTSWITCH)
		{
			ObjectSwitch(myobjectNS::ApplicationObjectManager::getEditableCollector());
			return;
		}

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
			auto L_clusterPosition = [](GLFWwindow* w, int key,int scancode, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				//casto w a puntatore alla funzione key_callback di Controls
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->key_callbackMoveCluster(w,key,scancode,action,mods);// w, key, scancode, action, mods);
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

		if (buttonID == NonButtonMap::OBJECTPOSITION)
		{

			UserInterface::mapButtonOnParentBranch(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
				"Move the "+
				myobjectNS::ApplicationObjectManager::getEditableObjectName()+
				" object using A,S,D,W,1,2 and directional Arrows");

			auto L_key_callbackMoveObject = [](GLFWwindow* w, int key, int scancode, int action, int mods)
			{
				if (action == GLFW_RELEASE) return;
				//casto w a puntatore alla funzione key_callback di Controls
				static_cast<EditObjectModeButton*>(glfwGetWindowUserPointer(w))->key_callbackMove(w, key, scancode, action, mods);
			};
			glfwSetKeyCallback(Application::window, L_key_callbackMoveObject);
			return;
		}


		if (buttonID == ButtonMap::BACKBUTTON)
			UserInterface::back();
			

	}




	
	


	void EditObjectModeButton::ObjectSwitch(collectorNS::ApplicationObjectCollector* obj)
	{
		
			if (obj->isOn)
			{
				obj->canSleep(true);
				UserInterface::ph.mapButtonOnBranch(
					uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
					uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "OBJECT OFF");


			}
			else
			{
				obj->canSleep(false);
				UserInterface::ph.mapButtonOnBranch(
					uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
					uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "OBJECT ON");
			}

	}








	void EditObjectModeButton::key_callbackEditColor(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			//controls.setScrollCallback(window);
			//myobjectNS::TextRenderer::clearEditMenuString();
			UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
			//controls.setAllCallbackFunction(window);

			return;
		}

		collectorNS::ApplicationObjectCollector* objcoll = myobjectNS::ApplicationObjectManager::getEditableCollector();
		vmath::vec4 currentColor = objcoll->getBody()->AOcolor;

		/*UserInterface::mapButtonOnParentBranch
		(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,objcoll->collectorID+" color : "+mymathlibNS:);*/

		UserInterface::mapButtonOnParentBranch
		(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Enter the color components r,g,b,a in range [0,100]");

		static vector<float> color;

		if (UserInterface::control->NInsertion(key, action, 4, color))
		{
			mymathlibNS::stdVectorProdFloat(color, 0.01);
			static_cast<myobjectNS::ApplicationObject*>(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeColor(color);
		}
	}
	




}



