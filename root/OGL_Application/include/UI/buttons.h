#pragma once
#include<text.h>
#include<buttonMap.h>
#include<cluster.h>
namespace uiNS {

	struct Button {
		Button(){}
		Button(const string& bID, const string& bName,
			const float& x, const float& y, const unsigned& buttonLVL, const float& s);
		/*key*/
		string buttonID;
		/*value*/
		string buttonName;
		unsigned buttonLevel;
		/*each pair may be child of a parent hierarchy*/
		float y_min = 0.0;
		float y_min_frame = 0.0;
		float x_min = 0.0;
		float y_max = 0.0;
		float y_max_frame = 0.0;
		float x_max = 0.0;
		float textScale = 0.3;
		float height = 0.1;
		vector<string> parentNodes;
	};



	class ButtonInterface
	{
	protected:
		
	public:
		Button button;
		ButtonInterface(){}
		ButtonInterface(const Button& b) :button({ b }) {}
		//ButtonInterface(const std::string& buttonID) :button({ buttonID }) {}
		virtual const std::string& getButtonID(){ return button.buttonID; }
		std::string getButtonID_() { return button.buttonID; }
		virtual void action() {}
		virtual void setControls() {}
		void Highligt();
		float frameColor[4] = { 1.0,1.0,1.0,0.5 };
		bool isHighligted = false;
		void update(){}
		void turnOff();

};

	class EditGameButton : public ButtonInterface
	{
		string buttonID = ButtonMap::EDITGAMEMODEBUTTON;
	public:
		EditGameButton() { button.buttonID = buttonID; }
		void action() override;
		static void setControls();
		const std::string& getButtonID() override { return button.buttonID; }
	};

	class CreateObjectButton : public ButtonInterface
	{
		string buttonID = ButtonMap::CREATEBUTTON;
	public:
		CreateObjectButton() { button.buttonID = buttonID; }
		void action() override;
		static void selectObject(GLFWwindow*, int, int, int);
		const std::string& getButtonID() override { return button.buttonID; }
		
	};

	class BackButton : public ButtonInterface
	{
		string buttonID = ButtonMap::BACKBUTTON;
	public:
		BackButton() { button.buttonID = buttonID; }
		void action() override;
		//void selectObject(GLFWwindow*, int, int, int);
		const std::string& getButtonID() override { return button.buttonID; }
	};


	class DeleteObjectButton : public ButtonInterface
	{
		string buttonID = ButtonMap::DELETEBUTTON;
	public:
		DeleteObjectButton() { button.buttonID = buttonID; }
		//DeleteObjectButton() :ButtonInterface({ ButtonMap::DELETEBUTTON }) {}
		void action() override;
		static void selectObject(GLFWwindow* w, int button, int action, int mode);
		const std::string& getButtonID() override { return button.buttonID; }
	};

	class StartButton : public ButtonInterface
	{
		string buttonID = ButtonMap::STARTINGBUTTON;
		
	public:
		StartButton() { button.buttonID = buttonID; }
		//StartButton() :ButtonInterface({ ButtonMap::STARTINGBUTTON }) {}
		void action() override;
		static void menu();
		static void start();
		static void load(GLFWwindow* w, int button, int action, int mods);
		static void newProject(int,int);
		void selectObject(GLFWwindow* w, int button, int action, int mode);
		static void cursorPositionCallBack(GLFWwindow* w, double x, double y);
		static	void cursorButtonCallBack(GLFWwindow* w, int button, int action, int mode);
		void keyCallBack_startMenu(GLFWwindow* w, int key,int scancode, int action, int mode);
		const std::string& getButtonID() override { return button.buttonID; }
		static bool nogoback;
	};


	class ControlModeButton : public ButtonInterface
	{
		string buttonID = ButtonMap::CONTROLMODEBUTTON;
	public:
		ControlModeButton() { button.buttonID = buttonID; }
		void action() override;
		static void setControls();
		const std::string& getButtonID() override { return button.buttonID; }
	};

	class SaveButton : public ButtonInterface
	{
		string buttonID = ButtonMap::SAVEBUTTON;
	public:
		SaveButton() { button.buttonID = buttonID; }
		//SaveButton():ButtonInterface({ButtonMap::SAVEBUTTON}){}
		void action() override;
		static void save();
		const std::string& getButtonID() override { return button.buttonID; }
	};

	class QuitButton : public ButtonInterface
	{
		string buttonID = ButtonMap::ESCAPEBUTTON;
	public:
		QuitButton() { button.buttonID = buttonID; }
		//QuitButton() :ButtonInterface({ ButtonMap::ESCAPEBUTTON }){}
		void action() override;
		static void showMenu();
		const std::string& getButtonID() override { return button.buttonID; }
	};


}