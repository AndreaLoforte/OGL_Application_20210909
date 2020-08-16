#pragma once
#include<string>
#include<textRenderer.h>
#include<buttonsList.h>
namespace printHelperNS {

	class PrintHelper {
		friend class TextRenderer;
		std::string printerOwner;
		std::string printerID;

	public:
		PrintHelper(
			const std::string& pOwner,
			const float& x = 0.0,
			const float& y = 0.0,  
			const float& scale = 0.3) :
			printerOwner(pOwner),
			mapIDbutton_button{ x,y,scale }
		{
				printerID = pOwner;
		}

		PrintHelper(
			const std::string& pOwner,
			const std::string& pID,
			const float& x = 0.0,
			const float& y = 0.0,
			const float& scale = 0.3) :
			printerOwner(pOwner),
			printerID(pID),
			mapIDbutton_button{ x,y,scale }
		{}





		~PrintHelper() {
			delete[] VBO;
		}
		float color_text[4]{ 0.3f,0.6f,0.8f,1.0f };

		textRendererNS::ButtonsList mapIDbutton_button;

		unsigned text_tot_size = 0;
		unsigned VBO_size = 0;
		GLuint VAO;
		GLuint *VBO;
		static GLuint classVBBI;
		GLuint instanceVBBI; 
		size_t buffer_index = 0;


		void mapNewString(std::string, std::string);
		void mapButtonOnBranch(std::string, std::string, std::string);
		uiNS::ButtonInterface* mapButtonOnBranch(std::string, std::string, std::string,unsigned, float);
		void eraseButtonByID(std::string);
		void eraseByBranch(std::string,const unsigned& stopAtLVL = 0);
		void cascadeEraseFromMap(std::string key);
		void update();
		void create();
		void initBuffer();
		void resetPosition() { mapIDbutton_button.resetPosition(); }
		void incrementBufferIndex()
		{
			if (buffer_index < text_tot_size)
				++buffer_index;
			else
				buffer_index = 0;
		}
		void substituteButton(const unsigned& lvl, const string txt);
		string getHeader() { return mapIDbutton_button.begin()->getButtonID(); }
	};




	class PrintHelperCollector
	{
		typedef map<string, PrintHelper>::iterator PHCollectorIT;
		/*activeButton.first = printHelperID , 
		activeButton.second = branchID*/
		
	public:
		pair<string, string> activePHbutton;
		map<string, PrintHelper> printHmap;
		PHCollectorIT it;
		void updateRenderer();
		PrintHelper& getPH(unsigned);
		PrintHelper& getPHbyID(const string& phID);
		string getPHID(unsigned);
		PrintHelper* getActivePrintHelper();
		unsigned activePHindex;
		size_t size() { return printHmap.size(); }
		PrintHelper& operator [](unsigned i);
		void showButton(const string& phID, const string& stringID, const string& text = "_DEFAULT" ,const unsigned& buttonLevel = 1, const float& scale = 0.3);
		void showDropDownMenu(const string& phID, const vector<string>& buttonsList, const bool& hideOtherPrinst = true, const float& scale = 0.3);
		void showDropDownMenu(const string& phID);
		void click(const string&, const string&);
		void turnOffAllButtons();
		void turnOffButton(const string& phID);
		void hideDropDownMenu(const string& phID, const unsigned& buttonLevel = 1);
		void substituteButton(const string& phID, const string& stringID, const string& text, const unsigned& buttonLevel);
		void hideDropDownMenu();
	};







}