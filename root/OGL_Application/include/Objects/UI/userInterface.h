#pragma once
#include<inputs.h>
#include<text.h>
#include<buttonfunctionlist.h>
/*user interface*/


namespace uiNS {

	class ButtonInterface;
	class StartButton;

	class UserInterface
	{
		
	public:
		UserInterface(InputsNS::Controls* c);
		static App* app;
		static unsigned frameID;
		static buttonFunctiosList bfl;
		static InputsNS::Controls* control;
		static textRendererNS::PrintHelper ph;
		static StartButton* start;
		static vector<ButtonInterface*> buttonFlow;
		static map<string,ButtonInterface> buttonsList;
		//static vector<ButtonInterface*> parentFlow;
		static double cursor_x, cursor_y;
		static bool paused;
		static bool physicsOn;
		static bool AIon;
		
		static InputsNS::Typer typer;
		void init();
		static void pause();
		static std::string cursorVStext(const double& x, const double& y);
		static std::string cursorVStext();
		static bool clicked(const string&);
		static void deleteButtonsByBranch(const string& branchID);
		static void deleteNonButtonsByBranch(const string& branchID);
		static void deleteAllButtons();
		static ButtonInterface* getParentButton();
		static ButtonInterface* getButtonFromList(const string& bid);
		static void update();

		static void highlightButton(ButtonInterface* BI);

		static void turnOffAllButtons();

		static void printExistingObjects();
		static void printAssetObjectsList();
		static void clickButton(const string&);
		static void showButton(const string& stringID, const string& stringValue, const float& scale = 0.3);
		static void setFlags(const bool& pause, const bool& aion, const bool& physicson);

		static void back();
		static void ShowBackButton();
		static bool enableBack(const string&);

	};

	
	

	

}