#include<buttonEditSounds.h>
#include<sound.h>
#include<userInterface.h>
#include<applicationDerivedObject.h>
#include<applicationObjectManager.h>
#include<objectControlsInterface.h>
#include<inputs.h>
#include<app.h>
#include<AI.h>
#include<cluster.h>
#include<toStringLib.h>

using namespace myobjectNS;

namespace uiNS
{

	void EditSoundsButton::switchSoundsONOFF()
	{
		soundNS::soundMap::switchSoundsOnOff();
	}




}



