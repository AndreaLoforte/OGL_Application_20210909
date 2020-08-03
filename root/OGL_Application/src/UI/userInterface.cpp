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
	bool UserInterface::paused{ true };
	bool UserInterface::physicsOn{ true };
	bool UserInterface::AIon{ true };
	printHelperNS::PrintHelperCollector UserInterface::phc;
	InputsNS::Controls* UserInterface::control;
	InputsNS::Typer UserInterface::typer;
	buttonFunctiosList UserInterface::bfl;
	unsigned UserInterface::frameID = 0;
	App* UserInterface::app;
	




	UserInterface::UserInterface(InputsNS::Controls* c)
	{
		control = c;
		control->setUserInterface(this);
		using namespace textRendererNS;

		printHelperNS::PrintHelper ph1{ "uiInterface",-0.9f,0.9f };
		printHelperNS::PrintHelper ph2{ "uiInterface",-0.7f,0.9f };
		printHelperNS::PrintHelper ph3{ "uiInterface",-0.4f,0.9f };
		printHelperNS::PrintHelper ph4{ "uiInterface",-0.1f,0.9f };


		phc.printHmap.emplace(NonButtonMap::FILE, ph1);
		phc.printHmap.emplace(ButtonMap::EDITGAMEMODEBUTTON, ph2);
		phc.printHmap.emplace(ButtonMap::EDITOBJECTMODEBUTTON, ph3);
		phc.printHmap.emplace(ButtonMap::CONTROLMODEBUTTON, ph4);
		phc.updateRenderer();
		
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(NonButtonMap::FILE));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(ButtonMap::EDITGAMEMODEBUTTON));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(ButtonMap::EDITOBJECTMODEBUTTON));
		textRendererNS::TextRenderer::printList.push_back(&UserInterface::phc.getPHbyID(ButtonMap::CONTROLMODEBUTTON));
		/*textRendererNS::TextRenderer::printList.push_back(&ph4);
		textRendererNS::TextRenderer::printList.push_back(&ph5);*/
		start = new StartButton();
		buttonFlow.push_back(start);
		ButtonMap();
	}

	void UserInterface::init()
	{

		/*glfwSetInputMode(Application::window, GLFW_STICKY_KEYS, 1);
		glfwSetWindowUserPointer(Application::window, this);*/

		UserInterface::paused = true;
		//UserInterface::deleteAllButtons();

		UserInterface::bfl.setMouseButtonCallback(StartButton::cursorButtonCallBack);
		
		UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
		StartButton::cursorButtonCallBack(Application::window, 0, 1, 0);


	}




	void UserInterface::back()
	{
		/*deleteAllButtons();*/
		vector<ButtonInterface*>::iterator it;
		size_t size = buttonFlow.size();

		
		int h = 1;
		ButtonInterface* b;
		do
		{
			it = buttonFlow.begin();
			for (int i = 0; i < size - h; i++)
				it++;
			/*never delete the first button (start button)*/
			if (it == buttonFlow.begin())
			{
				UserInterface::start->nogoback = true;
				UserInterface::start->menu();
				return;
			}
				buttonFlow.erase(it);
			b = ButtonMap::getButtonByID(buttonFlow.back()->getButtonID());
			if(b)
				b->action();
		} while (h++ < size && !b);

	}
	
	//void UserInterface::ShowBackButton()
	//{
	//	//UserInterface::showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);

	//}


	bool UserInterface::enableBack(const string& buttonID)
	{
		/*UserInterface::ShowBackButton();
		if (buttonID == ButtonMap::BACKBUTTON)
		{
			UserInterface::back();
			return true;
		}*/
		return false;
			
	}
	


	void UserInterface::setFlags(const bool& pause, const bool& aion, const bool& physicson)
	{
		paused = pause;
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
		for (int j = 0; j < phc.size(); j++)
		{
			for (int i = 0; i < phc[j].mapIDbutton_button.buttons.size(); i++)
			{
				if (phc[j].mapIDbutton_button.buttons[i].isHighligted)
					phc[j].mapIDbutton_button.buttons[i].turnOff();
			}
			BI->Highligt();
		}
	}

	ButtonInterface* UserInterface::getButtonFromList(const string& bid)
	{
		for (int j = 0; j < phc.size(); j++)
		{
			for (int i = 0; i < phc[j].mapIDbutton_button.buttons.size(); i++)
				if (phc[j].mapIDbutton_button.buttons[i].getButtonID() == bid)
					return &phc[j].mapIDbutton_button.buttons[i];
		}
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
		size_t size = myobjectNS::ApplicationObjectManager::ApplicationCollectorList.size();
		if (size == 0)
			UserInterface::phc.showButton(phID, "No object to Edit");
		
		static vector<string> vec;
		for (int i = 0; i < size; i++)
		{
			vec.push_back(myobjectNS::ApplicationObjectManager::
				ApplicationCollectorList[i]->getCollectorID());
		}
		UserInterface::phc.showDropDownMenu(phID, vec);

	}


	void UserInterface::clickButton(const string& stringID)
	{
		/*ButtonInterface* newB = new ButtonInterface(*UserInterface::getButtonFromList(stringID));
		buttonFlow.push_back(newB);*/

	}

	 


	void UserInterface::pause()
	{

		if (paused)
		{
			paused = false;
			//UserInterface::ph.eraseFromMap("PAUSED");

		}
		else
		{
			//UserInterface::showButton("PAUSED", "PAUSE");
			paused = true;
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
		static string buttonID;
		static unsigned functionCallID;
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