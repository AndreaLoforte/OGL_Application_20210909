#include<cluster.h>
#include<userInterface.h>
namespace clusterNS {

	std::map<std::string, Cluster> ClusterManager::clusterMap;
	ClusterManager::clusterIT ClusterManager::it;


	void ClusterManager::printClusterList()
	{
		for (it = clusterMap.begin(); it != clusterMap.end(); it++)
		{
			UserInterface::showButton(it->first, it->first + " : ");

			for (int i = 0; i < it->second.group.size(); i++)
			{
				UserInterface::showButton(it->second.group[i]->collectorID,it->second.group[i]->collectorID);
			}
		}
	}


	void ClusterManager::saveCluster(const Cluster& c){}


	
}

