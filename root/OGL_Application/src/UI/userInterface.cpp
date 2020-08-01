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
	map<string, ButtonInterface> UserInterface::buttonsList;
	//vector<ButtonInterface*> UserInterface::parentFlow;
	StartButton* UserInterface::start;
	bool UserInterface::paused{ true };
	bool UserInterface::physicsOn{ true };
	bool UserInterface::AIon{ true };
	textRendererNS::PrintHelper UserInterface::ph{ "uiInterface",-0.9f,0.9f};
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
		textRendererNS::TextRenderer::printList.push_back(&ph);
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

		UserInterface::bfl.setMouseButtonCallback(StartButton::menu);
		StartButton::menu();
		UserInterface::bfl.setMouseCursorCallback(StartButton::cursorPositionCallBack);
		


	}




	void UserInterface::back()
	{
		deleteAllButtons();
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
				showButton("WARNING", "CREATE A NEW PROJECT OR LOAD AN EXISTING ONE");
				return;
			}
				buttonFlow.erase(it);
			b = ButtonMap::getButtonByID(buttonFlow.back()->getButtonID());
			if(b)
				b->action();
		} while (h++ < size && !b);

	}
	
	void UserInterface::ShowBackButton()
	{
		UserInterface::showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);

	}


	bool UserInterface::enableBack(const string& buttonID)
	{
		UserInterface::ShowBackButton();
		if (buttonID == ButtonMap::BACKBUTTON)
		{
			UserInterface::back();
			return true;
		}
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
		for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
		{
			if (ph.mapIDbutton_button.buttons[i].isHighligted)
				ph.mapIDbutton_button.buttons[i].turnOff();
		}
	}

	void UserInterface::highlightButton(ButtonInterface* BI)
	{
		for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
		{
			if (ph.mapIDbutton_button.buttons[i].isHighligted)
				ph.mapIDbutton_button.buttons[i].turnOff();
		}
		BI->Highligt();
	}

	ButtonInterface* UserInterface::getButtonFromList(const string& bid)
	{
		for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
			if (ph.mapIDbutton_button.buttons[i].getButtonID() == bid)
				return &ph.mapIDbutton_button.buttons[i];
	}



	void UserInterface::update()
	{
		for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
		{
			ph.mapIDbutton_button.buttons[i].update();
		}

		/*avoid overflow*/
		if (frameID > 10000000)
			frameID = 0;
		frameID++;
	}

	



	void UserInterface::printAssetObjectsList()
	{

		UserInterface::deleteAllButtons();
		UserInterface::ph.resetPosition();

		std::map<std::string, int>* assetIndex = AssetNS::Assets::getAssetIndex();
		std::map<std::string, int>::iterator it = assetIndex->begin();


		for (it; it != assetIndex->end(); it++)
			UserInterface::showButton(it->first,it->first);

		showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);

	}


	void UserInterface::printExistingObjects()
	{

		for (int i = 0; i < myobjectNS::ApplicationObjectManager::ApplicationCollectorList.size(); i++)
		{
			string s =
				myobjectNS::ApplicationObjectManager::
				ApplicationCollectorList[i]->getCollectorID();//+"_"+std::to_string(i);
			
			UserInterface::showButton(s, s);
		}
		UserInterface::showButton(ButtonMap::BACKBUTTON, ButtonMap::BACKBUTTON);
	}


	void UserInterface::clickButton(const string& stringID)
	{
		ButtonInterface* newB = new ButtonInterface(*UserInterface::getButtonFromList(stringID));
		buttonFlow.push_back(newB);

	}

	void UserInterface::showButton(const string& stringID, const string& stringValue, const float& scale)
	{
		string partentID = buttonFlow.back()->getButtonID();/* getParentButton()->getButtonID();*/
		ButtonInterface* newbutton{
		ph.mapButtonOnBranch(
			partentID,
			stringID,
			stringValue, scale) };

		buttonsList.emplace(stringID,*newbutton);
	}


	




	void UserInterface::pause()
	{

		if (paused)
		{
			paused = false;
			UserInterface::ph.eraseFromMap("PAUSED");

		}
		else
		{
			UserInterface::showButton("PAUSED", "PAUSE");
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

	
	void UserInterface::deleteButtonsByBranch(const string& buttonID)
	{
		buttonFlow.pop_back();
		ph.eraseByBranch(buttonID);
	}


	void UserInterface::deleteNonButtonsByBranch(const string& buttonID)
	{
		ph.eraseByBranch(buttonID);
	}

	void UserInterface::deleteAllButtons()
	{
		using namespace textRendererNS;
		for (int i = 0; i < buttonFlow.size(); i++)
			ph.eraseByBranch(buttonFlow[i]->getButtonID());
	}
	

	std::string UserInterface::cursorVStext(const double& x, const double& y)
	{
		using namespace textRendererNS;

		/*x,y go from 0 to window_width, window_height.*/
		float transformed_x = (x - Application::window_width / 2) / Application::window_width * 2;
		float transformed_y = -(y - Application::window_height / 2) / Application::window_height * 2;

		for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
			if (transformed_x < ph.mapIDbutton_button.buttons[i].button.x_min ||
				transformed_x > ph.mapIDbutton_button.buttons[i].button.x_max ||
				transformed_y < ph.mapIDbutton_button.buttons[i].button.y_min_frame ||
				transformed_y > ph.mapIDbutton_button.buttons[i].button.y_max_frame)
				/*do nothing*/;
			else
				return ph.mapIDbutton_button.buttons[i].button.buttonID;

		return NonButtonMap::NOBUTTON;
	}


	std::string UserInterface::cursorVStext()
	{
		using namespace textRendererNS;

		/*x,y go from 0 to window_width, window_height.*/
		float transformed_x = (UserInterface::cursor_x - Application::window_width / 2) / Application::window_width * 2;
		float transformed_y = -(UserInterface::cursor_y - Application::window_height / 2) / Application::window_height * 2;

		for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
			if (transformed_x < ph.mapIDbutton_button.buttons[i].button.x_min ||
				transformed_x > ph.mapIDbutton_button.buttons[i].button.x_max ||
				transformed_y < ph.mapIDbutton_button.buttons[i].button.y_min_frame ||
				transformed_y > ph.mapIDbutton_button.buttons[i].button.y_max_frame)
				/*do nothing*/;
			else
				return ph.mapIDbutton_button.buttons[i].button.buttonID;

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

			for (int i = 0; i < ph.mapIDbutton_button.buttons.size(); i++)
				if (transformed_x < ph.mapIDbutton_button.buttons[i].button.x_min ||
					transformed_x > ph.mapIDbutton_button.buttons[i].button.x_max ||
					transformed_y < ph.mapIDbutton_button.buttons[i].button.y_min_frame ||
					transformed_y > ph.mapIDbutton_button.buttons[i].button.y_max_frame)
					/*if cursor is not upon this button do nothing*/;
				else
				{
					buttonID = ph.mapIDbutton_button.buttons[i].button.buttonID;
					return bID == buttonID;
				}
						

			/*if cursor is outside every button frame assign NOBUTTON*/
				buttonID = NonButtonMap::NOBUTTON;
				return bID == buttonID;
			
		}
		else
			return bID == buttonID;
			

	}



	
}