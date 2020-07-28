#include<objectControlsInterface.h>
#include<applicationDerivedObject.h>
#include<applicationObjectManager.h>
#include<userInterface.h>
namespace objectControlsNS {

	using namespace textRendererNS;

	bool ObjectControlsI::mustPrint = true;
	textRendererNS::PrintHelper ObjectControlsI::ph{ "ObjectControlsInterface" };

	

	void ObjectControlsI::ObjectPhysicsSwitcher(myobjectNS::ApplicationObject* obj)
	{
	
		
	}


	void ObjectControlsI::ObjectSwitch(collectorNS::ApplicationObjectCollector* obj)
	{
		
		if (obj->isOn)
		{
			obj->canSleep(true);
			ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "OBJECT OFF");
			
		}
		else
		{
			obj->canSleep(false);
			ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "OBJECT ON");
		}
		

	}



	void ObjectControlsI::key_callbackEditSize(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		if (action == GLFW_RELEASE) return;
			if (key == GLFW_KEY_ESCAPE)
			{
				ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
				controls.setScrollCallback(window);
				controls.setAllCallbackFunction(window);
				mustPrint = true;
				return;
			}

			if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==
				myobjectNS::classSphere)
			{
				uiNS::UserInterface::ph.mapButtonOnBranch(
					uiNS::UserInterface::getParentButton()->getButtonID(),
					uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Type the new radius : ");

			
				float radius = controls.typing(key, action);
				if (radius <= 0) return;
				else
					static_cast<myobjectNS::ObjectSphere*>
					(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeRadius(radius);
			}



			if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==
				myobjectNS::classBox)
			{
				ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
					NEWLINE + NEWLINE + "Type 3 dimensions w,h, d : " + NEWLINE);


				static GLfloat x, y, z;
				static bool typefirst = true, typesecond = false, typethird = false;
				if (typefirst)
				{
					ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter first dimension");
					x = controls.typing(key, action);
					if (x <= 0) return;
					else
					{
						typefirst = false;
						typesecond = true;
					}

				}
				if (typesecond)
				{
					ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter second dimension");
					y = controls.typing(key, action);
					if (y <= 0) return;
					else
					{
						typesecond = false;
						typethird = true;
					}

				}
				if (typethird)
				{
					ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter third dimension");
					z = controls.typing(key, action);
					if (z <= 0) return;
					else
					{
						typefirst = true;
						typesecond = false;
						typethird = false;
					}
					static_cast<myobjectNS::ObjectBox*>
						(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeDimensions(x, y, z);
				}
			}



			if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==
				myobjectNS::classPlane)
			{
				ph.mapNewString(
					uiNS::ButtonMap::EDITOBJECTMODEBUTTON, NEWLINE + NEWLINE + "Type 2 dimensions w, h : " + NEWLINE);


				static float x, y;
				static bool typefirst = true, typesecond = false;
				if (typefirst)
				{
					ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter first dimension");
					x = controls.typing(key, action);
					if (x <= 0) return;
					else
					{
						typefirst = false;
						typesecond = true;
					}

				}
				if (typesecond)
				{
					ph.mapNewString(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter second dimension");
					y = controls.typing(key, action);
					if (y <= 0) return;
					else
					{
						typefirst = true;
						typesecond = false;
					}


				}


				static_cast<myobjectNS::ObjectPlane*>
					(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeDimensions(x, y);
			}

		
		

	}




	

	void ObjectControlsI::key_callbackEditColor(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		
		

		if (action != GLFW_RELEASE || mustPrint)
		{
			

			if (key == GLFW_KEY_ESCAPE)
			{
				controls.setScrollCallback(window);
				//myobjectNS::TextRenderer::clearEditMenuString();
				ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
				controls.setAllCallbackFunction(window);
				mustPrint = true;
				return;
			}

			if (mustPrint)
			{
				ph.mapNewString
				(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Scroll to set sizes");
				ph.mapNewString
				(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Enter the color components r,g,b,a in range [0,100]" + NEWLINE);
				mustPrint = false;
				return;
			}

			static vector<float> color;
			if (controls.NInsertion(key, action, 4, color))
			{
				mymathlibNS::stdVectorProdFloat(color, 0.01);
				static_cast<myobjectNS::ObjectSphere*>
					(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeColor(color);
			}
		}
	}

	void ObjectControlsI::setKeyCallbackEditColor(GLFWwindow * window)
	{
		auto L_key_callbackEditColor = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
		{
			//casto w a puntatore alla funzione key_callback di Controls
			static_cast<ObjectControlsI*>(glfwGetWindowUserPointer(w))->key_callbackEditColor(w, i1, i2, i3, i4);
		};
		glfwSetKeyCallback(window, L_key_callbackEditColor);
		static_cast<ObjectControlsI*>(glfwGetWindowUserPointer(window))->key_callbackEditColor(window, 0,0, 0, 0);
		return;
	}





		void ObjectControlsI::setKeyCallbackEditSize(GLFWwindow * window)
		{
			auto l_key_callbackeditsize = [](GLFWwindow* w, int key, int scancode, int action, int mods)
			{
				//casto w a puntatore alla funzione key_callback di controls
				static_cast<ObjectControlsI*>(glfwGetWindowUserPointer(w))->key_callbackEditSize(w, key, scancode, action, mods);
			};
			glfwSetKeyCallback(window, l_key_callbackeditsize);
			static_cast<ObjectControlsI*>(glfwGetWindowUserPointer(window))->key_callbackEditSize(window, 0, 0, 0, 0);
			return;
		}



		void ObjectControlsI::setScrollCallback(GLFWwindow * window)
		{

			auto L_scroll_callback = [](GLFWwindow* w, double xoffset, double yoffset)
			{
				static_cast<ObjectControlsI*>(glfwGetWindowUserPointer(w))->scroll_callback(w, xoffset, yoffset);
			};


			glfwSetScrollCallback(window, L_scroll_callback);
			static_cast<ObjectControlsI*>(glfwGetWindowUserPointer(window))->scroll_callback(window, 0.0, 0.0);
			return;

		}



	
		void ObjectControlsI::scroll_callback(GLFWwindow* w, double vscroll, double hscroll) 
		{

			static int mode = 0;

			if (mode == 0)
			{
				ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
				//myobjectNS::TextRenderer::clearEditMenuString();
				mustPrint = true;
				setKeyCallbackEditSize(w);
				mode = 1;
				return;
			}
			if (mode == 1)
			{
				ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
				//myobjectNS::TextRenderer::clearEditMenuString();
				setKeyCallbackEditColor(w);
				mustPrint = true;
				mode = 0;
				return;
			}
		}




		



}