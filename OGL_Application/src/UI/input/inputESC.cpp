#include<inputs.h>
#include<application/app.h>
#include<gun/gun.h>
#include<applicationDerivedObject.h>


namespace InputsNS{

	using namespace textRendererNS;


void Controls::key_callbackESC(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	/*UserInterface::showButton("ESCOPT1","Y : Save changes end quit ");
	UserInterface::showButton("ESCOPT2", "L : load next project data file");
	UserInterface::showButton("ESCOPT3", "N : cancel ");
	UserInterface::showButton("ESCOPT4", "ESC exit without save");*/


	if (action == GLFW_RELEASE) return;

	
	if (key == GLFW_KEY_Y)
	{
		App::SaveProjectData(App::projectDataFileName);

		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_N)
	{
		mode = 0;
		ph.eraseButtonByID("ESCAPEMODE");
		setAllCallbackFunction(window);
		return;
	}

	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	

}




























    
}//InputsNS