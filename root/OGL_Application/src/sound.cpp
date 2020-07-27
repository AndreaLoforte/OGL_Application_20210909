#include<sound.h>
#include<conio.h>
#include<contacts.h>
#include<text.h>
#include<physics.h>
#include<playerCharacter.h>
#include<applicationDerivedObject.h>
#include<cameraManager.h>
#include<userInterface.h>
namespace soundNS {

#pragma comment(lib, "irrKlang.lib")

	static const string projectile_plane_coll_sound_filename = "myshotsound.wav";
	static const string rumRogers_soundtrack_filename = "RumRogersCottage_edited.ogg";

	map<CollisionPair, string> soundMap::collisionSoundMap;
	textRendererNS::PrintHelper soundMap::ph{ "soundMap",-0.9f,-0.5f };


	irrklang::ISoundEngine* soundMap::engine = irrklang::createIrrKlangDevice();

	static constexpr unsigned scaleDistanceFactor = 1;

	soundMap::soundMap()
	{
		if (!engine)
		{
			logNS::Logger::writeLog("Could not startup engine");
			return;
		}
		collisionSoundMap.emplace(CollisionPair("Surface", "projectile"), SOUNDSDIR+ projectile_plane_coll_sound_filename);
		collisionSoundMap.emplace(CollisionPair("projectile", "Surface"), SOUNDSDIR+ projectile_plane_coll_sound_filename);

		irrklang::ISoundEngine *dev = irrklang::createIrrKlangDevice(irrklang::ESOD_WIN_MM);
		

	

	}



	void soundMap::startSounds()
	{
		update();

		string filename_ = SOUNDSDIR + rumRogers_soundtrack_filename;
		const char * filename = filename_.c_str();


		//irrklang::ISoundSource *source = engine->addSoundSourceFromFile(filename);

		/*in generale pare non sia garantito che engine->play ritorni il puntatore al suono !
		Inoltre irrklang fa già il caching del puntatore, quindi non farti problemi
		a richiamarlo ogni volta!*/
		static irrklang::ISoundSource* sound = engine->getSoundSource(filename);//, { 0.0,0.0,0.0 }, true, true, true);
		//static irrklang::ISound sound_ = 
		
		static bool play = false;
		if (play)
		{
			
			//engine->play2D(sound);
			engine->play3D(sound, { 0.0,0.0,0.0 },false,true);
			engine->setDefault3DSoundMinDistance(50.0f);
			//sound->setVolume(0.7);
			
			
			play = false;
		}
		else
		{
			engine->play3D(sound, { 0.0,0.0,0.0 }, true, true);
			engine->setDefault3DSoundMinDistance(50.0f);
			play = true;
		}
			

	}

	void soundMap::collisionSound(const Contact* contactArray, const unsigned& contactCounter)
	{
		for (int i = 0; i < myphysicsNS::CollisorePolimorfo::frameContactCounter;  i++)
		{
			Contact contact = contactArray[i];

			static constexpr float epsilon = 40.0;
			float deltaVelocity = contact.getDeltaVelocity();
			float squared_deltaVel = deltaVelocity * deltaVelocity;

			/*se una sfera è ferma sul piano non abbiamo suono di collisione*/
			if (squared_deltaVel > epsilon )
			{

				map<CollisionPair, string>::iterator iterator_to_collisionSound =
					collisionSoundMap.find(CollisionPair{ contact.body[0]->RBobjectName, contact.body[1]->RBobjectName });
				if (iterator_to_collisionSound != collisionSoundMap.end())
				{

					string collisionSoundFileName = iterator_to_collisionSound->second;

					const char *filename = collisionSoundFileName.c_str();

					/*in base all'ampiezza dell'ambienta rispetto al volume di default,
					scaliamo la posizione inviata al motore audio altrimenti i suoni risultano troppo
					lontani per essere sentiti*/
					float pos[3];
					pos[0] = contact.contactPoint[0];// scaleDistanceFactor;
					pos[1] = contact.contactPoint[1];// scaleDistanceFactor;
					pos[2] = contact.contactPoint[2];// scaleDistanceFactor;
					irrklang::vec3df contactPosition(pos[0], pos[1], pos[2]);

					static irrklang::ISoundSource  * shot_source = engine->addSoundSourceFromFile(projectile_plane_coll_sound_filename.c_str());
					irrklang::ISound *shot_sound = engine->play3D(filename, contactPosition,false, true,true);
					float collisionSoundMagnitude = squared_deltaVel / 2000;
					ph.mapNewString("SOUND", logNS::Logger::floatArr3ToString(pos));
					
					/*se non si chiama setIsPaused il puntatore non viene inizializzato???*/
					shot_sound->setVolume(collisionSoundMagnitude);
					//shot_source->setDefaultVolume(0);
					shot_sound->setIsPaused(false);
					
					
					/*la funzione play va sempre richiamata !*/
					//engine->play3D(filename, contactPosition);
					


				}
				else
				{
					ph.mapButtonOnBranch( uiNS::UserInterface::getParentButton()->getButtonID() ,
						"SOUNDWARNING", "some collision sound file has not been found");
				}
			}
		}
	}



	void soundMap::update()
	{
		static myobjectNS::PlayerCharacter* pc;
		std::array<float, 3> arr = pc->getPosition();
		irrklang::vec3df GLBcoords = soundNS::toIrrklang::stdfarray(arr);
		GLBcoords.X = GLBcoords.X / scaleDistanceFactor;
		GLBcoords.Y = GLBcoords.Y / scaleDistanceFactor;
		GLBcoords.Z = GLBcoords.Z / scaleDistanceFactor;
		

		const irrklang::vec3df lookat = toIrrklang::farray(fpcameraNS::CameraManager::getActiveCamera().lookat);

		//textRendererNS::PrintHelper::mapNewString("LISTENERPOS", "Listener Pos : " + logNS::Logger::stdarray3ToString(arr));
		engine->setListenerPosition(GLBcoords, lookat);



		
	}
	

	





	void soundMap::collisionSound(const Contact& contact)
	{

		map<CollisionPair, string>::iterator iterator_to_collisionSound =
			collisionSoundMap.find(CollisionPair{ contact.body[0]->RBobjectName, contact.body[1]->RBobjectName });
		if (iterator_to_collisionSound != collisionSoundMap.end())
		{

			string collisionSoundFileName = iterator_to_collisionSound->second;
			//collisionSoundMap.find(CollisionPair{ contact.body[0]->RBobjectID, contact.body[1]->RBobjectID });

			const char *c = collisionSoundFileName.c_str();


			float pos[3];
			pos[0] = contact.contactPoint[0];
			pos[1] = contact.contactPoint[1];
			pos[2] = contact.contactPoint[2];
			irrklang::vec3df contactPosition(pos[0], pos[1], pos[2]);
			engine->play3D(c, contactPosition);

		}
		else
		{
			logNS::Logger::writeLog("did not found sound file for collision");
		}
	}



	irrklang::vec3df soundMap::convertIntoIrrklang(const std::array<float, 3>& vec)
	{
		irrklang::vec3df result(vec[0], vec[1], vec[2]);
		return result;
	}


}