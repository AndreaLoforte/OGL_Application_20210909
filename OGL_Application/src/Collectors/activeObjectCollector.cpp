#include<activeobjectCollector.h>
#include<applicationDerivedObject.h>
#include<ground.h>
#include<activeobjectloader.h>
#include<activeObjectManager.h>
namespace collectorNS {


	

	ActiveObject::~ActiveObject()
	{
		activeObjectManagerNS::ActiveObjectManager::del(this);
	}



	const bool& ActiveObject::damage(const int& i)
	{

		healt -= i;
		if (healt > 0)
			isAlive = true;
		else
			isAlive = false;
		return isAlive;
	}
	

	void ActiveObject::OCsave(std::string& filename)
	{
		saveloadNS::ActiveObjectSaver::save(this, filename);

	}

	
	ActiveObject* ActiveObject::OCloadActiveObject( const unsigned& collNumber)
	{
		return 0;
	}

}