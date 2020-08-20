#include<activeobjectCollector.h>
#include<applicationDerivedObject.h>
#include<ground.h>
#include<activeobjectloader.h>

namespace collectorNS {



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


}