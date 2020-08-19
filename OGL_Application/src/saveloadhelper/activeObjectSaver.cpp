//#include<fstream>
//#include<string>
#include<activeobjectloader.h>
#include<activeObjectCollector.h>
#include<applicationObject.h>
#include<ground.h>

using namespace std;
namespace saveloadNS {

	ofstream* ActiveObjectSaver::save(collectorNS::ActiveObject* coll, std::string& projectName)
	{
		if (CreateDirectoryA(logNS::Logger::PROJECTDIR.c_str(), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			// CopyFile(...)
		}
		else
		{
			// Failed to create directory.
			return NULL;
		}
		
		static ofstream out(logNS::Logger::PROJECTDIR + saveloadNS::ACTIVEOBJECTSAVINGFILE);
		
		//IDENTIFICO IL COLLETTORE
		out << saveloadNS::ActiveObjectLoader::COLLECTORTAG << std::endl;
		out << coll->getCollectorName() << std::endl;
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


		return &out;

	}


}