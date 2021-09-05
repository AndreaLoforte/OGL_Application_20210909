#include<collectorloader.h>
#include<applicationObject.h>
#include<surface/groundsurface/ground.h>

using namespace std;
namespace saveloadNS {

	ofstream CollectorSaver::out;

	void CollectorSaver::save(collectorNS::ApplicationObjectCollector* coll, std::string& projectName)
	{

		saveloadNS::dataSaver::ofstreamList.insert(&out);

		if (!out.is_open())
		{
			out.open(logNS::Logger::PROJECTDIR + saveloadNS::COLLECTORSAVINGFILE);
			dataSaver::sessionWasClosed = false;
		}
			

		out << saveloadNS::CollectorLoader::COLLECTORTAG << std::endl;
		out << coll->getCollectorName() << std::endl;
		out << saveloadNS::CollectorLoader::COLLECTORNUMBER << std::endl;
		out << coll->collectorNumber << std::endl;
		out << saveloadNS::CollectorLoader::COLLECTORISONTAG << std::endl;
		out << coll->isOn << std::endl;
		for (int i = 0; i < coll->Pcontainer->size(); i++)
			coll->getSubObject(i)->save(out);
		out << saveloadNS::CollectorLoader::COLLECTORENDTAG << std::endl;


	}

}