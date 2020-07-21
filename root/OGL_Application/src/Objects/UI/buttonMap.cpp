#include<buttonMap.h>
#include<userInterface.h>
#include<buttons.h>
namespace uiNS {

	const string NonButtonMap::NEXTOBJECT = "NEXT OBJECT";
	const string NonButtonMap::PREVOBJECT = "PREVIOUS OBJECT";
	const string NonButtonMap::SELECTOBJECT = "SELECT OBJECT";
	const string NonButtonMap::ADJUSTSIZE = "ADJUST SIZE";
	const string NonButtonMap::ADJUSTCOLOR = "ADJUST COLOR";
	const string NonButtonMap::OBJECTSWITCH = "TURN ON/OFF";

	const string ButtonMap::CREATEBUTTON = "CREATE";
	const string ButtonMap::DELETEBUTTON = "DELETE";
	const string ButtonMap::ESCAPEBUTTON = "QUIT";
	const string ButtonMap::BACKBUTTON = "BACK";
	const string ButtonMap::CONTROLMODEBUTTON = "CONTROLMODE";
	const string ButtonMap::EDITOBJECTMODEBUTTON = "EDITOBJECTMODE";
	const string ButtonMap::EDITGAMEMODEBUTTON = "EDITGAME";
	const string ButtonMap::STARTINGBUTTON = "START";
	const string ButtonMap::SAVEBUTTON = "SAVE";
	const string ButtonMap::QUITANDSAVE = "QUIT_AND_SAVE";
	const string ButtonMap::QUITNOSAVE = "QUIT_NO_SAVE";



	std::map<std::string, uiNS::ButtonInterface*> ButtonMap::buttonMap;
	

	ButtonMap::ButtonMap()
	{
		buttonMap.emplace(EDITGAMEMODEBUTTON, new EditGameButton());
		buttonMap.emplace(CREATEBUTTON, new CreateObjectButton());
		buttonMap.emplace(DELETEBUTTON, new DeleteObjectButton());
		buttonMap.emplace(BACKBUTTON, new BackButton());
		buttonMap.emplace(CONTROLMODEBUTTON, new ControlModeButton());
		buttonMap.emplace(SAVEBUTTON, new SaveButton());
		buttonMap.emplace(ESCAPEBUTTON, new QuitButton());
		buttonMap.emplace(QUITANDSAVE, new QuitAndSaveButton());
		buttonMap.emplace(QUITNOSAVE, new QuitNoSaveButton());
		buttonMap.emplace(EDITOBJECTMODEBUTTON, new EditObjectModeButton());
	}


	

	/*this method returns a button pointer if a button is pressed, otherwise 
	returns null*/
	uiNS::ButtonInterface* ButtonMap::getButtonByID(const string& bID)
	{
		using namespace textRendererNS;
		std::map<std::string, uiNS::ButtonInterface*>::iterator it = buttonMap.find(bID);
		
		if (it == buttonMap.end())
		{
		/*	UserInterface::ph.mapButtonOnBranch
			(UserInterface::getParentButton()->getButtonID(),
				"GETBUTTONBYID",
				"ButtonID not Found in Map");*/
			
			return NULL;
		}
	
		return it->second;
		
	}

}