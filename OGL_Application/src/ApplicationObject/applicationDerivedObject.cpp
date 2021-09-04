#include<applicationDerivedObject.h>
#include<physics.h>
#include<applicationObjectManager.h>
//#include<applicationObject.h>
#include<string>
#include<objectCollector.h>
#include<collectorLoader.h>
namespace myobjectNS {


  
  void ObjectBox::editBoxSize(const GLfloat& width, const GLfloat& heigth, const GLfloat& depth) {}

  unsigned ObjectPlane::instanceCounter = 0;
  unsigned ObjectSphere::instanceCounter = 0;
  unsigned ObjectBox::instanceCounter = 0;
  


	std::string  ObjectPlane::showParameters() 
	{

		std::string editableObjInfos= "must define getEditableObject()->AOTrMatrix in case of collectors";
		return editableObjInfos;
	}


	/*############################## SET SIZE, CHANGE DIMENSION ############################*/
	void ObjectAABB::changeDimensions(const GLfloat& w, const GLfloat& h, const GLfloat& d)
	{
		L1 = w;
		L2 = h;
		L3 = d;
		create();
	}
	void ObjectAABB::setSize(const std::vector<float>& sz)
	{
		changeDimensions(sz[0], sz[1], sz[2]);
	}

	


	void ObjectBox::setSize(const std::vector<float>& sz)
	{
		AOsize = sz;
		L1 = AOsize.at(0);
		L2 = AOsize.at(1);
		L3 = AOsize.at(2);
	}
	void ObjectBox::changeDimensions(const GLfloat& w, const GLfloat& h, const GLfloat& d)
	{
		L1 = w;
		L2 = h;
		L3 = d;
		halfSize[0] = L1 / 2;
		halfSize[1] = L2 / 2;
		halfSize[2] = L3 / 2;
		create();
	}


	void ObjectPlane::changeDimensions(const GLfloat& w, const GLfloat& h)
	{
		CollisionFinitePlane::size[0] = w;
		CollisionFinitePlane::size[1] = 0;
		CollisionFinitePlane::size[2] = h;

		ApplicationObject::setSize({ w,0,h });
		create();
	}

	/*chiamata da application manager in loading*/
	void ObjectPlane::setSize(const std::vector<float>& sz)
	{
		size[0] = sz[0];
		size[1] = sz[1];
		size[2] = sz[2];

		ApplicationObject::setSize(sz);
		/*AOsize.push_back(sz[0]);
		AOsize.push_back(sz[1]);
		AOsize.push_back(sz[2]);*/

	}


	void ObjectSphere::changeRadius(float Rad)
	{
		DOradius = Rad;
		radius = DOradius;
		create();
	}
	void ObjectSphere::setSize(const std::vector<float>& sz)
	{
		changeRadius(sz[0]);
	}

	/*#################### SCALE OBJECT ####################################à*/

	void ObjectSphere::scaleDimension(const float& s)
	{
		/*Matrix4 scaleMat = Matrix4();
		scaleMat.setDiagonal(s, s, s);
		body->transformMatrix = body->transformMatrix * scaleMat;*/
		radius = radius * s;
	}


	void ObjectBox::scaleDimension(const float& s)
	{
		Matrix4 scaleMat = Matrix4();
		scaleMat.setDiagonal(s, s, s);
		body->transformMatrix = body->transformMatrix * scaleMat;
	}

	void ObjectPlane::scaleDimension(const float& s)
	{
		Matrix4 scaleMat = Matrix4();
		scaleMat.setDiagonal(s, s, s);
		body->transformMatrix = body->transformMatrix * scaleMat;
	}

	void ObjectAABB::scaleDimension(const float& s)
	{
		Matrix4 scaleMat = Matrix4();
		scaleMat.setDiagonal(s, s, s);
		body->transformMatrix = body->transformMatrix * scaleMat;
	}


	/*#####################################*/

		

	std::string ObjectBox::showParameters() {

		std::string editableObjInfos = "infos not available : must define getEditableObject() for a collector";
		return editableObjInfos;
	}



	void ObjectBox::setParameters() {}

	
	std::string ObjectSphere::showParameters() {
		std::string editableObjInfos = "infos not available, must define getEditableObject()->AOTrMatrix for a collector";
		/*myobjectNS::TextRenderer::printMatrix44(editableObjInfos,
			myobjectNS::ApplicationObjectManager::getEditableObject()->AOTrMatrix,
			"^Transformation Matrix of " + AOobjectName);*/

		return editableObjInfos;
	}

	


	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	//CONSTRUCTORS

	/*constructor of a new plane*/
	ObjectPlane::ObjectPlane(const std::string& s,const size_t& L1, const size_t& L2, const size_t& L3) :
		ApplicationObject(s), CollisionFinitePlane(AOobjectName,L1,L2,L3)
	{
		AOobjectClass = myobjectNS::classPlane;
		AOinstanceNumber = instanceCounter++;
		AOCollisorID = 3;
		//AOinstanceID = s + "_" + std::to_string(instanceNumber);
	}

	/*constructor of a new plane with same data of an existing one*/
	ObjectPlane::ObjectPlane(ObjectPlane* p,const size_t& L1, const size_t& L2, const size_t& L3): 
		ApplicationObject(p->AOobjectName), CollisionFinitePlane(p->AOobjectName,L1,L2,L3)
	{
		AOCollisorID = p->AOCollisorID;
		AOinstanceNumber = p->AOinstanceNumber;
		AOinstanceID = p->AOinstanceID;
		AOobjectClass = p->AOobjectClass;
		AOobjectName = p->AOobjectName;
		AOTrMatrix = p->AOTrMatrix;

		//body->RBobjectID = AOobjectName;
	}



	ObjectBox::ObjectBox(const std::string& s, const float& l1, const float& l2, const float& l3) :
		L1(l1),
		L2(l2),
		L3(l3),
		ApplicationObject(s), 
		CollisionBox(s,l1,l2,l3)
	{
		AOobjectClass = myobjectNS::classBox;
		halfSize = Vector3(L1 / 2, L2 / 2, L3 / 2);
		instanceNumber = instanceCounter++;
		AOinstanceID = s + "_" + std::to_string(instanceNumber);
		//body->RBobjectID = AOobjectName;
	}


	ObjectBox::ObjectBox(ObjectBox* p, const float& l1, const float& l2, const float& l3) :
		ApplicationObject(p->AOobjectName), CollisionBox(p->AOobjectName,l1,l2,l3)
	{
		AOCollisorID = p->AOCollisorID;
		AOinstanceNumber = p->AOinstanceNumber;
		AOinstanceID = p->AOinstanceID;
		AOobjectClass = p->AOobjectClass;
		AOobjectName = p->AOobjectName;
		AOTrMatrix = p->AOTrMatrix;

		//body->RBobjectID = AOobjectName;


	}


	ObjectSphere::ObjectSphere(std::string s) :ApplicationObject(s), CollisionSphere(s)
	{
		AOobjectClass = myobjectNS::classSphere;
		DOradius = 5.0;
		radius = ObjectSphere::DOradius;
		instanceNumber = instanceCounter++;
		AOinstanceID = s + "_" + std::to_string(instanceNumber);
		//body->RBobjectID = AOobjectName;
	}


	ObjectSphere::ObjectSphere(ObjectSphere* p) :ApplicationObject(p->AOobjectName), CollisionSphere(p->AOobjectName)
	{
		AOCollisorID = p->AOCollisorID;
		AOinstanceNumber = p->AOinstanceNumber;
		AOinstanceID = p->AOinstanceID;
		AOobjectClass = p->AOobjectClass;
		AOobjectName = p->AOobjectName;
		AOTrMatrix = p->AOTrMatrix;
		DOradius = 5.0;
		radius = ObjectSphere::DOradius;

		//body->RBobjectID = AOobjectName;
	}




	//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
////////////////////////GET NEW INSTANCE

	ObjectPlane* ObjectPlane::getNewInstance()
	{
		/*creo un altro oggetto uguale a questo*/
		ObjectPlane*obj(new ObjectPlane(this->AOobjectName,size[0],size[1],size[2]));
		return obj;
	}




	ObjectBox* ObjectBox::getNewInstance()
	{
		/*creo un altro oggetto uguale a questo*/
		ObjectBox*obj(new ObjectBox(AOobjectName, L1,L2,L2));
		return obj;
	}



	ObjectSphere* ObjectSphere::getNewInstance()
	{
		ObjectSphere*obj(new ObjectSphere());
		return obj;
	}

	/*################# DO_CAN_SLEEP ###################################*/
	void ObjectSphere::DOcanSleep(const bool& v)
	{
		body->canSleep = v;
		body->isAwake = !v;
	}

	void ObjectBox::DOcanSleep(const bool& v)
	{
		body->canSleep = v;
		body->isAwake = !v;
	}

	void ObjectAABB::DOcanSleep(const bool& v)
	{
		body->canSleep = v;
		body->isAwake = !v;
	}

	void ObjectPlane::DOcanSleep(const bool& v)
	{
		body->canSleep = v;
		body->isAwake = !v;
	}

	/*################### UPDATE PHYSICS ################################*/

	void ObjectSphere::updatePhysics(const float& duration)
	{
		body->integrate(duration);
		calculateInternals();
	}


	void ObjectBox::updatePhysics(const float& duration) 
	{
		body->integrate(duration);
		calculateInternals();
	}


	void ObjectAABB::updatePhysics(const float& duration)
	{
		body->integrate(duration);
		calculateInternals();
	}


	void ObjectPlane::updatePhysics(const float& duration)
	{
		body->integrate(duration);
		calculateInternals();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////SAVE


	void ObjectSphere::specializedSave(std::ofstream& out)
	{
		out << saveloadNS::CollectorLoader::DOSIZETAG << std::endl;
		out << DOradius << std::endl;
	}
	void ObjectBox::specializedSave(std::ofstream& out) 
	{
		out << saveloadNS::CollectorLoader::DOSIZETAG << std::endl;
		out << L1 << " " << L2 << " " << L3 << std::endl;
	}
	void ObjectPlane::specializedSave(std::ofstream& out)
	{
		out << saveloadNS::CollectorLoader::DOSIZETAG << std::endl;
		out << size[0]<< " "<<size[1]<< " " << size[2] <<  std::endl;
	}




	//////////////////////////////////////////////////////77
	////////////////////GET RIGID BODY

#include<body.h>

	RigidBody* ObjectSphere::getRB()
	{
		return body;
	}

	RigidBody* ObjectPlane::getRB()
	{
		return body;
	}
	RigidBody* ObjectBox::getRB()
	{
		return body;
	}

	

}