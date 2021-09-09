#pragma once


#pragma once
#include<gl3w.h>
#include<glfw3.h>
#include<buttons.h>
#include<sound.h>

namespace uiNS
{


	class EditSoundsButton : public ButtonInterface
	{

	public:

		string buttonID = NonButtonMap::EDITSOUNDS;

		EditSoundsButton()
		{
			button.buttonID = buttonID;
		}
		
		static void switchSoundsONOFF();
		
	};




}