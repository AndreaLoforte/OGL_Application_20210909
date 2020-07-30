#include<cluster.h>
#include<userInterface.h>
namespace clusterNS {

	std::map<std::string, Cluster> ClusterManager::clusterMap;
	ClusterManager::clusterIT ClusterManager::it;


	void ClusterManager::printClusterList()
	{
		for (it = clusterMap.begin(); it != clusterMap.end(); it++)
		{
			UserInterface::mapButtonOnParentBranch(it->first,it->first+ " : ",0.30);

			for (int i = 0; i < it->second.group.size(); i++)
			{
				UserInterface::mapButtonOnParentBranch(it->second.group[i]->collectorID,it->second.group[i]->collectorID);
			}
		}
	}


	void ClusterManager::saveCluster(const Cluster& c)
	{



	}


	
}

