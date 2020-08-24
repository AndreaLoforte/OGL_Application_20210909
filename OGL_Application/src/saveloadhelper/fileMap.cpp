#include<fileMap.h>
#include<log.h>
#include<regex>
using namespace std;

namespace saveloadNS {


	
	


	void FileHelper::setTAGLIST(const vector<string>& tagList)
	{
		for (int i = 0; i < tagList.size(); i++)
			TAGLIST.emplace(tagList[i], FileMap(tagList[i]));
	}




	void FileHelper::loadAttributeString(string& targetString, const size_t& pos_start, const size_t& pos_end, FileMap& fm)
	{
		for (int k = 0; k < fm.getSize(); k++)
		{
			size_t fetchedData_posInFile = fm.getPos(k);

			if (fetchedData_posInFile > pos_start && fetchedData_posInFile < pos_end)
			{
				targetString = fm.getLine(k);
			}
		}

	}

	void FileHelper::loadAttributeArray(array<float, 3>& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm)
	{
		for (int k = 0; k < fm.getSize(); k++)
		{
			size_t array_posInFile = fm.getPos(k);

			if (array_posInFile > pos_start && array_posInFile < pos_end)
			{
				string dataStringFormat = fm.getLine(k);
				dataStorage = stringToVec3(dataStringFormat);

			}
		}

	}

	void FileHelper::loadAttributeQuaternion(mymathlibNS::Quaternion& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm)
	{
		for (int k = 0; k < fm.getSize(); k++)
		{
			size_t quaternion_posInFile = fm.getPos(k);

			if (quaternion_posInFile > pos_start && quaternion_posInFile < pos_end)
			{
				string AOorientationStringFormat = fm.getLine(k);

				std::vector<float> tempStorage;
				stringToFloatVec(AOorientationStringFormat, tempStorage);

				dataStorage.w = tempStorage[0];
				dataStorage.x = tempStorage[1];
				dataStorage.y = tempStorage[2];
				dataStorage.z = tempStorage[3];

			}
		}

	}


	void FileHelper::loadAttributevmathVec4(vmath::vec4& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm)
	{
		for (int k = 0; k < fm.getSize(); k++)
		{
			size_t vec4_posInFile = fm.getPos(k);

			if (vec4_posInFile > pos_start && vec4_posInFile < pos_end)
			{
				string AOcolorStringFormat = fm.getLine(k);//il tag sta in k il valore in k+1;

				std::vector<float> tempStorage;
				stringToFloatVec(AOcolorStringFormat, tempStorage);
				dataStorage[0] = tempStorage[0];
				dataStorage[1] = tempStorage[1];
				dataStorage[2] = tempStorage[2];
				dataStorage[3] = tempStorage[3];

			}
		}
	}

	void FileHelper::loadAttributevectorFloat(vector<float>& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm)
	{
		for (int k = 0; k < fm.getSize(); k++)
		{
			size_t vec_posInFile = fm.getPos(k);

			if (vec_posInFile > pos_start && vec_posInFile < pos_end)
			{
				string StringFormat = fm.getLine(k);//il tag sta in k il valore in k+1;

				std::vector<float> size;
				stringToFloatVec(StringFormat, size);
				for (int i = 0; i < size.size(); i++)
					dataStorage.push_back(size[i]);

			}
		}

	}

	void FileHelper::loadAttributeBool(bool& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm)
	{
		for (int k = 0; k < fm.getSize(); k++)
		{
			size_t flag_posInFile = fm.getPos(k);

			if (flag_posInFile > pos_start && flag_posInFile < pos_end)
			{
				string isOnStringFormat = fm.getLine(k);//il tag sta in k il valore in k+1;
				if (isOnStringFormat == "1")
					dataStorage = true;
				else
					dataStorage = false;


			}
		}
	}

	void FileHelper::loadAttributevmathMatrix4(vmath::mat4& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm)
	{
		for (int k = 0; k < fm.getSize(); k++)
		{
			size_t Matrix_posInFile = fm.getPos(k);
			size_t Matrix_posInFile_LastRow = fm.getPos(k + 3);//5 = 1 riga tag + 4 righe numeriche
			if (Matrix_posInFile > pos_start && Matrix_posInFile_LastRow < pos_end)
			{
				//AOTrMatrix è una matrice di 4 righe, quindi devo prendere 4 stringhe
				string row1 = fm.getLine(k);
				string row2 = fm.getLine(k + 1);
				string row3 = fm.getLine(k + 2);
				string row4 = fm.getLine(k + 3);

				dataStorage = stringToMat4(row1 + " " + row2 + " " + row3 + " " + row4);

			}
		}
	}




	void  FileHelper::loadAllCollectorsMap(map<string,FileMap>& TAGLIST)
	{

		for (map<string, FileMap>::iterator it = TAGLIST.begin(); it != TAGLIST.end(); it++)
		{
			loadLine(it->first, it->second);
		}
	}



	void FileHelper::loadLine(const string& TAG, FileMap& fmTarget)
	{
		unsigned linesNbr = 1;
		if (TAG.find(TAG_TYPEMATRIX) != string::npos)
		{
			linesNbr = 4;
			for (int i = 0; i < totalLines; i++)
				if (fileMap.getLine(i).find(TAG) != string::npos)
				{
					for (int j = 1; j <= linesNbr; j++)
						fmTarget.insert(fileMap.getLine(i + j), fileMap.getPos(i + j));
				}

			return;
		}


		for (int i = 0; i < totalLines; i++)
			if(std::regex_match(fileMap.getLine(i),std::regex(TAG)))
			{
				if (TAG.find("END") != string::npos)
				{
					fmTarget.insert(fileMap.getLine(i), fileMap.getPos(i));
					continue;
				}
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



	unsigned& FileMap::getCharNumber(const ifstream& in)
	{

		for (int i = 0; i < fileLines.size(); i++)
			charnumber += fileLines[i].length();
		return charnumber;
	}





}