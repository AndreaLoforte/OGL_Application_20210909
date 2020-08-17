#include<fileMap.h>
#include<log.h>

using namespace std;

namespace saveloadNS {


	void FileMap::insert(string s, size_t pos) {
		fileLines.push_back(s);
		filePos.push_back(pos);
		size++;
	}
	string FileMap::getLine(unsigned i) {//ritorna la stringa i-esima della mappa
		if (i < fileLines.size())
			return fileLines[i];
		else
			return "error : out of map size";
	}
	size_t FileMap::getPos(unsigned i)//ritorna la posizione nel file, della i-esima stringa della mappa
	{
		if (i < fileLines.size())
			return filePos[i];
		else
			return -1;

	}
	unsigned& FileMap::getSize() { return size; }

	void FileMap::popLastElement()
	{
		fileLines.pop_back();
		filePos.pop_back();
		--size;
	}


	vector<string> FileMap::getContentInRange(size_t beg, size_t end)
	{
		vector<string> result;

		for (int i = 0; i < fileLines.size(); i++)
			if (beg <= filePos[i] && filePos[i] <= end)
				result.push_back(fileLines[i]);

		return result;
	}



	





}