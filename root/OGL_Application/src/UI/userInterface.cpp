#include<userInterface.h>
#include<inputs.h>

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
	textRendererNS::PrintHelper UserInterface::ph{ "uiInterface",-0.9f,0.9f};
	InputsNS::Controls* UserInterface::control;
	

	void UserInterface::printExistingObjects()
	{
		UserInterface::deleteAllButtons();
		UserInterface::ph.resetPosition();
		UserInterface::setButton(ButtonMap::BACKBUTTON);

		for (int i = 0; i < myobjectNS::ApplicationObjectManager::ApplicationCollectorList.size(); i++)
		{
			string s =
				myobjectNS::ApplicationObjectManager::
				ApplicationCollectorList[i]->getCollectorID();//+"_"+std::to_string(i);

			UserInterface::ph.mapButtonOnBranch(
				UserInterface::getParentButton()->getButtonID(),
				s,
				s);
		}
	}




	void UserInterface::mapButtonOnParentBranch(const string& stringID, const string& stringValue)
	{
		ph.mapButtonOnBranch(
			getParentButton()->getButtonID(),
			stringID,
			stringValue);
	}



	void UserInterface::printAssetObjectsList()
	{

		UserInterface::deleteAllButtons();
		UserInterface::ph.resetPosition();

		std::map<std::string, int>* assetIndex = AssetNS::Assets::getAssetIndex();
		std::map<std::string, int>::iterator it = assetIndex->begin();


		for (it; it != assetIndex->end(); it++)
			UserInterface::ph.mapButtonOnBranch(
				UserInterface::getParentButton()->getButtonID(),
				it->first,
				it->first);

	}



	void UserInterface::setButton(const string& bID)
	{
		ButtonInterface* b = ButtonMap::getButtonByID(bID);
		if (b->getButtonID() != "")
		ph.mapButtonOnBranch(
			getParentButton()->getButtonID(),
			b->getButtonID(),
			b->getButtonID());

	}

	void UserInterface::setButton(const string& bID, const string& bName)
	{
		ButtonInterface* b = ButtonMap::getButtonByID(bID);
		if(b->getButtonID() != "")
		ph.mapButtonOnBranch(
			getParentButton()->getButtonID(),
			b->getButtonID(),
			b->getButtonID());

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
			UserInterface::mapButtonOnParentBranch("PAUSED", "PAUSE");
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

	UserInterface::UserInterface(InputsNS::Controls * c) 
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
		start->action();
	}

	void UserInterface::deleteButtonsByBranch(const string& buttonID)
	{
		buttonFlow.pop_back();
		ph.eraseByBranch(buttonID);
	}

	void UserInterface::deleteAllButtons()
	{
		using namespace textRendererNS;
		for (int i = 0; i < buttonFlow.size(); i++)
			ph.eraseByBranch(buttonFlow[i]->getButtonID());

		ph.resetPosition();
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

		return "CLICK_NO_BUTTON";
	}

	



	
}