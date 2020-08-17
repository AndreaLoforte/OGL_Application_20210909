#include<applicationDerivedObject.h>
#include<physics.h>
#include<applicationObjectManager.h>
#include<string>
#include<collectorLoader.h>

namespace myobjectNS {



  unsigned ObjectAABB::instanceCounter = 0;
  


	std::string ObjectAABB::showParameters() {

		std::string editableObjInfos = "infos not available : must define getEditableObject() for a collector";

		return editableObjInfos;
	}



	void ObjectAABB::setParameters() {

	}

	
	

	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	//CONSTRUCTORS

	
	ObjectAABB::ObjectAABB(const std::string& s, const float& l1, const float& l2, const float& l3) :
		L1(l1),
		L2(l2),
		L3(l3),
		ApplicationObject(s), 
		CollisionAABB(s,l1,l2,l3)
	{
		AOobjectClass = myobjectNS::classBox;
		halfSize = Vector3(L1 / 2, L2 / 2, L3 / 2);
		instanceNumber = instanceCounter++;
		AOinstanceID = s + "_" + std::to_string(instanceNumber);
		//body->RBobjectID = AOobjectName;
	}


	ObjectAABB::ObjectAABB(ObjectBox* p, const float& l1, const float& l2, const float& l3) :
		ApplicationObject(p->AOobjectName), CollisionAABB(p->AOobjectName,l1,l2,l3)
	{
		AOCollisorID = p->AOCollisorID;
		AOinstanceNumber = p->AOinstanceNumber;
		AOinstanceID = p->AOinstanceID;
		AOobjectClass = p->AOobjectClass;
		AOobjectName = p->AOobjectName;
		AOTrMatrix = p->AOTrMatrix;

		//body->RBobjectID = AOobjectName;


	}


	//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
////////////////////////GET NEW INSTANCE

	ObjectAABB* ObjectAABB::getNewInstance()
	{
		/*creo un altro oggetto uguale a questo*/
		ObjectAABB*obj(new ObjectAABB(AOobjectName, L1, L2, L2));
		return obj;
	}

	


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////SAVE



	void ObjectAABB::specializedSave(std::ofstream& out)
	{
		out << saveloadNS::CollectorLoader::DOSIZETAG << std::endl;
		out << L1 << " " << L2 << " " << L3 << std::endl;
	}



	//////////////////////////////////////////////////////77
	////////////////////GET RIGID BODY

#include<body.h>

	

	RigidBody* ObjectAABB::getRB()
	{
		return body;
	}

}