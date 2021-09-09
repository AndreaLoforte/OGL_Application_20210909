#include<textRenderer.h>
#include<inputs.h>
#include<buttonsList.h>
namespace printHelperNS {

	bool Timed_PrintHelper::triggered = false;

	/*COSTRUTTORI*/
	Timed_PrintHelper::Timed_PrintHelper(const std::string pOwner,const float x,const float y,const float scale,const std::array<float, 4> color) :
		printerOwner(pOwner),
		mapIDbutton_button{ x,y,scale },
		PrintHelper(pOwner, x, y, scale)
	{
		printerID = pOwner;		
	}


	PrintHelper::PrintHelper(const std::string& pOwner,const float x,const float y,const float scale) :
		printerOwner(pOwner),
		mapIDbutton_button{ x,y,scale }
	{
		printerID = pOwner;
		
	}

	PrintHelper::PrintHelper(const std::string& pOwner, const std::string& pID, const float x, const float y, const float scale) :
		printerOwner(pOwner),
		printerID(pID),
		mapIDbutton_button{ x,y,scale }
	{

	}

	/*#############################*/

	/*static attribute of the class*/
	GLuint PrintHelper::classVBBI = 0;

	void PrintHelper::create()
	{
		VBO = new GLuint;
		VBO_size = 1;
		/*do not use glGenBuffer*/
		glCreateBuffers(VBO_size, VBO);
		initBuffer();
		glGenVertexArrays(1, &VAO);
		instanceVBBI = classVBBI;
		classVBBI++;
	}


	/*##################*/


	void PrintHelper::initBuffer() {


		GLfloat vertices[6][4];
		for (int i = 0; i < VBO_size; i++)
		{
			glNamedBufferStorage(VBO[i], sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);
		}
	}


/*###############################*/




	

	void PrintHelper::mapNewString(std::string id, std::string s)
	{
		mapIDbutton_button.mapStringOnBranch(id, s, s, 0);
	}

	void PrintHelper::mapButtonOnBranch(std::string branchID, std::string id, std::string s)
	{
		mapIDbutton_button.mapStringOnBranch(branchID, id, s,mapIDbutton_button.text_scale);
	}

	uiNS::ButtonInterface* PrintHelper::mapButtonOnBranch(std::string branchID, std::string id, std::string s, unsigned buttonLevel,  float scale)
	{
		return mapIDbutton_button.mapStringOnBranch(branchID, id, s,buttonLevel, scale);
	}


	void PrintHelper::eraseButtonByID(std::string key)
	{
		mapIDbutton_button.erase(key);
	}

	void PrintHelper::substituteButton(const unsigned& lvl, const string buttonString)
	{
		mapIDbutton_button.substituteButton(lvl, buttonString);
	}


	void PrintHelper::eraseByBranch(std::string branchID, const unsigned& stopAtLevel)
	{
		/*flag to exit inner for cycle when element from the map 
		has been deleted (must avoid inspecting again 
		mapIDbutton_button.map[i] because does not exist anymore) */
		static bool childDeleted = false;
		/*double iteration because a text may have multiple parent branches*/
		for (int i = 0; i < mapIDbutton_button.buttonslistSize; i++)
		{
			childDeleted = false;

			//for (int j = 0;!childDeleted && j < mapIDbutton_button.buttons[i].button.parentNodes.size(); j++)
				if (mapIDbutton_button.buttons[i].button.parentNode == branchID && mapIDbutton_button.buttons[i].button.buttonLevel >= stopAtLevel)
				{
					/*deleting always using the key */
					mapIDbutton_button.erase(mapIDbutton_button.buttons[i].button.buttonID);
					childDeleted = true;
					/*when I delete the i-th elemen from the map
					the i+1-th element becomes the i-th element
					=> must decrease i in order to check this new i-th element*/
					--i;
				}
		}

		resetPosition();
	}





	void PrintHelper::cascadeEraseFromMap(std::string key)
	{/*
		ButtonsList::buttonsListIter itbeg = mapIDbutton_button.getIteratorOf(key);
		ButtonsList::buttonsListIter itend = mapIDbutton_button.end();
		mapIDbutton_button.eraseByIterator(itbeg, itend);*/
	}


	void PrintHelper::update()
	{
		text_tot_size = mapIDbutton_button.text_tot_size;
		if (text_tot_size > VBO_size )
		{
			//text_VBO_size = text_tot_size * 2;
			glDeleteBuffers(VBO_size, VBO);
			delete[] VBO;
			VBO_size = text_tot_size*2;
			VBO = new GLuint[VBO_size];
			glCreateBuffers(VBO_size, &VBO[0]);
			initBuffer();
		}

	}

	


	

	

}