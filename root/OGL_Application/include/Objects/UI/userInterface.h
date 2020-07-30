#pragma once
#include<inputs.h>
#include<text.h>

/*user interface*/


namespace uiNS {

	class ButtonInterface;
	class StartButton;

	class UserInterface
	{
		
	public:
		static InputsNS::Controls* control;
		static textRendererNS::PrintHelper ph;
		static StartButton* start;
		static vector<ButtonInterface*> buttonFlow;
		static double cursor_x, cursor_y;
		static bool paused;
		static bool physicsOn;
		static bool AIon;
		UserInterface(InputsNS::Controls * c);
		static InputsNS::Typer typer;
		void init();
		static void pause();
		static std::string cursorVStext(const double& x, const double& y);
		static void deleteButtonsByBranch(const string& branchID);
		static void deleteNonButtonsByBranch(const string& branchID);
		static void deleteAllButtons();
		static ButtonInterface* getParentButton();
		static void setButton(const string& buttonID);
		static void setButton(const string& branchID, const string& buttonID);
		static ButtonInterface* getButtonFromList(const string& bid);
		static void update();

		static void highlightButton(ButtonInterface* BI);

		static void turnOffAllButtons();

		static void printExistingObjects();
		static void printAssetObjectsList();
		static void mapButtonOnParentBranch(const string&, const string&, const float& = 0.3);
		static void setFlags(const bool& pause, const bool& aion, const bool& physicson);

		static void back();
		static void ShowBackButton();
		static void enableBack(const string&);

	};

	
	

	

}