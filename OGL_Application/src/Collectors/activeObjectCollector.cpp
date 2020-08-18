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
		filename += "ActiveObject";
		static ofstream out(filename);

		//IDENTIFICO IL COLLETTORE
		out << saveloadNS::ActiveObjectLoader::COLLECTORTAG << std::endl;
		out << getCollectorName() << std::endl;
		out << saveloadNS::ActiveObjectLoader::COLLECTORISONTAG << std::endl;
		out << isOn << std::endl;
		out << saveloadNS::ActiveObjectLoader::ACTIVITYGROUNDID << std::endl;
		if (getActivityGround() != NULL)
			out << getActivityGround()->collectorID << std::endl;
		else
			out << std::endl;
		for (int i = 0; i < Pcontainer->size(); i++)
			getSubObject(i)->save(out);
		out << saveloadNS::ActiveObjectLoader::COLLECTORENDTAG << std::endl;

	}


}