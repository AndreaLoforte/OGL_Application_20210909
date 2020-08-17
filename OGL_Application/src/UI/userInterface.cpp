#include<userInterface.h>
#include<inputs.h>
#include<app.h>
#include<applicationObjectManager.h>
#include<buttonsList.h>
#include<buttonMap.h>
using namespace InputsNS;

namespace uiNS {

	double UserInterface::cursor_x, UserInterface::cursor_y;
	vector<ButtonInterface*> UserInterface::buttonFlow;
	StartButton* UserInterface::start;
	bool UserInterface::UIon{ true };
	bool UserInterface::physicsOn{ true };
	bool UserInterface::AIon{ true };
	printHelperNS::PrintHelperCollector UserInterface::phc;
	InputsNS::Controls* UserInterface::control;
	InputsNS::Typer UserInterface::typer;
	buttonFunctiosLoader UserInterface::bfl;
	unsigned UserInterface::frameID = 0;
	App* UserInterface::app;		
	




	UserInterface::UserInterface(InputsNS::Controls* c)
	{
		control = c;
		control->setUserInterface(this);
		using namespace textRendererNS;

		printHelperNS::PrintHelper ph1{ "uiInterface",NonButtonMap::FILE ,-0.9f,0.95f };
		printHelperNS::PrintHelper ph2{ "uiInterface",ButtonMap::EDITGAMEMODEBUTTON,-0.7f,0.95f };
		printHelperNS::PrintHelper ph3{ "uiInterface",ButtonMap::EDITOBJECTMODEBUTTON,-0.4f,0.95f };
		printHelperNS::PrintHelper ph4{ "uiInterface",NonButtonMap::EDITSOUNDS , 0.f,0.95f };
		printHelperNS::PrintHelper ph5{ "uiInterface",ButtonMap::CONTROLMODEBUTTON, 0.3f,0.95f };
		printHelperNS::PrintHelper ph6{ "uiInterface",NonButtonMap::CAMERAVIEW , 0.6f,0.95f };
		printHelperNS::PrintHelper ph7{ "uiInterface",NonButtonMap::QUITBUTTON , 0.95f,0.95f };


		phc.printHmap.emplace(NonButtonMap::FILE, ph1);
		phc.printHmap.emplace(ButtonMap::EDITGAMEMODEBUTTON, ph2);
		phc.printHmap.emplace(ButtonMap::EDITOBJECTMODEBUTTON, ph3);
		phc.printHmap.emplace(NonButtonMap::EDITSOUNDS, ph4);
		phc.printHmap.emplace(ButtonMap::CONTROLMODEBUTTON, ph5);
		phc.printHmap.emplace(NonButtonMap::CAMERAVIEW, ph6);
		phc.printHmap.emplace(NonButtonMap::QUITBUTTON, ph7);
		


		phc.updateRenderer();
		
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(NonButtonMap::FILE));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(ButtonMap::EDITGAMEMODEBUTTON));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(ButtonMap::EDITOBJECTMODEBUTTON));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(NonButtonMap::EDITSOUNDS));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(ButtonMap::CONTROLMODEBUTTON));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(NonButtonMap::CAMERAVIEW));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(NonButtonMap::QUITBUTTON));


		start = new StartButton();
		buttonFlow.push_back(start);
		ButtonMap();
	}

	void UserInterface::init()
	{
		//UserInterface::paused = false;
		//UserInterface::setFlags(false, false, false);
		start->mainMenu(Application::window, 0, 1, 0);
		start->setControls();

	}




	void UserInterface::setFlags(const bool& uion, const bool& aion, const bool& physicson)
	{
		UIon = pause;
		AIon = aion;
		physicsOn = physicson;
	}

	void UserInterface::turnOffAllButtons()
	{
		for (int j = 0; j < phc.size(); j++)
		{
			for (int i = 0; i < phc[j].mapIDbutton_button.buttons.size(); i++)
			{
				if (phc[j].mapIDbutton_button.buttons[i].isHighligted)
					phc[j].mapIDbutton_button.buttons[i].turnOff();
			}
		}
	}

	void UserInterface::highlightButton(ButtonInterface* BI)
	{
		if (BI == NULL) return;
		for (int j = 0; j < phc.size(); j++)
		{
			for (int i = 0; i < phc[j].mapIDbutton_button.buttons.size(); i++)
			{
				if (phc[j].mapIDbutton_button.buttons[i].isHighligted)
					phc[j].mapIDbutton_button.buttons[i].turnOff();
			}
			
		}
		
			BI->Highligt();
	}

	ButtonInterface* UserInterface::getButtonFromList(const string& bid)
	{
		for (int j = 0; j < phc.size(); j++)
		{
			for (int i = 0; i < phc[j].mapIDbutton_button.buttons.size(); i++)
				if (phc[j].mapIDbutton_button.buttons[i].getButtonID() == bid)
					return &phc[j].mapIDbutton_button.buttons[i];
		}
		return NULL;
	}



	void UserInterface::update()
	{
		/*avoid overflow*/
		if (frameID > 10000000)
			frameID = 0;
		frameID++;
	}

	



	void UserInterface::printAssetObjectsList(const string& phID)
	{
	
		for (int j = 0; j < phc.size(); j++)
			UserInterface::phc[j].resetPosition();

		std::map<std::string, int>* assetIndex = AssetNS::Assets::getAssetIndex();
		std::map<std::string, int>::iterator it = assetIndex->begin();


		for (it; it != assetIndex->end(); it++)
			UserInterface::phc.showButton(phID,it->first,it->first);


	}


	void UserInterface::printExistingObjects(const string& phID)
	{
		static vector<string> vec;

		vec.clear();

		size_t size = myobjectNS::ApplicationObjectManager::ApplicationCollectorList.size();
		if (size == 0)
		{
			UserInterface::phc.showButton(phID, "This project has no objects yet");
			return;
		}
			
		
		
		for (int i = 0; i < size; i++)
		{
			vec.push_back(myobjectNS::ApplicationObjectManager::
				ApplicationCollectorList[i]->getCollectorID());
		}
		UserInterface::phc.showDropDownMenu(phID, vec);

	}
	 


	void UserInterface::pause()
	{

		if (UIon)
		{
			UIon = false;
			//UserInterface::ph.eraseFromMap("PAUSED");

		}
		else
		{
			//UserInterface::showButton("PAUSED", "PAUSE");
			UIon = true;
		}

	}




	ButtonInterface* UserInterface::getParentButton()
	{
		if (buttonFlow.size() >= 2)
			return buttonFlow.at(buttonFlow.size() - 2);
		else
			return buttonFlow.at(0);
	}

	


	


	std::string UserInterface::cursorVStext()
	{
		using namespace textRendererNS;

		/*x,y go from 0 to window_width, window_height.*/
		float transformed_x = (UserInterface::cursor_x - Application::window_width / 2) / Application::window_width * 2;
		float transformed_y = -(UserInterface::cursor_y - Application::window_height / 2) / Application::window_height * 2;

		for (int j = 0; j < phc.size(); j++)
		{
			for (int i = 0; i < phc[j].mapIDbutton_button.buttons.size(); i++)
				if (transformed_x < phc[j].mapIDbutton_button.buttons[i].button.x_min ||
					transformed_x > phc[j].mapIDbutton_button.buttons[i].button.x_max ||
					transformed_y < phc[j].mapIDbutton_button.buttons[i].button.y_min_frame ||
					transformed_y > phc[j].mapIDbutton_button.buttons[i].button.y_max_frame)
					/*do nothing*/;
				else
					return phc[j].mapIDbutton_button.buttons[i].button.buttonID;
		}

		return NonButtonMap::NOBUTTON;
	}


	/*function that checks if the buttonID passed has been pressed*/
	bool UserInterface::clicked(const string& bID)
	{
		static string buttonID = NonButtonMap::NOBUTTON;
		static unsigned functionCallID = 0;
		if (functionCallID != frameID)
		{
			functionCallID = frameID;

			/*x,y go from 0 to window_width, window_height.*/
			float transformed_x = (UserInterface::cursor_x - Application::window_width / 2) / Application::window_width * 2;
			float transformed_y = -(UserInterface::cursor_y - Application::window_height / 2) / Application::window_height * 2;

			for (int j = 0; j < phc.size(); j++)
			{
				for (int i = 0; i < phc[j].mapIDbutton_button.buttons.size(); i++)
					if (transformed_x < phc[j].mapIDbutton_button.buttons[i].button.x_min ||
						transformed_x > phc[j].mapIDbutton_button.buttons[i].button.x_max ||
						transformed_y < phc[j].mapIDbutton_button.buttons[i].button.y_min_frame ||
						transformed_y > phc[j].mapIDbutton_button.buttons[i].button.y_max_frame)
						/*if cursor is not upon this button do nothing*/;
					else
					{
						buttonID = phc[j].mapIDbutton_button.buttons[i].button.buttonID;
						phc.click(phc.getPHID(j), buttonID);
						return bID == buttonID;
					}

			}
			/*if cursor is outside every button frame assign NOBUTTON*/
			buttonID = NonButtonMap::NOBUTTON;
			//phc.click(buttonID, buttonID);
			return bID == buttonID;

		}
		else
			return bID == buttonID;


	}






	
}