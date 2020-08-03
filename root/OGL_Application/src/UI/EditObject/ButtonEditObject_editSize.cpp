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
		vector<float> size;

		if (key == GLFW_KEY_ESCAPE)
		{
			//UserInterface::ph.eraseFromMap(uiNS::ButtonMap::EDITOBJECTMODEBUTTON);
		}

		if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==myobjectNS::classSphere)
		{
			
			uiNS::UserInterface::phc.showButton(
				uiNS::ButtonMap::EDITOBJECTMODEBUTTON,"SIZE", "Type the new radius : "+UserInterface::typer.NInsertion2(key, action,1, size));

			if(UserInterface::typer.completed_total)
				static_cast<myobjectNS::ObjectSphere*>
				(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeRadius(size[0]);
		}


		if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass == myobjectNS::classPlane)
		{
			UserInterface::phc.showButton(ButtonMap::EDITOBJECTMODEBUTTON, "SIZE", "enter X size, Y size : " + UserInterface::typer.NInsertion2(key, action, 2, size));

			if (UserInterface::typer.completed_total)
				static_cast<myobjectNS::ObjectPlane*>
				(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeDimensions(size[0], size[1]);

		}


		if (myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOobjectClass ==myobjectNS::classBox)
		{
			
			UserInterface::phc.showButton(
				uiNS::ButtonMap::EDITOBJECTMODEBUTTON, "SIZE","Type 3 dimensions : " + UserInterface::typer.NInsertion2(key, action, 3, size));

			if (UserInterface::typer.completed_total)		
				static_cast<myobjectNS::ObjectBox*>
					(myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody())->changeDimensions(size[0], size[1], size[2]);
			
		}
		

		



	}


}



