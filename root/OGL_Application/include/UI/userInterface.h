#pragma once
#include<inputs.h>
#include<PrintHelper.h>
#include<buttonfunctionLoader.h>
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
		/*bfl : button's function loader*/
		static buttonFunctiosList bfl;
		static InputsNS::Controls* control;
		/*phc : printHelper collector*/
		static printHelperNS::PrintHelperCollector phc;
		static StartButton* start;
		static vector<ButtonInterface*> buttonFlow;
		static double cursor_x, cursor_y;
		static bool paused;
		static bool physicsOn;
		static bool AIon;
		
		
		static InputsNS::Typer typer;
		void init();
		static void pause();
		//static std::string cursorVStext(const double& x, const double& y);
		static std::string cursorVStext();
		static bool clicked(const string&);
		static ButtonInterface* getParentButton();
		static ButtonInterface* getButtonFromList(const string& bid);
		static void update();
		
		static void highlightButton(ButtonInterface* BI);

		static void turnOffAllButtons();

		static void printExistingObjects(const string&);
		static void printAssetObjectsList(const string&);
		static void clickButton(const string&);
		static void setFlags(const bool& pause, const bool& aion, const bool& physicson);
		
		static void back();
		//static void ShowBackButton();
		static bool enableBack(const string&);

	};

	
	

	

}