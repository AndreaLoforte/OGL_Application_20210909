#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>
#include<buttonEditObject.h>
#include<userInterface.h>
namespace uiNS {



	void StartButton::createObject()
	{
		string buttonID{ UserInterface::cursorVStext() };

		if(UserInterface::cursorPointing(NonButtonMap::NOBUTTON))
		{
			resetCallbackFunc();
			return;
		}

		/*createNewObject ritorna true se riesce a creare l'oggetto altrimenti false*/
		if(!myobjectNS::ApplicationObjectManager::createNewObject(buttonID))
		{
			resetCallbackFunc();
			return;
		}
	}

	void StartButton::deleteObject()
	{
		string buttonID{ UserInterface::cursorVStext() };


		if (UserInterface::cursorPointing(NonButtonMap::NOBUTTON))
		{
			resetCallbackFunc();
			return;
		}
			

		if (myobjectNS::ApplicationObjectManager::deleteObject(buttonID))
			 UserInterface::printExistingObjects(ButtonMap::EDITGAMEMODEBUTTON);
		else
		{
			resetCallbackFunc();
			return;
		}
	}


}