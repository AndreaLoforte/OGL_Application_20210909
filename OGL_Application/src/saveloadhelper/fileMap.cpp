#include<fileMap.h>
#include<log.h>

using namespace std;

namespace saveloadNS {


	void  FileHelper::loadAllCollectorsMap(map<string,FileMap>& TAGLIST)
	{

		for (map<string, FileMap>::iterator it = TAGLIST.begin(); it != TAGLIST.end(); it++)
		{
			loadLine(it->first, it->second);
		}
	}



	void FileHelper::loadLine(const string& TAG, FileMap& fmTarget)
	{

		if (TAG.find(TAG_ENDCOLLECTOR) != string::npos)
		{
			for (int i = 0; i < totalLines; i++)
				if (fileMap.getLine(i).find(TAG) != string::npos)
				{
					fmTarget.insert(fileMap.getLine(i), fileMap.getPos(i));
				}

			return;
		}

		unsigned linesNbr = 1;
		if (TAG.find(TAG_TYPEMATRIX) != string::npos)
		{
			linesNbr = 4;
			/*look through all the fileMap, if TAG is found, insert in fmTarget
		the follwint linesNbr lines of the file*/
			for (int i = 0; i < totalLines; i++)
				if (fileMap.getLine(i).find(TAG) != string::npos)
				{
					for (int j = 1; j <= linesNbr; j++)
						fmTarget.insert(fileMap.getLine(i + j), fileMap.getPos(i + j));
				}

			return;
		}


		for (int i = 0; i < totalLines; i++)
			if (fileMap.getLine(i).find(TAG) != string::npos)
			{
				fmTarget.insert(fileMap.getLine(i + 1), fileMap.getPos(i + 1));
			}
	}



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