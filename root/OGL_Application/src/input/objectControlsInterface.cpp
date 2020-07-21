#include<objectControlsInterface.h>
#include<applicationObjectManager.h>
#include<applicationDerivedObject.h>


namespace objectControlsNS {

	using namespace textRendererNS;

	bool ObjectControlsI::mustPrint = true;
	textRendererNS::PrintHelper ObjectControlsI::ph{ "ObjectControlsInterface" };

	static const string EDITOBJECT;

	void ObjectControlsI::ObjectPhysicsSwitcher(myobjectNS::ApplicationObject* obj)
	{
	
		
	}


	void ObjectControlsI::ObjectSwitch(collectorNS::ApplicationObjectCollector* obj)
	{
		
		if (obj->isOn)
		{
			obj->canSleep(true);
			ph.mapNewString(EDITOBJECT, "OBJECT OFF");
			
		}
		else
		{
			obj->canSleep(false);
			ph.mapNewString(EDITOBJECT, "OBJECT ON");
		}
		

	}



	void ObjectControlsI::key_callbackEditSize(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		if (action != GLFW_RELEASE || mustPrint)
		{
			ph.mapNewString(EDITOBJECT,"Scroll to set Colors");

			if (key == GLFW_KEY_ESCAPE)
			{
				ph.eraseFromMap(EDITOBJECT);
				controls.setScrollCallback(window);
				controls.setAllCallbackFunction(window);
				mustPrint = true;
				return;
			}



			if (myobjectNS::ApplicationObjectManager::getEditableObject()->getBody()->AOobjectClass ==
				myobjectNS::classSphere)
			{
				ph.mapNewString(
					EDITOBJECT, "Type the new radius : ");

				float radius = controls.typing(key, action);
				if (radius <= 0) return;
				else
					static_cast<myobjectNS::ObjectSphere*>
					(myobjectNS::ApplicationObjectManager::getEditableObject()->getBody())->changeRadius(radius);
			}



			if (myobjectNS::ApplicationObjectManager::getEditableObject()->getBody()->AOobjectClass ==
				myobjectNS::classBox)
			{
				ph.mapNewString(EDITOBJECT,
					NEWLINE + NEWLINE + "Type 3 dimensions w,h, d : " + NEWLINE);


				static GLfloat x, y, z;
				static bool typefirst = true, typesecond = false, typethird = false;
				if (typefirst)
				{
					ph.mapNewString(EDITOBJECT, "enter first dimension");
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
					ph.mapNewString(EDITOBJECT, "enter second dimension");
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
					ph.mapNewString(EDITOBJECT, "enter third dimension");
					z = controls.typing(key, action);
					if (z <= 0) return;
					else
					{
						typefirst = true;
						typesecond = false;
						typethird = false;
					}
					static_cast<myobjectNS::ObjectBox*>
						(myobjectNS::ApplicationObjectManager::getEditableObject()->getBody())->changeDimensions(x, y, z);
				}
			}



			if (myobjectNS::ApplicationObjectManager::getEditableObject()->getBody()->AOobjectClass ==
				myobjectNS::classPlane)
			{
				ph.mapNewString(
					EDITOBJECT, NEWLINE + NEWLINE + "Type 2 dimensions w, h : " + NEWLINE);


				static float x, y;
				static bool typefirst = true, typesecond = false;
				if (typefirst)
				{
					ph.mapNewString(EDITOBJECT, "enter first dimension");
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
					ph.mapNewString(EDITOBJECT, "enter second dimension");
					y = controls.typing(key, action);
					if (y <= 0) return;
					else
					{
						typefirst = true;
						typesecond = false;
					}


				}


				static_cast<myobjectNS::ObjectPlane*>
					(myobjectNS::ApplicationObjectManager::getEditableObject()->getBody())->changeDimensions(x, y);
			}

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
				ph.eraseFromMap(EDITOBJECT);
				controls.setAllCallbackFunction(window);
				mustPrint = true;
				return;
			}

			if (mustPrint)
			{
				ph.mapNewString
				(EDITOBJECT, "Scroll to set sizes");
				ph.mapNewString
				(EDITOBJECT, "Enter the color components r,g,b,a in range [0,100]" + NEWLINE);
				mustPrint = false;
				return;
			}

			static vector<float> color;
			if (controls.NInsertion(key, action, 4, color))
			{
				mymathlibNS::stdVectorProdFloat(color, 0.01);
				static_cast<myobjectNS::ObjectSphere*>
					(myobjectNS::ApplicationObjectManager::getEditableObject()->getBody())->changeColor(color);
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
			auto l_key_callbackeditsize = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
			{
				//casto w a puntatore alla funzione key_callback di controls
				static_cast<ObjectControlsI*>(glfwGetWindowUserPointer(w))->key_callbackEditSize(w, i1, i2, i3, i4);
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
				ph.eraseFromMap(EDITOBJECT);
				//myobjectNS::TextRenderer::clearEditMenuString();
				mustPrint = true;
				setKeyCallbackEditSize(w);
				mode = 1;
				return;
			}
			if (mode == 1)
			{
				ph.eraseFromMap(EDITOBJECT);
				//myobjectNS::TextRenderer::clearEditMenuString();
				setKeyCallbackEditColor(w);
				mustPrint = true;
				mode = 0;
				return;
			}
		}




		



}