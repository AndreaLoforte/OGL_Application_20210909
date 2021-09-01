#include<activeobjectCollector.h>
#include<applicationDerivedObject.h>
#include<ground.h>
#include<activeobjectloader.h>
#include<activeObjectManager.h>
namespace collectorNS {


	

	ActiveObjectCollector::~ActiveObjectCollector()
	{
		activeObjectManagerNS::ActiveObjectManager::del(this);
	}



	const bool& ActiveObjectCollector::damage(const int& i)
	{

		healt -= i;
		if (healt > 0)
			isAlive = true;
		else
			isAlive = false;
		return isAlive;
	}
	

	void ActiveObjectCollector::OCsave(std::string& filename)
	{
		saveloadNS::ActiveObjectSaver::save(this, filename);

	}

	
	ActiveObjectCollector* ActiveObjectCollector::OCloadActiveObject( const unsigned& collNumber)
	{
		return 0;
	}

}