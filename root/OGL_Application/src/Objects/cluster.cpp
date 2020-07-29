#include<cluster.h>
namespace myobjectNS {


	/*void Cluster::push_back(collectorNS::ApplicationObjectCollector* obj)
	{
		if (counter < size)
		{
			group[counter].pointer = obj;
			counter++;
		}

		else
		{
			Backup();
			AllocateSpace();
			Restore();
			group[counter].pointer = obj;
		}
	}

	void Cluster::Backup()
	{
		backup = new ObjectPointer[counter];
		for (int i = 0; i < counter; i++)
			backup[i].pointer = group[i].pointer;
		delete group;
	}

	void Cluster::Restore()
	{

		for (int i = 0; i < counter; i++)
			group[i].pointer = backup[i].pointer;
		delete backup;
	}

	void Cluster::AllocateSpace()
	{
		size = 2 * counter;
		group = new ObjectPointer[size];
	}*/

	
}

