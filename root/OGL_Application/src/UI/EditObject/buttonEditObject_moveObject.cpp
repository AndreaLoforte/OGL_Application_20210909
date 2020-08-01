#include<buttonEditObject.h>
#include<userInterface.h>
#include<applicationDerivedObject.h>
#include<applicationObjectManager.h>
#include<objectControlsInterface.h>
#include<inputs.h>
#include<app.h>
#include<AI.h>
#include<toStringLib.h>
namespace uiNS
{




	void camRelativeShiftZ(const int& sign)
	{
		using namespace myobjectNS;
		using namespace mymathlibNS;

		const fpcameraNS::Transformation* cam{ fpcameraNS::CameraManager::getActiveCameraPT() };
		const array<float, 3> camPos = cam->getCamGLBCoords();
		ApplicationObject* obj = ApplicationObjectManager::getEditableCollector()->getBody();
		const array<float, 3> objPos = obj->AOposition;
		//ApplicationObjectManager::getEditableCollector()->getBody()->AOposition;

		array<float, 3> object_cam_distance =
		{
			camPos[0] - objPos[0],
			/*camPos[1] - objPos[1]*/0.0,
			camPos[2] - objPos[2],
		};

		array<float, 3> obj_cam_normalized = mymathlibNS::stdLibHelper::array3Normalize(object_cam_distance);
		array<float, 3> obj_cam_ortogonal{ obj_cam_normalized[2],obj_cam_normalized[1],obj_cam_normalized[0] };


		const array<float, 3> absoluteZDir{ 0.0,0.0,-sign * 1.0 };
		const array<float, 3> absoluteXDir{ -sign * 1.0,0.0,0.0 };


		ApplicationObjectManager::getEditableCollector()->AOtr(
			stdLibHelper::array3fScalarProduct(absoluteXDir, obj_cam_normalized) * 100,
			0.0,
			stdLibHelper::array3fScalarProduct(absoluteZDir, obj_cam_normalized) * 100);

	}


	void camRelativeShiftX(const int& sign)
	{
		const fpcameraNS::Transformation* cam{ fpcameraNS::CameraManager::getActiveCameraPT() };
		const array<float, 3> camPos = cam->getCamGLBCoords();
		const array<float, 3> objPos =
			myobjectNS::ApplicationObjectManager::getEditableCollector()->getBody()->AOposition;

		array<float, 3> object_cam_distance =
		{
			camPos[0] - objPos[0],
			/*camPos[1] - objPos[1]*/0.0,
			camPos[2] - objPos[2],
		};

		array<float, 3> obj_cam_normalized = mymathlibNS::stdLibHelper::array3Normalize(object_cam_distance);
		array<float, 3> obj_cam_ortogonal
		{ mymathlibNS::stdLibHelper::array3Normalize(
			mymathlibNS::stdLibHelper::array3VectorProduct(obj_cam_normalized,{0,1,0})
			) };


		const array<float, 3> absoluteZDir{ 0.0,0.0,-sign * 1.0 };
		const array<float, 3> absoluteXDir{ -sign * 1.0,0.0,0.0 };
		using namespace mymathlibNS;

		myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtr(
			stdLibHelper::array3fScalarProduct(absoluteXDir, obj_cam_ortogonal) * 100,
			0.0,
			stdLibHelper::array3fScalarProduct(absoluteZDir, obj_cam_ortogonal) * 100);

	}





	


	void EditObjectModeButton::key_callbackMove(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		UserInterface::showButton(uiNS::ButtonMap::EDITOBJECTMODEBUTTON,
			"Move the " +
			myobjectNS::ApplicationObjectManager::getEditableObjectName() +
			" object using A,S,D,W,1,2 and directional Arrows");

		collectorNS::ApplicationObjectCollector* obj = myobjectNS::ApplicationObjectManager::getEditableCollector();
		UserInterface::showButton(NonButtonMap::TYPEPOSITION, "OBJECT POSITION X,Y,Z : " + tostringNS::stdToString::arrayfloat3(obj->getBody()->AOposition));
		UserInterface::showButton(NonButtonMap::TYPEROTATION, "OBJECT ROTATION X°,Y°,Z° : " + tostringNS::stdToString::arrayfloat3(obj->getBody()->AOrot));

		

		if (action == GLFW_RELEASE) return;

		if (typePosition)
		{
			std::vector<float> pos;
				
			UserInterface::showButton(NonButtonMap::TYPEPOSITION, "OBJECT POSITION X,Y,Z : "+ UserInterface::typer.NInsertion2(key, action, 3, pos));
			if(UserInterface::typer.completed_total)
				obj->getBody()->setPosition({ pos[0],pos[1],pos[2] });
			return;
		}

		if (typeRotation)
		{
			std::vector<float> rot;
			UserInterface::showButton(NonButtonMap::TYPEROTATION, "OBJECT ROTATION X,Y,Z : " + UserInterface::typer.NInsertion2(key, action, 3, rot));
			if (UserInterface::typer.completed_total)
				obj->getBody()->setPosition({ rot[0],rot[1],rot[2] });
			return;
		}

		if (mods == GLFW_MOD_CONTROL)
		{

			if (key == GLFW_KEY_LEFT)
			{
				obj->AOrotZ(-1);

				return;
			}
			if (key == GLFW_KEY_RIGHT)
			{
				obj->AOrotZ(1);

				return;
			}

		}

		switch (key) {
		case GLFW_KEY_I:
			textRendererNS::TextRenderer::printEditableObjectInfos();
			break;
		case GLFW_KEY_C:
			fpcameraNS::CameraManager::switchCamera();
			break;
		case GLFW_KEY_W:
			//camRelativeShiftZ(1);
			obj->AOtrZ(-1);
			break;
		case GLFW_KEY_S:
			//camRelativeShiftZ(-1);
			obj->AOtrZ(1);
			break;
		case GLFW_KEY_D:
			//camRelativeShiftX(1);
			obj->AOtrX(-1);
			break;
		case GLFW_KEY_A:
			//camRelativeShiftX(-1);
			obj->AOtrX(1);
			break;
		case GLFW_KEY_1:
			obj->AOtrY(-1);
			break;
		case GLFW_KEY_2:
			obj->AOtrY(1);
			break;

		case GLFW_KEY_UP:
			obj->AOrotX(1);
			break;
		case GLFW_KEY_DOWN:
			obj->AOrotX(-1);
			break;
		case GLFW_KEY_RIGHT:
			obj->AOrotY(-1);
			break;
		case GLFW_KEY_LEFT:
			obj->AOrotY(1);
			break;
		case GLFW_KEY_R:
			fpcameraNS::CameraManager::resetAll();
			UserInterface::control->app_pt->resetAll();
			break;

		}


		UserInterface::showButton(NonButtonMap::TYPEPOSITION, "OBJECT POSITION X,Y,Z : " + tostringNS::stdToString::arrayfloat3(obj->getBody()->AOposition));
		UserInterface::showButton(NonButtonMap::TYPEROTATION, "OBJECT ROTATION X°,Y°,Z° : " + tostringNS::stdToString::arrayfloat3(obj->getBody()->AOrot));
	}




	
	void EditObjectModeButton::cursor_callbackMoveObject(GLFWwindow* w, int button, int action, int mods)
	{
		if (action == GLFW_RELEASE) return;
		std::string buttonID = UserInterface::cursorVStext(UserInterface::cursor_x, UserInterface::cursor_y);

		if (buttonID == NonButtonMap::TYPEPOSITION)
		{
			typeRotation = false;
			typePosition = true;
			key_callbackMove(Application::window, 0, 0, 1, 0);
			return;
		}
		if (buttonID == NonButtonMap::TYPEROTATION)
		{
			typePosition = false;
			typeRotation = true;
			key_callbackMove(Application::window, 0, 0, 1, 0);
			return;
		}
		
		if (buttonID == NonButtonMap::NOBUTTON)
		{
			typePosition = false;
			typeRotation = false;
			key_callbackMove(Application::window, 0, 0, 1, 0);
			return;
		}

		if (UserInterface::enableBack(buttonID))
			return;
		UserInterface::bfl.setMouseButtonCallback(editObject);
		

	}





	void EditObjectModeButton::key_callbackMoveByInsertion(GLFWwindow* window, int key, int scancode, int action, int mods)
	{}





	/*this function should be able to recognize when the cursor is upon an object so that it can be selected and then moved*/
	void EditObjectModeButton::cursorVSobject()
	{}



}



