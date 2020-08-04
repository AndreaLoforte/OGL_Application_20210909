#ifndef INPUTSH_H
#define INPUTSH_H

#include<mymathlib.h>
#include<fpcamera.h>
#include<text.h>
#include<map>
#include<PrintHelper.h>
class App;

namespace myobjectNS {

	class Gun;
	class PlayerCharacterOC;
}

namespace uiNS {
	class UserInterface;
}


namespace InputsNS{ 

	

    class Controls{
		/*static constexpr int L = 10, N = 10, M = 10, O = 10;
		static std::vector<int> objNumberChoosed;
		int objectIndex[L][M][N][O];
		static std::map<int, int> glfw_KeyConversion;*/
		//bool ispressed1 = false, ispressed2 = false;
        static myobjectNS::PlayerCharacterOC* player;
		static bool playerIsOn;
		
		bool moveMode = false;
		static uiNS::UserInterface* userInterface;
        static GLboolean hideCursor; 
		static int scrollCallbackCallerID;
		static printHelperNS::PrintHelper ph;
    public:
		static App* app_pt;
		static unsigned mode; //0 : control mode, 1 = moveMode, 2 = editMode

	~Controls() {}

    Controls(){
        initControls(Application::window);
		//initObjectIndex();
        
    }
        static void key_callbackControl(GLFWwindow*,int,int,int,int);
		static void cursor_callback(GLFWwindow*, double, double);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void setAllCallbackFunction(GLFWwindow* window);

		void key_callbackMove(GLFWwindow*, int, int, int, int);
		void key_callbackEdit(GLFWwindow*, int, int, int, int);
		void key_callbackESC(GLFWwindow* window, int key, int scancode, int action, int mods);
        
		void cursor_callback_editMode(GLFWwindow*, double, double);
        
		void mouse_button_callback_editMode(GLFWwindow* window, int button, int action, int mods);
        void initControls(GLFWwindow* window);
		
		void setup(App* application);
		
		void setScrollCallback(GLFWwindow*);
		void setButtonCallback(GLFWwindow*);
		void setCursorCallback(GLFWwindow*);
		
		void changeCamera() {}
		int chooseObject(int);
		/*int typing(int,int activity);
		bool NInsertion(int key, int action, int numberToInsert, vector<float>& vec);*/
		void switchPhysics() {/* App::switchPhysics();*/ }
		static void setPlayer(myobjectNS::PlayerCharacterOC* pc) { player = pc; playerIsOn = true; }
		static void setScrollCallbackCallerID(int i)
		{
			scrollCallbackCallerID = i;
		}

		void setUserInterface(uiNS::UserInterface*ui) { userInterface = ui; }
};



	class TextTyper {
	public:
		string text;
		bool completed_total = false;
		string stringInsertion(int, int);

	};




	class Typer {
		static constexpr int L = 10, N = 10, M = 10, O = 10;
		static std::vector<int> objNumberChoosed;
		int objectIndex[L][M][N][O];
		static std::map<int, int> glfw_KeyConversion;
		
	public:
		TextTyper textTyper;
		bool completed_partial = false;
		bool completed_total = false;
		string partial_string;
		string total_string;
		string return_string;
		std::vector<float> vec;
		
		Typer()
		{
			initObjectIndex();
		}
		void initObjectIndex();
		int typing(int, int activity);
		bool NInsertion(int key, int action, int numberToInsert, vector<float>& vec);
		std::string NInsertion2(int key, int action, int numberToInsert, vector<float>& vec);
		int typing2(int key, int action);
		//string stringInsertion(int, int);
		
	};


	

    

}//namespace



#endif