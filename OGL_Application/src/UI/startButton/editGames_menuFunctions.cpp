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

		if (!myobjectNS::ApplicationObjectManager::createNewObject(buttonID) || UserInterface::clicked(NonButtonMap::NOBUTTON))
			resetCallbackFunc();
	}

	void StartButton::deleteObject()
	{
		string buttonID{ UserInterface::cursorVStext() };

		if (!myobjectNS::ApplicationObjectManager::deleteObject(buttonID) || UserInterface::clicked(NonButtonMap::NOBUTTON))
			resetCallbackFunc();
		else
			UserInterface::printExistingObjects(ButtonMap::EDITGAMEMODEBUTTON);
	}


}