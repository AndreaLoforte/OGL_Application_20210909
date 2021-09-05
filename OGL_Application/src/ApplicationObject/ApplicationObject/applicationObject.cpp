#include <applicationObject.h>
#include<vmath.h>
#include<fstream>
#include<app.h>
#include<vmath.h>
#include<physics.h>
#include<objectCollector.h>
#include<applicationObjectManager.h>
//#include<saveloadhelper.h>
#include<body.h>
#include<cameraManager.h>
#include<userInterface.h>
#include<collectorLoader.h>
namespace myobjectNS
{



static const std::string TAG_APPLICATIONOBJECT{ "AppObj" };



void ApplicationObject::save(std::ofstream& out) {

	out << saveloadNS::CollectorLoader::OBJECTNAMETAG << std::endl;
	out << AOobjectName << std::endl;
	out << saveloadNS::CollectorLoader::AOINSTANCENUMBERTAG << std::endl;
	out << AOinstanceNumber << std::endl;
	/*out << saveloadNS::CollectorSavings::AOTRMATRIXTAG << std::endl;
	logNS::Logger::saveMatrix44(out, AOTrMatrix);
	out << std::endl;*/
	out << saveloadNS::CollectorLoader::AOSCALE << std::endl;
	out << AOscale << std::endl;
	out << saveloadNS::CollectorLoader::AOPOSITIONTAG << std::endl;
	out << AOposition[0] << " " << AOposition[1] << " " << AOposition[2] << std::endl;
	out << saveloadNS::CollectorLoader::AOORIENTATIONTAG << std::endl;
	out << AOorientation[0] << " " << AOorientation[1] << " " << AOorientation[2] <<" "<< AOorientation[3]<< std::endl;
	out << saveloadNS::CollectorLoader::AOCOLORTAG << std::endl;
	out << AOcolor[0] << " " << AOcolor[1] << " " << AOcolor[2] << " " << AOcolor[3] << std::endl;
	out << saveloadNS::CollectorLoader::AOISONFLAGTAG << std::endl;
	out << AOisOn << std::endl;
	specializedSave(out);
}


void ApplicationObject::setColor(const vmath::vec4& col)
{
	AOcolor[0] = col[0];
	AOcolor[1] = col[1];
	AOcolor[2] = col[2];
	AOcolor[3] = col[3];

}


void ApplicationObject::changeColor(const std::vector<float>& col)
{
	AOcolor[0] = col[0];
	AOcolor[1] = col[1];
	AOcolor[2] = col[2];
	AOcolor[3] = col[3];
}

void ApplicationObject::setSize(const std::vector<float>& sz)
{
	AOsize = sz;
}



void ApplicationObject::AOcanSleep(const bool v)
{
	AOisOn = !v;
	DOcanSleep(v);
}

void ApplicationObject::setCollectorOwnership(const std::string s)
{
	AOcollectorOwnershipID = s;
}

void ApplicationObject::scaleDimension(const float& s)
{
	AOscale = s;
	for (int i = 0; i < AOsize.size(); i++)
		AOsize[i] = AOsize[i] * AOscale;
	create();
	//vmath::mat4 scalingMat = vmath::mat4{ 
	//	vmath::vec4(s,0.0,0.0,0.0),
	//	vmath::vec4(0.0,s,0.0,0.0),
	//	vmath::vec4(0.0,0.0,s,0.0),
	//	vmath::vec4(0.0,0.0,0.0,1) };
	////AOTrMatrix = mymathlibNS::vmatMatrix::getProduct(scalingVector, AOTrMatrix);
	//AOTrMatrix = vmath::matrixCompMult(AOTrMatrix, scalingMat);
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



void ApplicationObject::AOtr(const int& shiftX, const int& shiftY, const int& shiftZ)
{
	constexpr float shift = .1;
	AOposition[0] += shiftX * shift;
	AOposition[1] += shiftY * shift;
	AOposition[2] += shiftZ * shift;
	setParameters();
}


void ApplicationObject::AOupdate(const float& duration)
{
	this->update(duration);
	if (UserInterface::physicsOn)
		this->updatePhysics(duration);
}


void ApplicationObject::setPosition(std::array<float, 3> pos)
{
	AOposition = pos;
	setParameters();
}

void ApplicationObject::setPosition(const GLfloat arr[3])
{
	AOposition[0] = arr[0];
	AOposition[1] = arr[1]; 
	AOposition[2] = arr[2]; 
	setParameters();
}

void ApplicationObject::setParameters()
{
	Matrix4 tempMat;
	Vector3 tempPosVec{ AOposition[0],AOposition[1],AOposition[2] };
	
	mymathlibNS::calculateTransformMatrix(tempMat, tempPosVec, AOorientation);
	mymathlibNS::getGLTransform(tempMat, AOTrMatrix);
}



void ApplicationObject::setRotation(const std::array<float, 3>& r)
{
	AOrot = r;
	
	mymathlibNS::Quaternion qx(mymathlibNS::Quaternion::getQuaternionfromZAngle(AOrot[0]));
	mymathlibNS::Quaternion qy(mymathlibNS::Quaternion::getQuaternionfromZAngle(AOrot[1]));
	mymathlibNS::Quaternion qz(mymathlibNS::Quaternion::getQuaternionfromZAngle(AOrot[2]));


	AOorientation = mymathlibNS::Quaternion::getProduct(qx, qz);
	AOorientation = mymathlibNS::Quaternion::getProduct(qy, AOorientation);
	setParameters();
}


void ApplicationObject::AOtrX(int sign) {
	AOposition[0] += sign * deltaShift;
	setParameters();
}
void ApplicationObject::AOtrY(int sign) { 
	AOposition[1] += sign * deltaShift;
	setParameters();
}
void ApplicationObject::AOtrZ(int sign) { 
	AOposition[2] += sign * deltaShift;
	setParameters();
}
void ApplicationObject::AOrotX(int sign) { 
	AOrot[0] += sign * deltaRot;
	mymathlibNS::Quaternion newRot(mymathlibNS::Quaternion::getQuaternionfromXAngle(sign * deltaRot));
	AOorientation = mymathlibNS::Quaternion::getProduct(AOorientation, newRot);
	
	setParameters();
	
}
void ApplicationObject::AOrotY(int sign) { 
	AOrot[1] += sign * deltaRot;
	mymathlibNS::Quaternion newRot(mymathlibNS::Quaternion::getQuaternionfromYAngle(sign * deltaRot));
	AOorientation = mymathlibNS::Quaternion::getProduct(AOorientation, newRot);

	setParameters();
	
}
void ApplicationObject::AOrotZ(int sign) { 
	AOrot[2] += sign * deltaRot;
	mymathlibNS::Quaternion newRot(mymathlibNS::Quaternion::getQuaternionfromZAngle(sign * deltaRot));
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
