#pragma once

#include<objectCollector.h>
#include<map>
#include<string>

using namespace std;

namespace clusterNS {


	class Cluster {
	public:

		std::vector<collectorNS::ApplicationObjectCollector*> group;

	};


	class ClusterManager {
		typedef std::map<std::string, Cluster>::iterator clusterIT;
	public:
		static std::map<std::string, Cluster> clusterMap;
		static clusterIT it;
		static void printClusterList();
		static void saveCluster(const Cluster&);
		static void eraseByString(const string&);



	};

	

	
}//NS
