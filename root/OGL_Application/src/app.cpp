#include<app.h>
#include<inputs.h>
#include<extern_definitions.h>
#include<physics.h>
#include<set>
#include<fstream>

std::string App::projectDataFileName{ "AppObj" };

textRendererNS::PrintHelper App::ph{ "App" };



void App::switchPhysics() {}




std::string App::getNewProjectDataFilename()
{
	std::vector<string> fileList;
	std::vector<string>::iterator it, backup_it;
	logNS::Logger::exploreFolder(logNS::Logger::STOREDDATADIR, fileList);
	

	vector<string> SfileNumbers;
	bool found = false;

	for (int i = 0; i < fileList.size(); i++)
	{
		//inserisco in Snumbers solo la parte di nome del file contenente il numero
		if (fileList[i].find(projectDataFileName+"_") != string::npos)
		{
			size_t pos = fileList[i].find("_");
			SfileNumbers.push_back(fileList[i].substr(pos + 1));
			found = true;
		}
		
	}

	if(found)
	{
	set<int> fileNumbers;

	//trasformo i numeri-stringa in numeri interni e li inserisco in un vettore
	for (int i = 0; i < SfileNumbers.size(); i++)
		fileNumbers.emplace(std::stoi(SfileNumbers[i]));

	int lastFileNumber = *--fileNumbers.cend();

	int newFileNumber = lastFileNumber + 1;

	return projectDataFileName + "_" + std::to_string(newFileNumber);
	}
	else
		return projectDataFileName + "_1";

}


void App::endGame()
{
	ph.mapNewString("ENDGAME", "GAME OVER");
	ph.mapNewString("ENDGAME",
		"PRESS Q TO QUIT OR P TO PLAY AGAIN");
	

}

std::string App::switchProjectDataFile()
{
	std::vector<string> fileList;
	std::vector<string> ProjectFileList;
	logNS::Logger::exploreFolder(logNS::Logger::STOREDDATADIR, fileList);
	static int i = 0;

	//metto in un vettore a parte i soli nomi dei file AppObj
	for (int i = 0; i < fileList.size(); i++)
		if (fileList[i].find(App::projectDataFileName) != string::npos)
			ProjectFileList.push_back(fileList[i]);

	if (i < ProjectFileList.size()-1)
		i++;
	else
		i = 0;
	return ProjectFileList[i];

}


void App::render(double currentTime)
{

  GLfloat black[] = {0.2,0.2,0.2,1.0};
  GLfloat one = 1.0f;
  glClearBufferfv(GL_COLOR,0,black);
  glClearBufferfv(GL_DEPTH,0,&one);

  glViewport(0,0,Application::window_width,Application::window_height);

  

  for (int i = 0; i < objectManager.ApplicationCollectorList.size(); i++)
	  objectManager.ApplicationCollectorList[i]->OCrender();

  /*Il testo va renderizzato necessariamente 
  dopo tutto il resto altrimenti vedi i frame dei caratteri*/
  textRenderer.render(fpcameraNS::CameraManager::getActiveCamera());
  
}


void App::update(){
	
	fpcameraNS::CameraManager::update();
	userInterface.update();

	if (!UserInterface::paused)
	{
		TimingData::update();
		globalNS::DURATION = 0.1;// TimingData::get().lastFrameDuration * 0.005f;
		if (globalNS::DURATION <= 0.0f) return;

		

		for (int i = 0; i < objectManager.ApplicationCollectorList.size(); i++)
			objectManager.ApplicationCollectorList[i]->OCupdate(globalNS::DURATION);

		myphysicsNS::CollisorePolimorfo::update(globalNS::DURATION);

		soundNS::soundMap::update();
		soundNS::soundMap::collisionSound(polyCollisor.contacts, polyCollisor.frameContactCounter);

		aiNS::AI::updateHealt(polyCollisor.contacts, polyCollisor.frameContactCounter);
	}
}


void App::generateContacts(){	

}





void App::startup()
{
	TimingData::init();

	loadProjectData(App::projectDataFileName);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);



	soundEngine.startSounds();
	//controls.setup(this);
	userInterface.init();
	textRenderer.create();

	for (int i = 0; i < objectManager.ApplicationCollectorList.size(); i++)
		objectManager.ApplicationCollectorList[i]->OCcreateObject();
    
	for (int i = 0; i < objectManager.ApplicationCollectorList.size(); i++)
		objectManager.ApplicationCollectorList[i]->OCsetParameters();
	
}


void App::SaveProjectData(string filename) {

	std::string filepath{ logNS::Logger::STOREDDATADIR + filename };
	std::ofstream out(filepath);
	out.clear();
	out.close();	

	myobjectNS::ApplicationObjectManager::save(filename);
	fpcameraNS::CameraManager::save();
	

	
}

void App::loadProjectData(string filename) {
	
	myobjectNS::ApplicationObjectManager::loadData(filename);
	fpcameraNS::CameraManager::load();
	

}


// resetta l'intera applicazione in modo da poter caricare un nuovo file
void App::reset()
{
	
	//fpcameraNS::CameraManager::resetAll();
}



//resetta gli oggetti
void App::resetAll() {

	for (int i = 0; i < objectManager.ApplicationCollectorList.size(); i++)
		objectManager.ApplicationCollectorList[i]->OCreset();
	
	
}