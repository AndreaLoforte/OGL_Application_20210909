#include<activeobjectCollector.h>
#include<applicationDerivedObject.h>
#include<ground.h>
#include<collectorLoader.h>
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
	
	void ActiveObject::OCsave(std::ofstream& out)
	{
		//IDENTIFICO IL COLLETTORE
		out << saveloadNS::CollectorLoader::COLLECTORTAG << std::endl;
		out << getCollectorName() << std::endl;
		out << saveloadNS::CollectorLoader::COLLECTORISONTAG << std::endl;
		out << isOn << std::endl;
		out << saveloadNS::CollectorLoader::ACTIVITYGROUNDID << std::endl;
		out << getActivityGround()->p->getRB()->RBobjectID << std::endl;
		for (int i = 0; i < Pcontainer->size(); i++)
			getSubObject(i)->save(out);
		out << saveloadNS::CollectorLoader::COLLECTORENDTAG << std::endl;

	}


}