//#include<fstream>
//#include<string>
#include<activeobjectloader.h>
#include<activeObjectCollector.h>
#include<applicationObject.h>
#include<ground.h>

using namespace std;
namespace saveloadNS {

	ofstream ActiveObjectSaver::out;

	void ActiveObjectSaver::save(collectorNS::ActiveObjectCollector* coll, std::string& projectName)
	{

		saveloadNS::dataSaver::ofstreamList.insert(&out);
		if (!out.is_open())
		{
			out.open(logNS::Logger::PROJECTDIR + saveloadNS::ACTIVEOBJECTSAVINGFILE);
		}
			
		
		//IDENTIFICO IL COLLETTORE
		out << saveloadNS::ActiveObjectLoader::COLLECTORTAG << std::endl;
		out << coll->getCollectorName() << std::endl;
		out << saveloadNS::ActiveObjectLoader::COLLECTORNUMBER << std::endl;
		out << coll->collectorNumber << std::endl;
		out << saveloadNS::ActiveObjectLoader::COLLECTORISONTAG << std::endl;
		out << coll->isOn << std::endl;
		out << saveloadNS::ActiveObjectLoader::ACTIVITYGROUNDID << std::endl;
		if (coll->getActivityGround() != NULL)
			out << coll->getActivityGround()->collectorID << std::endl;
		else
			out << std::endl;
		for (int i = 0; i < coll->Pcontainer->size(); i++)
			coll->getSubObject(i)->save(out);
		out << saveloadNS::ActiveObjectLoader::COLLECTORENDTAG << std::endl;

	}


}