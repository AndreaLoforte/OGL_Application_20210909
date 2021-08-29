#include<gun.h>
#include<playerCharacter.h>
#include<cameraManager.h>
#include<collectorLoader.h>
#include<app.h>
namespace myobjectNS{

	
	const string shoot_audiofilename = "myshotsound.wav";
	const string shoot_audiofile_fullpath = App::audio_dir + shoot_audiofilename;
	const char* shoot_audiofile_fullpath_c_str = shoot_audiofile_fullpath.c_str();

void Gun::create() {

	invokeSetShaders();
	invokeSetRigidBodyParameters(fpcameraNS::CameraManager::getActiveCameraPT());
}


void Gun::shotAt(const std::array<float,3>& enemypos,const std::array<float,3>& targetPos) {
	
	
}


/*funzione che permette di sparare dato un firespot
e una direzione di fuoco*/
void Gun::shootTowards(const std::array<float,3>& pos,const std::array<float,3>& dir) {


}


void Gun::OCsetParameters() {}

void Gun::OCrender()
{ render(fpcameraNS::CameraManager::getActiveCamera()); }

void Gun::OCcreateObject() {
	//alla creazione deve essere creato solo il mirino e non il proiettile che viene invece creato quando sparo
	/*create();
	ApplicationObjectCollector::collector[0]->setParameters();*/


}


void Gun::render(const fpcameraNS::Transformation& cam) {
	
	/*al momento gun body non ha body */
	/*	for (int i = 0; i < collector.size(); i++)
			collector[i]->render(cam);*/
}



void Gun::update(const float& duration){
}

void Gun::invokeSetTextures(){}

void Gun::invokeSetShaders(){
	create();
}


void Gun::invokeSetPosition() {}



void Gun::invokeSetRigidBodyParameters(const fpcameraNS::Transformation* cam){
	OCsetParameters();
}


/////////////////////////////////////////////////////////7
////////////////////OC GUN
////////////////////OC GUN
////////////////////OC GUN
////////////////////OC GUN


void OCGun::create() {

	gun.invokeSetShaders();
	gun.invokeSetRigidBodyParameters(fpcameraNS::CameraManager::getActiveCameraPT());

	///stesso per projectile e viewfineder
}


void OCGun::shootAt(const std::array<float, 3>& enemypos, const std::array<float, 3>& targetPos) {
	typedef soundNS::soundMap sound;

	std::array<float, 3> distance 
	{ targetPos.at(0) - enemypos.at(0),
	targetPos.at(1) - enemypos.at(1),
	targetPos.at(2) - enemypos.at(2) };

	Projectile *prj(new Projectile{ "projectile", enemypos });
	OCinsertObject(prj);
	prj->setVelModule(velmodule);
	/*passo a projectile l'ownership di Gun (eg se gun è di Enemy => projectile è di enemy..*/
	prj->setCollectorOwnership(collectorOwnership);
	prj->shoot(enemypos,mymathlibNS::Vector::normalize(distance));


	/*imposto lo sparo sempre a volume massimo.*/
	sound::engine->setDefault3DSoundMinDistance(50.0f);
	//myobjectNS::PrintHelper::mapNewString("ENEMYPOS", "Enemy pos :" + logNS::Logger::stdarray3ToString(distance));
	
	soundNS::soundMap::engine->play3D
	(shoot_audiofile_fullpath_c_str, soundNS::toIrrklang::stdfarray(enemypos));
	
}





/*funzione che permette di sparare dato un firespot
e una direzione di fuoco*/
void OCGun::shootTowards(const std::array<float, 3>& pos, const std::array<float, 3>& dir) {

	Projectile *prj(new Projectile{ "projectile", pos });
	OCinsertObject(prj);
	prj->setVelModule(velmodule);
	prj->setCollectorOwnership(collectorOwnership);
	prj->shoot(pos, dir);

	/*imposto lo sparo sempre a volume massimo.*/
	irrklang::vec3df playerpos = soundNS::toIrrklang::stdfarray(pos);
	soundNS::soundMap::engine->setSoundVolume(1);

	soundNS::soundMap::engine->play2D(shoot_audiofile_fullpath_c_str);


}



void OCGun::OCsave(std::string& filename) {


	static ofstream out(filename);

	out << saveloadNS::CollectorLoader::COLLECTORTAG << std::endl;
	out << getCollectorName() << std::endl;
	for (int i = 0; i < Pcontainer->size(); i++)
	{
		if (Pcontainer->at(i)->AOobjectName == "projectile");
		if (Pcontainer->at(i)->AOobjectName == "viewfinder")
			Pcontainer->at(i)->save(out);
	}
	out << saveloadNS::CollectorLoader::COLLECTORENDTAG << std::endl;

}


void OCGun::OCsetParameters() {
	//vw.setParameters();

}


void OCGun::OCcreateObject() {
	//alla creazione deve essere creato solo il mirino e non il proiettile che viene invece creato quando sparo
	//vw.create(
}

void OCGun::OCrender()  { render(fpcameraNS::CameraManager::getActiveCamera()); }

void OCGun::render(const fpcameraNS::Transformation& cam) {


	for (int i = 0; i < Pcontainer->size(); i++)
		Pcontainer->at(i)->render(cam);
}



void OCGun::invokeSetRigidBodyParameters(const fpcameraNS::Transformation* cam) {
	OCsetParameters();
}


void OCGun::OCinsertObject(myobjectNS::ApplicationObject* obj) 
{
	/*verifico quale container sto utilizzando*/
	if (externalContainer)
	{
		if (projcounter >= MAXNUMEXISTINGPROJ)
		{
			for (int i = 0; i < Pcontainer->size(); i++)
				if (Pcontainer->at(i)->AOobjectName == "projectile")
				{
					deleteAtPos(i);
					i = Pcontainer->size();
				}
		}
		Pcontainer->push_back(obj);
		Pcontainer->back()->AOcreateObject();
		Pcontainer->back()->setParameters();
		projcounter++;
	}
	else
	{
		/*aggiungere utilizzo ownContainer*/
	}
}


}//weaponNS