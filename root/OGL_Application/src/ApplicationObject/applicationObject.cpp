#include <applicationObject.h>
#include<vmath.h>
#include<text.h>
#include<fstream>
#include<app.h>
#include<vmath.h>
#include<physics.h>
#include<objectCollector.h>
#include<applicationObjectManager.h>
#include<saveloadhelper.h>
#include<body.h>
#include<cameraManager.h>

namespace myobjectNS
{



static const std::string TAG_APPLICATIONOBJECT{ "AppObj" };



void ApplicationObject::save(std::ofstream& out) {

	out << saveloadNS::CollectorSavings::OBJECTNAMETAG << std::endl;
	out << AOobjectName << std::endl;
	out << saveloadNS::CollectorSavings::AOINSTANCENUMBERTAG << std::endl;
	out << AOinstanceNumber << std::endl;
	out << saveloadNS::CollectorSavings::AOTRMATRIXTAG << std::endl;
	logNS::Logger::saveMatrix44(out, AOTrMatrix);
	out << std::endl;
	out << saveloadNS::CollectorSavings::AOPOSITIONTAG << std::endl;
	out << AOposition[0] << " " << AOposition[1] << " " << AOposition[2] << std::endl;
	out << saveloadNS::CollectorSavings::AOORIENTATIONTAG << std::endl;
	out << AOorientation[0] << " " << AOorientation[1] << " " << AOorientation[2] <<" "<< AOorientation[3]<< std::endl;
	out << saveloadNS::CollectorSavings::AOCOLORTAG << std::endl;
	out << AOcolor[0] << " " << AOcolor[1] << " " << AOcolor[2] << " " << AOcolor[3] << std::endl;
	out << saveloadNS::CollectorSavings::AOISONFLAGTAG << std::endl;
	out << AOisOn << std::endl;
	specializedSave(out);
}



ApplicationObject* ApplicationObject::load(std::ifstream& in, std::size_t start_from, std::size_t stop_at) {
	
	std::string  collType, collName, collNumber, flushTag;
	

	//prendo i primi due parametri utili ad ident
	in >> flushTag;
	in >> collType;
	in >> flushTag;
	in >> collName;
	in >> flushTag;
	in >> collNumber;
	
	ApplicationObject*newObj = AssetNS::Assets::getNewObject(collName);

	in >> flushTag;
	logNS::Logger::loadMatrix44(in, newObj->AOTrMatrix, in.tellg(), stop_at);

	in >> flushTag;
	in >> newObj->AOposition[0];
	in >> newObj->AOposition[1];
	in >> newObj->AOposition[2];

	in >> flushTag;

	in >> newObj->AOorientation[0];
	in >> newObj->AOorientation[1];
	in >> newObj->AOorientation[2];

	return newObj;
}



ApplicationObject* ApplicationObject::getNewInstance()
{
	ApplicationObject*obj(new ApplicationObject());
		return obj;
}

std::string ApplicationObject::AOgetInstanceID()
{
	AOinstanceID = AOobjectName + "_" + std::to_string(AOinstanceNumber);
	return AOinstanceID;
}





std::string ApplicationObject::AOprintInfos() {
	return this->showParameters();

}





void ApplicationObject::AOtrX(int sign) {
	/*sempre specificare f per float!*/
	AOposition[0] += sign * AOshift[0];
	setParameters();
}
void ApplicationObject::AOtrY(int sign) { 
	/*sempre specificare f per float!*/

	AOposition[1] += sign * AOshift[0];
	setParameters();
}
void ApplicationObject::AOtrZ(int sign) { 
	AOposition[2] += sign * AOshift[0];
	setParameters();
}
void ApplicationObject::AOrotX(int sign) { 
	/*sempre specificare f per float!*/
	mymathlibNS::Quaternion newRot(mymathlibNS::Quaternion::getQuaternionfromXAngle(sign * AOrot[0]));
	AOorientation = mymathlibNS::Quaternion::getProduct(AOorientation, newRot);
	
	setParameters();
	
}
void ApplicationObject::AOrotY(int sign) { 
	//AOorientation[1] += sign * AOrot[0];
	mymathlibNS::Quaternion newRot(mymathlibNS::Quaternion::getQuaternionfromYAngle(sign * AOrot[0]));
	AOorientation = mymathlibNS::Quaternion::getProduct(AOorientation, newRot);

	setParameters();
	
}
void ApplicationObject::AOrotZ(int sign) { 
	//AOorientation[2] += sign * AOrot[0];
	mymathlibNS::Quaternion newRot(mymathlibNS::Quaternion::getQuaternionfromZAngle(sign * AOrot[0]));
	AOorientation = mymathlibNS::Quaternion::getProduct(AOorientation, newRot);
	setParameters();
}



ApplicationObject::ApplicationObject(std::string objName) :AOobjectName(objName)
{
}

void ApplicationObject::AOrender() 
{ this->render(fpcameraNS::CameraManager::getActiveCamera()); }

ApplicationObject::ApplicationObject(ApplicationObject* p) 
{
	AOCollisorID = p->AOCollisorID;
	AOinstanceNumber = p->AOinstanceNumber;
	AOinstanceID = p->AOinstanceID;
	AOobjectClass = p->AOobjectClass;
	AOobjectName = p->AOobjectName;
	AOTrMatrix = p->AOTrMatrix;


}





RigidBody* ApplicationObject::getRB()
{
	return nullptr;
}










} // namespace myobjectNS
