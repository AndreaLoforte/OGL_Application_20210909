#include<buttonMap.h>
#include<userInterface.h>
#include<buttons.h>
#include<buttonEditObject.h>
namespace uiNS {
	const string NonButtonMap::NOBUTTON = "NO BUTTON";
	const string NonButtonMap::NEXTOBJECT = "NEXT OBJECT";
	const string NonButtonMap::PREVOBJECT = "PREVIOUS OBJECT";
	const string NonButtonMap::SELECTOBJECT = "SELECT OBJECT";
	const string NonButtonMap::SELECTCLUSTER = "CREATE CLUSTER";
	const string NonButtonMap::EDITCLUSTER = "EDIT CLUSTER";
	const string NonButtonMap::CLUSTERLIST = "SHOW CLUSTERS";
	const string NonButtonMap::ADJUSTSIZE = "CHANGE SIZE";
	const string NonButtonMap::ADJUSTCOLOR = "CHANGE COLOR";
	const string NonButtonMap::OBJECTPOSITION = "CHANGE POSITION";
	const string NonButtonMap::OBJECTSWITCH = "TURN ON/OFF";
	const string NonButtonMap::CLUSTERSWITCH = "TURN CLUSTER ON/OFF";
	const string NonButtonMap::SAVECLUSTER = "SAVE CLUSTER";
	const string NonButtonMap::CLUSTERPOSITION = "CLUSTER POSITION";
	const string NonButtonMap::CLUSTERCOLOR = "CLUSTER COLOR";
	const string NonButtonMap::TYPEPOSITION = "TYPE POSITION";
	const string NonButtonMap::TYPEROTATION = "TYPE ORIENTATION";
	const string NonButtonMap::CHANGEPROJECT = "CHANGE PROJECT";
	const string NonButtonMap::PROGRAMINFOS = "PROGRAM INFOS";
	const string NonButtonMap::FILE = "FILE";
	const string NonButtonMap::LOADPROJECT = "LOAD PROJECT";
	const string NonButtonMap::NEWPROJECT = "NEWPROJECT";

	const string ButtonMap::CREATEBUTTON = "CREATE";
	const string ButtonMap::DELETEBUTTON = "DELETE";
	const string ButtonMap::ESCAPEBUTTON = "QUIT";
	const string ButtonMap::BACKBUTTON = "<<";
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
		buttonMap.emplace(STARTINGBUTTON, new StartButton());
		buttonMap.emplace(EDITGAMEMODEBUTTON, new EditGameButton());
		buttonMap.emplace(CREATEBUTTON, new CreateObjectButton());
		buttonMap.emplace(DELETEBUTTON, new DeleteObjectButton());
		buttonMap.emplace(BACKBUTTON, new BackButton());
		buttonMap.emplace(CONTROLMODEBUTTON, new ControlModeButton());
		buttonMap.emplace(SAVEBUTTON, new SaveButton());
		buttonMap.emplace(ESCAPEBUTTON, new QuitButton());
		buttonMap.emplace(EDITOBJECTMODEBUTTON, new EditObjectModeButton());
	}


	

	/*this method returns a button pointer if a button is pressed, otherwise 
	returns null*/
	uiNS::ButtonInterface* ButtonMap::getButtonByID(string bID)
	{
		using namespace textRendererNS;
		std::map<std::string, uiNS::ButtonInterface*>::iterator it = buttonMap.find(bID);
		
		if (it == buttonMap.end())
			return NULL;
	
		return it->second;
		
	}

}