#pragma once
#include<gl3w.h>
#include<glfw3.h>
#include<buttons.h>

namespace uiNS
{


	class EditObjectModeButton : public ButtonInterface
	{
		static bool typePosition;
		static bool typeRotation;
		
	public:

		string buttonID = ButtonMap::EDITOBJECTMODEBUTTON;
		/*if not static won't initialize*/
		static clusterNS::Cluster cluster;

		EditObjectModeButton()
		{
			button.buttonID = buttonID;
		}
		//QuitNoSaveButton() : ButtonInterface({ ButtonMap::QUITNOSAVE }){}
		void action() override;
		static void goToEditObject();
		static void editPosition();
		const std::string& getButtonID() override { return button.buttonID; }
		static void cursorButtonCallBack_clusters(GLFWwindow* w, int button, int action, int mode);
		static void insertInCluster(GLFWwindow* w, int button, int action, int mode);
		static void cursorButtonCallback_editObject(GLFWwindow* w, int button, int action, int mode);
		static void editObjectMenu(GLFWwindow* w, double x, double y);
		static void editClusterMenu(GLFWwindow* w, int button, int action_, int mods);
		static void key_callbackEditColor(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void key_callbackEditSize(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void key_callback_scale(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ObjectSwitch(collectorNS::ApplicationObjectCollector* obj);
		static void clusterSwitch();
		static void key_callbackClusterColor(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void key_callbackMoveCluster(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void key_callbackMove(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursorButtoncallbackMoveObject(GLFWwindow* w, int button, int action, int mode);
		static void mouseButtonCallback_editCluster(GLFWwindow* w, int button, int action, int mode);
		static void cursorVSobject();
		static void key_callbackMoveByInsertion(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void selectObject(GLFWwindow*,int,int,int);
		static void createCluster(GLFWwindow* w, int button, int action_, int mods);
		static void mouseButtonCallback_editClusterLVL2();
	};




}