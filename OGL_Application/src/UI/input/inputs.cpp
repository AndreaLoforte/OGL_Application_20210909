#include<inputs.h>
#include<app.h>
#include<gun.h>
#include<playercharacter.h>

namespace InputsNS{

	using namespace textRendererNS;

	printHelperNS::PrintHelper Controls::ph{ "Controls" };
	bool Controls::playerIsOn = false;//settato a true quando il puntatore a gun di controls viene settato
	myobjectNS::PlayerCharacterOC* Controls::player;
	GLboolean Controls::hideCursor = true;
	int Controls::scrollCallbackCallerID = 0;
	unsigned Controls::mode = 0;
	unsigned Controls::activeCameraIndex = 0;
	float Controls::stored_cursor_coords[3][2]{ 0.0 };
	uiNS::UserInterface* Controls::userInterface;
	App* Controls::app_pt;
	bool Controls::load_stored_cursor_coords = true;
	std::vector<int> Typer::objNumberChoosed;
	std::map<int, int> Typer::glfw_KeyConversion
	{ {48,0},{49,1},{50,2},{51,3},{52,4},{53,5},{54,6},{55,7},{56,8},{57,9} };



	void Typer::initObjectIndex() {

		for(int l = 0; l < L ; l++)
		for (int m = 0; m < M; m++) {
			for (int n = 0; n < N; n++)
				for (int o = 0; o < O; o++)
				objectIndex[l][m][n][o] = l*1000 + m * 100 + n*10+o;
		}

		/*objectIndex = [0,1,2,3,4,5,6,7,8,9],
						[10,11,12,13,14,15,16,17,18,19],
						....
						....
		*/
	}


	void Controls::setAllCallbackFunction(GLFWwindow* window)
	{

		if (mode == 0) 
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			auto L_key_callbackControl = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
			{
				static_cast<Controls*>(glfwGetWindowUserPointer(w))->key_callbackControl(w, i1, i2, i3, i4);
			};
			glfwSetKeyCallback(window, L_key_callbackControl);

			auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
			{
				static_cast<Controls*>(glfwGetWindowUserPointer(w))->cursor_callback(w, d1, d2);
			};
			glfwSetCursorPosCallback(window, L_cursor_callback);

			auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
			{
				static_cast<Controls*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, i1, i2, i3);
			};
			glfwSetMouseButtonCallback(window, L_mouse_button_callback);

			return;
		}

		////EDITOBJECT MODE
		//if (mode == 1) 
		//{
		//	auto L_key_callbackMove = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
		//	{
		//		static_cast<Controls*>(glfwGetWindowUserPointer(w))->key_callbackMove(w, i1, i2, i3, i4);
		//	};
		//	glfwSetKeyCallback(window, L_key_callbackMove);
		//	return;

		//}

		////EDITGAME MODE
		//if (mode == 2) 
		//{
		//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//	auto L_key_callbackEdit = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
		//	{
		//		static_cast<Controls*>(glfwGetWindowUserPointer(w))->key_callbackEdit(w, i1, i2, i3, i4);
		//	};
		//	glfwSetKeyCallback(window, L_key_callbackEdit);

		//	auto L_cursor_callback = [](GLFWwindow* w, double d1, double d2)
		//	{
		//		static_cast<Controls*>(glfwGetWindowUserPointer(w))->cursor_callback_editMode(w, d1, d2);
		//	};
		//	glfwSetCursorPosCallback(window, L_cursor_callback);

		//	auto L_mouse_button_callback = [](GLFWwindow* w, int i1, int i2, int i3)
		//	{
		//		static_cast<Controls*>(glfwGetWindowUserPointer(w))->mouse_button_callback_editMode(w, i1, i2, i3);
		//	};
		//	glfwSetMouseButtonCallback(window, L_mouse_button_callback);

		//	return;
		//}

		//if (mode == 3) 
		//{
		//	auto L_key_callbackESC = [](GLFWwindow* w, int i1, int i2, int i3, int i4)
		//	{
		//		//casto w a puntatore alla funzione key_callback di Controls
		//		static_cast<Controls*>(glfwGetWindowUserPointer(w))->key_callbackESC(w, i1, i2, i3, i4);
		//	};
		//	glfwSetKeyCallback(window, L_key_callbackESC);

		//	

		//	return;
		//}




	}



	void Controls::initControls(GLFWwindow* window)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

		glfwSetWindowUserPointer(window, this);

		setCursorCallback(window);
		setButtonCallback(window);
		setScrollCallback(window);
		
		setAllCallbackFunction(window);

	}

	void Controls::setup(App* application) {
		/*mode is set inside in the construction of the
		button interface*/
		//mode = 0;
		initControls(Application::window);
		//initObjectIndex();
		app_pt = application;

	}


std::string TYPINGID = "TYPING";




vector<bool>  Typer::insertionSelector;
vector<bool>  Typer::totalInsertion;
vector<float> Typer::insertedNumbers;
unsigned      Typer::insertionIndex = 0;
int Typer::iterationIndex = 0;
vector<float>* Typer::p = NULL;



void  Typer::reset(vector<float>* vector, int numbersToEnter)
{
	p = vector;
	completed_partial = false;
	completed_total = false;
	partial_string.clear();
	total_string.clear();
	return_string.clear();
	vec.clear();
	objNumberChoosed.clear();

	insertionSelector.clear();
	totalInsertion.clear();
	insertedNumbers.clear();
	insertionIndex = 0;
	iterationIndex = 0;



	for (int i = 0; i < numbersToEnter; i++)
	{
		insertionSelector.push_back(false);
		totalInsertion.push_back(false);
		insertedNumbers.push_back(-1);
	}

}



/*this second version of NInsertion returns the partial number entered by the user
instead of returning a bool. While Completion is specified by the boolean member attribute "completed" */
string Typer::NInsertion2(int key, int action, int numberToInsert, vector<float>& returnetVec)
{
	
	if (p == NULL || p!=&returnetVec || numberToInsert == 0)
		reset(&returnetVec,numberToInsert);


	insertionSelector[insertionIndex] = true;


	if (insertionSelector[insertionIndex] && insertionIndex < numberToInsert)
	{

		insertedNumbers[insertionIndex] = typing2(key, action);
		if (insertedNumbers[insertionIndex] >= 0)
		{
			if (completed_partial)
			{
				completed_partial = false;
				partial_string.clear();
				total_string += " ";// std::to_string((int)insertedNumbers[insertionIndex]);
				insertionSelector[insertionIndex] = false;
				totalInsertion[insertionIndex] = true;
				
				completed_total = true;
				for (int i = 0; i < totalInsertion.size(); i++)
					completed_total &= totalInsertion[i];

				if (completed_total)
				{
					returnetVec = insertedNumbers;

					/*set parameters so that at 
					next call will reset all variables*/
					numberToInsert = 0;
					p = NULL;

					return total_string;
				}

				if (insertionIndex < numberToInsert - 1)
					insertionSelector[++insertionIndex] = true;
				return total_string;
			}
			else
			{
				completed_total = false;

				total_string += std::to_string((int)insertedNumbers[insertionIndex]);
				return total_string;
			}
				
			
		}
		else
		{
			completed_total = false;
			return total_string;
		}
			
	}

}



int Typer::typing2(int key, int action) {


	


	if (key == GLFW_KEY_BACKSPACE)
	{
		/*objNumberChoosed.clear();
		iterationIndex = 0;
		return -1;*/
	}


	if (
		(key == GLFW_KEY_0 ||
			key == GLFW_KEY_1 ||
			key == GLFW_KEY_2 ||
			key == GLFW_KEY_3 ||
			key == GLFW_KEY_4 ||
			key == GLFW_KEY_5 ||
			key == GLFW_KEY_6 ||
			key == GLFW_KEY_7 ||
			key == GLFW_KEY_8 ||
			key == GLFW_KEY_9))
	{
		if (action != GLFW_RELEASE)
		{
			objNumberChoosed.push_back(glfw_KeyConversion[key]);
			//n += std::to_string(objNumberChoosed[iterationIndex++]);
			completed_partial = false;
			return objNumberChoosed[iterationIndex++];
		}
		return -2;
	}

	if (key == GLFW_KEY_ENTER && objNumberChoosed.size() == 1)
	{
		completed_partial = true;
		int result = objectIndex[0][0][0][objNumberChoosed[0]];
		iterationIndex = 0;
		objNumberChoosed.clear();
		return result;
	}
	if (key == GLFW_KEY_ENTER && objNumberChoosed.size() == 2)
	{
		completed_partial = true;
		int result = objectIndex[0][0][objNumberChoosed[0]][objNumberChoosed[1]];
		iterationIndex = 0;
		objNumberChoosed.clear();
		return result;
	}
	if (key == GLFW_KEY_ENTER && objNumberChoosed.size() == 3)
	{
		completed_partial = true;
		int result = objectIndex[0][objNumberChoosed[0]][objNumberChoosed[1]][objNumberChoosed[2]];
		iterationIndex = 0;
		objNumberChoosed.clear();
		return result;
	}
	if (key == GLFW_KEY_ENTER && objNumberChoosed.size() == 4)
	{
		completed_partial = true;
		int result = objectIndex[objNumberChoosed[0]][objNumberChoosed[1]][objNumberChoosed[2]][objNumberChoosed[3]];
		iterationIndex = 0;
		objNumberChoosed.clear();
		return result;
	}


	return -100;

}



string TextTyper::stringInsertion(int key, int action) {

	if (action == GLFW_RELEASE) return "";
	completed_total = false;

	switch (key)
	{
		case GLFW_KEY_A:
			temp.append("a");
			break;
		case GLFW_KEY_B:
			temp.append("b");
			break;
		case GLFW_KEY_C:
			temp.append("c");
			break;
		case GLFW_KEY_D:
			temp.append("d");
			break;
		case GLFW_KEY_E:
			temp.append("e");
			break;
		case GLFW_KEY_F:
			temp.append("f");
			break;
		case GLFW_KEY_G:
			temp.append("g");
			break;
		case GLFW_KEY_H:
			temp.append("h");
			break;
		case GLFW_KEY_I:
			temp.append("i");
			break;
		case GLFW_KEY_J:
			temp.append("j");
			break;
		case GLFW_KEY_K:
			temp.append("k");
			break;
		case GLFW_KEY_L:
			temp.append("l");
			break;
		case GLFW_KEY_M:
			temp.append("m");
			break;
		case GLFW_KEY_N:
			temp.append("n");
			break;
		case GLFW_KEY_O:
			temp.append("o");
			break;
		case GLFW_KEY_P:
			temp.append("p");
			break;
		case GLFW_KEY_Q:
			temp.append("q");
			break;
		case GLFW_KEY_R:
			temp.append("r");
			break;
		case GLFW_KEY_S:
			temp.append("s");
			break;
		case GLFW_KEY_T:
			temp.append("t");
			break;
		case GLFW_KEY_U:
			temp.append("u");
			break;
		case GLFW_KEY_V:
			temp.append("v");
			break;
		case GLFW_KEY_W:
			temp.append("w");
			break;
		case GLFW_KEY_X:
			temp.append("x");
			break;
		case GLFW_KEY_Y:
			temp.append("y");
			break;
		case GLFW_KEY_Z:
			temp.append("z");
			break;
		case GLFW_KEY_1:
			temp.append("1");
			break;
		case GLFW_KEY_2:
			temp.append("2");
			break;
		case GLFW_KEY_3:
			temp.append("3");
			break;
		case GLFW_KEY_4:
			temp.append("4");
			break;
		case GLFW_KEY_5:
			temp.append("5");
			break;
		case GLFW_KEY_6:
			temp.append("6");
			break;
		case GLFW_KEY_7:
			temp.append("7");
			break;
		case GLFW_KEY_8:
			temp.append("8");
			break;
		case GLFW_KEY_9:
			temp.append("9");
			break;
		case GLFW_KEY_0:
			temp.append("0");
			break;
		case GLFW_KEY_BACKSPACE:
			if(temp.size()>0)
			temp.pop_back();
			break;
		case GLFW_KEY_ENTER:
		{
			completed_total = true;
			text = temp;
			temp.clear();
			return text;
		}
			

	}
	
	
	return temp;

}



    
}//InputsNS