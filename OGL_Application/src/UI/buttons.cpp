#include<buttons.h>
#include<applicationObjectManager.h>
#include<inputs.h>
#include<app.h>


namespace uiNS {

	Button::Button(const string& bID, const string& bName,
		const float& x, const float& y, const unsigned& buttonLVL, const float& s) :
		x_min(x),
		y_min(y),
		y_min_frame(y),
		y_max(y),
		textScale(s),
		buttonID(bID),
		buttonName(bName),
		buttonLevel(buttonLVL)
	{
		x_max = x_min + textScale * bName.length()*0.06;
		
		/*height is non linear function of text scale!*/
		//below my best guess as far : 
		constexpr float f1 = 0.05;
		
		float f2 = f1 * (8- textScale*.9);/*5 per 0.3 e 2, 8 per 0.6-1.3*/
		height = (f1*textScale + pow(f1*textScale, 1.0-textScale*f2)); 
		y_min -= height;
		
		/*frames have impact only in the 
		interaction with the cursor*/
		y_min_frame = y_min+0.03;
		y_max_frame = y_max+0.06;

	}


	void ButtonInterface::Highligt()
	{
		frameColor[0] = 1.0;
		frameColor[1] = 1.0;
		frameColor[2] = 1.0;
		frameColor[3] = 1.0;

		isHighligted = true;
	}

	void ButtonInterface::turnOff()
	{

		frameColor[3] = 0.5;
		isHighligted = false;
	}






	void EditGameButton::action()
	{
		/*UserInterface::setFlags(false, false, false);

		
		UserInterface::bfl.setMouseButtonCallback(setControls);
		return;*/

	}

	
	void EditGameButton::setControls()
	{


	}




	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	void QuitButton::action()
	{
		showMenu();
	}

	void QuitButton::showMenu()
	{

		
		UserInterface::phc.showDropDownMenu(NonButtonMap::QUITBUTTON,
			{ ButtonMap::QUITANDSAVE,ButtonMap::QUITNOSAVE, ButtonMap::BACKBUTTON });


		if (UserInterface::cursorPointing(ButtonMap::QUITANDSAVE))
		{
			App::SaveProjectData(App::projectDataFileName);
			glfwSetWindowShouldClose(Application::window, GLFW_TRUE);
		}

		if(UserInterface::cursorPointing(ButtonMap::QUITNOSAVE))
			glfwSetWindowShouldClose(Application::window, GLFW_TRUE);

		
		if (UserInterface::cursorPointing(ButtonMap::BACKBUTTON))
			;/*UserInterface::back();*/


	}


}