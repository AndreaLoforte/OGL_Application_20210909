#include<collectorLoader.h>
#include<log.h>
#include<regex>

using namespace std;

namespace saveloadNS {


	const string
		CollectorLoader::COLLECTORTAG = "--------COLLECTOR--------",
		CollectorLoader::COLLECTORNUMBER = "COLLECTOR_NUMBER",
		CollectorLoader::COLLECTORENDTAG = "--------ENDCOLLECTOR--------",
		CollectorLoader::OBJECTNAMETAG = "AOobjectName",
		CollectorLoader::AOPOSITIONTAG = "AOposition",
		CollectorLoader::AOORIENTATIONTAG = "AOorientation",
		CollectorLoader::AOTRMATRIXTAG = "AOTrMatrix",
		CollectorLoader::AOINSTANCENUMBERTAG = "AOinstanceNumber",
		CollectorLoader::AOCOLORTAG = "AOcolor",
		CollectorLoader::DOSIZETAG = "DOsize",
		CollectorLoader::AOISONFLAGTAG = "AOisOnFlag",
		CollectorLoader::COLLECTORISONTAG = "OCisOnFlag";


	void CollectorLoader::loadCollectorMapsIntoDataStructure()
	{
		/*itero su tutti i collettori*/
		for (int i = 0; i < TAGLIST.at(COLLECTORTAG).getSize(); i++)
		{
			CollectorDataStructure collettore;
			collettore.collectorsName = TAGLIST.at(COLLECTORTAG).getLine(i);
			collettore.collectorNumber = std::stoi(TAGLIST.at(COLLECTORNUMBER).getLine(i));
			collettore.pos_start = TAGLIST.at(COLLECTORTAG).getPos(i);
			collettore.pos_end = TAGLIST.at(COLLECTORENDTAG).getPos(i);

			/*itero su tutti gli oggetti dei collettori*/
			for (int j = 0; j < TAGLIST.at(OBJECTNAMETAG).getSize(); j++)
			{
				size_t objectPosInFile = TAGLIST.at(OBJECTNAMETAG).getPos(j);
				size_t NextObjectPosInFile = TAGLIST.at(OBJECTNAMETAG).getPos(j + 1);

				/*quando la posizione dell'oggetto nel file, è contenuta dentro il range di posizione iniziale-finale
				di un collettore, allora carico quell'oggetto*/
				if (objectPosInFile > collettore.pos_start && objectPosInFile < collettore.pos_end)
				{
					collettore.AOobjects.push_back(AODataStructure());
					collettore.AOobjects.back().ObjectName = TAGLIST.at(OBJECTNAMETAG).getLine(j);

					loadAttributeArray(collettore.AOobjects.back().AOposition, collettore.pos_start, collettore.pos_end, TAGLIST.at(AOPOSITIONTAG));
					loadAttributeQuaternion(collettore.AOobjects.back().AOorientation, collettore.pos_start, collettore.pos_end, TAGLIST.at(AOORIENTATIONTAG));
					loadAttributevmathVec4(collettore.AOobjects.back().AOcolor, collettore.pos_start, collettore.pos_end, TAGLIST.at(AOCOLORTAG));
					loadAttributevectorFloat(collettore.AOobjects.back().AOsize, collettore.pos_start, collettore.pos_end, TAGLIST.at(DOSIZETAG));
					loadAttributeBool(collettore.AOobjects.back().isOn, collettore.pos_start, collettore.pos_end, TAGLIST.at(AOISONFLAGTAG));
					loadAttributeBool(collettore.isOn, collettore.pos_start, collettore.pos_end, TAGLIST.at(COLLECTORISONTAG));
					loadAttributevmathMatrix4(collettore.AOobjects.back().AOTrMatrix, collettore.pos_start, collettore.pos_end, TAGLIST.at(AOTRMATRIXTAG));


				}
			}

			collectors.push_back(collettore);
		}
	}



	CollectorLoader::CollectorLoader(ifstream& in)
	{

		if (in.is_open())
		{
			while (!in.eof() && (int/*casting is needed to avoid ambiguous operator !=*/)in.tellg() != -1)
			{
				getline(in, s);
				size_t cursor_pos = in.tellg();
				size_t lineLength = s.length();
				size_t line_beg = cursor_pos - lineLength - 2; //2 extra char "\n"
				fileMap.insert(s, line_beg);

			}

			totalLines = fileMap.getSize();


			if (fileMap.getCharNumber() == 0)
			{
				FileIsEmpty = true;
				return;
			}


			setTAGLIST(tagList);
			loadAllCollectorsMap(TAGLIST);
			loadCollectorMapsIntoDataStructure();


		}
	}
}