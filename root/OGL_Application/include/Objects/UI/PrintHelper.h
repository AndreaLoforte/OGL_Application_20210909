#pragma once
#include<string>
#include<text.h>
#include<buttonsList.h>
namespace textRendererNS {

	class PrintHelper {
		friend class TextRenderer;
		std::string printerOwner;

	public:
		PrintHelper(
			const std::string& s,
			const float& x = 0.0,
			const float& y = 0.0,
			const float& scale = 0.3) :
			printerOwner(s),
			mapIDbutton_button{ x,y,scale }
		{
			TextRenderer::printList.push_back(this);

		}
		~PrintHelper() {
			delete[] VBO;
		}
		float color_text[4]{ 0.3f,0.6f,0.8f,1.0f };

		ButtonsList mapIDbutton_button;

		unsigned text_tot_size = 0;
		unsigned VBO_size = 0;
		GLuint VAO;
		GLuint *VBO;
		static GLuint classVBBI;
		GLuint instanceVBBI; 
		size_t buffer_index = 0;


		void mapNewString(std::string, std::string);
		void mapButtonOnBranch(std::string, std::string, std::string);
		uiNS::ButtonInterface* mapButtonOnBranch(std::string, std::string, std::string, float);
		void concatenate(std::string, std::string);
		void eraseFromMap(std::string);
		void eraseByBranch(std::string);
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

	};



}