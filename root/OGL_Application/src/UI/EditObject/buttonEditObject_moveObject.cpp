#include<buttonEditObject.h>
#include<userInterface.h>
#include<applicationDerivedObject.h>
#include<applicationObjectManager.h>
#include<objectControlsInterface.h>
#include<inputs.h>
#include<app.h>
#include<AI.h>
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
		/*myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrX(stdLibHelper::array3fScalarProduct(absoluteXDir, obj_cam_normalized)*10 );
		myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrZ(stdLibHelper::array3fScalarProduct(absoluteZDir, obj_cam_normalized)*10 );*/

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
		/*myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrX(stdLibHelper::array3fScalarProduct(absoluteXDir, obj_cam_ortogonal)*10 );
		myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrZ(stdLibHelper::array3fScalarProduct(absoluteZDir, obj_cam_ortogonal)*10 );*/

	}


	

	void EditObjectModeButton::key_callbackMove(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_RELEASE) return;
		if (mods == GLFW_MOD_CONTROL)
		{

			if (key == GLFW_KEY_LEFT)
			{
				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotZ(-1);

				return;
			}
			if (key == GLFW_KEY_RIGHT)
			{
				myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotZ(1);

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
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrZ(-1);
			break;
		case GLFW_KEY_S:
			//camRelativeShiftZ(-1);
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrZ(1);
			break;
		case GLFW_KEY_D:
			//camRelativeShiftX(1);
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrX(-1);
			break;
		case GLFW_KEY_A:
			//camRelativeShiftX(-1);
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrX(1);
			break;
		case GLFW_KEY_1:
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrY(-1);
			break;
		case GLFW_KEY_2:
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOtrY(1);
			break;

		case GLFW_KEY_UP:
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotX(1);
			break;
		case GLFW_KEY_DOWN:
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotX(-1);
			break;
		case GLFW_KEY_RIGHT:
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotY(-1);
			break;
		case GLFW_KEY_LEFT:
			myobjectNS::ApplicationObjectManager::getEditableCollector()->AOrotY(1);
			break;
		case GLFW_KEY_R:
			fpcameraNS::CameraManager::resetAll();
			UserInterface::control->app_pt->resetAll();
			break;

		}
	}



}



