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

		UserInterface(InputsNS::Controls * c);
		void init();
		static std::string cursorVStext(const double& x, const double& y);
		/*void cursorButtonCallBack(GLFWwindow*, int, int, int);
		void cursorPositionCallBack(GLFWwindow*, double, double);*/
		static void deleteButtonsByBranch(const string& branchID);
		static void deleteAllButtons();
		static ButtonInterface* getParentButton();
		static void setButton(const string& buttonID);
		static void setButton(const string& branchID, const string& buttonID);
		static ButtonInterface* getButtonFromList(const string& bid)
		{
			for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
				if (ph.mapIDbutton_button.buttons[i].getButtonID() == bid)
					return &ph.mapIDbutton_button.buttons[i];
		}

		static void update()
		{
			for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
			{
				ph.mapIDbutton_button.buttons[i].update();
			}
		}

		static void highlightButton(ButtonInterface* BI)
		{
			for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
			{
				if (ph.mapIDbutton_button.buttons[i].isHighligted)
					ph.mapIDbutton_button.buttons[i].turnOff();
			}
			BI->Highligt();
		}

		static void turnOffAllButtons()
		{
			for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
			{
				if (ph.mapIDbutton_button.buttons[i].isHighligted)
					ph.mapIDbutton_button.buttons[i].turnOff();
			}
		}

		static void printExistingObjects();
		static void printAssetObjectsList();
		static void mapButtonOnParentBranch(const string&, const string&);
		

	};

	
	

	

}