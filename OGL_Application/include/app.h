#ifndef APP_H
#define APP_H
#include<application.h>
#include<cameraManager.h>
#include<applicationObjectManager.h>
#include<applicationObject.h>
#include<sb7ktx.h>	
#include<random>
#include<inputs.h>
#include<textRenderer.h>
#include<physics.h>
#include<extern_definitions.h>
#include<sound.h>
#include<timing.h>
#include<AI.h>
#include<userInterface.h>



	class App : public Application {
		
		friend class InputsNS::Controls;
		/*Istanziare le classi sotto garantisce una corretta inizializzazione senza la quale
		sarebbe necessario chiamare delle funzioni di setup su App::startup. Questa soluzione è più pulita!*/
		myobjectNS::ApplicationObjectManager objectManager;
		fpcameraNS::CameraManager cameraManager;
		myphysicsNS::CollisorePolimorfo polyCollisor;
		soundNS::soundMap soundEngine;
		aiNS::AI ai;
	protected:
		
		InputsNS::Controls controls;		
		uiNS::UserInterface userInterface{&controls };
		void generateContacts();
		
		
		
	public:
		App() {}
		~App() {}

		textRendererNS::TextRenderer textRenderer{ "text" };
		static printHelperNS::PrintHelper ph;
	

		void render(double);
		void startup();

		void switchPhysics();
		void resetAll();
		void update();
		static void reset();
		void endGame();
		static void SaveProjectData(string);//static perchè richiamata da controls che non ha istanze di app.

		static std::string projectDataFileName;
		static bool loadProjectData(string s = "default");
		logNS::Logger log;

		static string defaultProjectFileName;
		static string audio_dir;
	};






#endif
