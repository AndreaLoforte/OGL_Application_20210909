#include<text.h>
#include<inputs.h>

namespace textRendererNS {

	void PrintHelper::mapNewString(std::string id, std::string s)
	{
		mapIDbutton_button.mapString(id, s);
	}



	void PrintHelper::mapButtonOnBranch(std::string branchID, std::string id, std::string s)
	{
		mapIDbutton_button.mapStringOnBranch(branchID, id, s,mapIDbutton_button.text_scale);
	}

	uiNS::ButtonInterface* PrintHelper::mapButtonOnBranch(std::string branchID, std::string id, std::string s, float scale)
	{
		return mapIDbutton_button.mapStringOnBranch(branchID, id, s, scale);
	}
	

	void PrintHelper::concatenate(std::string id, std::string s)
	{
		mapIDbutton_button.concatenate(id, s);
	}

	void PrintHelper::eraseFromMap(std::string key)
	{
		mapIDbutton_button.erase(key);
	}

	void PrintHelper::eraseByBranch(std::string branchID)
	{
		/*flag to exit inner for cycle when element from the map 
		has been deleted (must avoid inspecting again 
		mapIDbutton_button.map[i] because does not exist anymore) */
		static bool childDeleted = false;
		/*double iteration because a text may have multiple parent branches*/
		for (int i = 0; i < mapIDbutton_button.buttonslistSize; i++)
		{
			childDeleted = false;

			for (int j = 0;!childDeleted && j < mapIDbutton_button.buttons[i].button.parentNodes.size(); j++)
				if (mapIDbutton_button.buttons[i].button.parentNodes[j] == branchID)
				{/*deleting always using the key */
					mapIDbutton_button.erase(mapIDbutton_button.buttons[i].button.buttonID);
					childDeleted = true;
					/*when I delete the i-th elemen from the map
					the i+1-th element becomes the i-th element
					=> must decrease i in order to check this new i-th element*/
					--i;
				}
		}
	}

	void PrintHelper::cascadeEraseFromMap(std::string key)
	{
		ButtonsList::buttonsListIter itbeg = mapIDbutton_button.getIteratorOf(key);
		ButtonsList::buttonsListIter itend = mapIDbutton_button.end();
		mapIDbutton_button.eraseByIterator(itbeg, itend);
	}


	void PrintHelper::update()
	{
		text_tot_size = mapIDbutton_button.text_tot_size;
		if (text_tot_size > VBO_size)
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

	
	/*static attribute of the class*/
	GLuint PrintHelper::classVBBI = 0;

	void PrintHelper::create() 
	{
		VBO = new GLuint;
		VBO_size = 1;
		glGenBuffers(VBO_size, &VBO[0]);
		initBuffer();
		glGenVertexArrays(1, &VAO);
		instanceVBBI = classVBBI;
		classVBBI++;
	}

	void PrintHelper::initBuffer() {


		GLfloat vertices[6][4];
		for (int i = 0; i < VBO_size; i++)
		{
			glNamedBufferStorage(VBO[i], sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);
		}
	}

}