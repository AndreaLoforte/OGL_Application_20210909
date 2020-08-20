#include<saver.h>



namespace saveloadNS {


	bool dataSaver::sessionWasClosed;
	set<ofstream*> dataSaver::ofstreamList;



	void dataSaver::clearFile(const string& filefullpath)
	{
		/*out.open(filefullpath);
		out.clear();
		out.close();*/
	}
}