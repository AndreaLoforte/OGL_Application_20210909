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





	void EditObjectModeButton::key_callbackEditSize(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
		}

		if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==
			myobjectNS::classSphere)
		{
			uiNS::UserInterface::mapButtonOnParentBranch(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Type the new radius : ");


			float radius = UserInterface::typer.typing(key, action);
			if (radius <= 0) return;
			else
				static_cast<myobjectNS::ObjectSphere*>
				(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeRadius(radius);
		}



		if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==
			myobjectNS::classBox)
		{
			UserInterface::mapButtonOnParentBranch(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "Type 3 dimensions : ");


			static GLfloat x, y, z;
			static bool typefirst = true, typesecond = false, typethird = false;
			if (typefirst)
			{
				UserInterface::mapButtonOnParentBranch(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter first dimension");
				x = UserInterface::typer.typing(key, action);
				if (x <= 0) return;
				else
				{
					typefirst = false;
					typesecond = true;
				}

			}
			if (typesecond)
			{
				UserInterface::mapButtonOnParentBranch(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter second dimension");
				y = UserInterface::typer.typing(key, action);
				if (y <= 0) return;
				else
				{
					typesecond = false;
					typethird = true;
				}

			}
			if (typethird)
			{
				UserInterface::mapButtonOnParentBranch(uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "enter third dimension");
				z = UserInterface::typer.typing(key, action);
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



		if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==	myobjectNS::classPlane)
		{
			UserInterface::showButton(ButtonMap::EDITOBJECTMODEBUTTON, "enter X size, Y size : " + UserInterface::typer.total_string);

				if(UserInterface::typer.NInsertion(key, action, 2, UserInterface::typer.vec))
					static_cast<myobjectNS::ObjectPlane*>
						(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->
					changeDimensions(UserInterface::typer.vec[0], UserInterface::typer.vec[1]);

			UserInterface::showButton(ButtonMap::EDITOBJECTMODEBUTTON, "enter X size, Y size : " + UserInterface::typer.total_string);
		}




	}


}



