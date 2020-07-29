#pragma once

#include<buttons.h>

namespace uiNS
{


	class EditObjectModeButton : public ButtonInterface
	{

		
	public:

		string buttonID = ButtonMap::EDITOBJECTMODEBUTTON;
		/*if not static won't initialize*/
		static myobjectNS::Cluster cluster;

		EditObjectModeButton()
		{
			button.buttonID = buttonID;
		}
		//QuitNoSaveButton() : ButtonInterface({ ButtonMap::QUITNOSAVE }){}
		void action() override;
		const std::string& getButtonID() override { return button.buttonID; }
		void cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode);
		void editObject(GLFWwindow* w, int button, int action, int mode);
		void key_callbackEditColor(GLFWwindow* window, int key, int scancode, int action, int mods);
		void key_callbackEditSize(GLFWwindow* window, int key, int scancode, int action, int mods);
		void ObjectSwitch(collectorNS::ApplicationObjectCollector* obj);
		void clusterSwitch();
		void key_callbackClusterColor(GLFWwindow* window, int key, int scancode, int action, int mods);
		void key_callbackMoveCluster(GLFWwindow* window, int key, int scancode, int action, int mods);
		void key_callbackMove(GLFWwindow* window, int key, int scancode, int action, int mods);
		void insertInCluster(GLFWwindow* w, int button, int action, int mode);
	};




}