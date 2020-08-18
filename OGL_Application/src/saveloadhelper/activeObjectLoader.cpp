#include<activeobjectloader.h>
#include<log.h>

using namespace std;

namespace saveloadNS {


	const string
		ActiveObjectLoader::COLLECTORTAG = "ACTIVEOBJECT_",
		ActiveObjectLoader::COLLECTORENDTAG = "--------ACTIVEOBJECTEND--------",
		ActiveObjectLoader::OBJECTNAMETAG = "AOobjectName",
		ActiveObjectLoader::AOPOSITIONTAG = "AOposition",
		ActiveObjectLoader::AOORIENTATIONTAG = "AOorientation",
		ActiveObjectLoader::AOTRMATRIXTAG = "AOTrMatrix",
		ActiveObjectLoader::AOINSTANCENUMBERTAG = "AOinstanceNumber",
		ActiveObjectLoader::AOCOLORTAG = "AOcolor",
		ActiveObjectLoader::DOSIZETAG = "DOsize",
		ActiveObjectLoader::AOISONFLAGTAG = "AOisOnFlag",
		ActiveObjectLoader::COLLECTORISONTAG = "OCisOnFlag",
		ActiveObjectLoader::ACTIVITYGROUNDID = "ACTIVE_OBJECT_ACTIVITYGROUND_ID";







	void ActiveObjectLoader::loadCollectorMapsIntoDataStructure()
	{

		/*itero su tutti i collettori*/
		for (int i = 0; i < TAGLIST.at(STARTDELIMITER).getSize(); i++)
		{
			ActiveObjectDataStructure collettore;
			collettore.collectorsID =TAGLIST.at(STARTDELIMITER).getLine(i);
			collettore.pos_start = TAGLIST.at(STARTDELIMITER).getPos(i);
			collettore.pos_end = TAGLIST.at(ENDDELIMITER).getPos(i);


			//now loading ActivityGroundID
			for (int k = 0; k < TAGLIST.at("ACTIVE_OBJECT_ACTIVITYGROUND_ID").getSize(); k++)
			{
				size_t ActivityGroundID_posInFile = TAGLIST.at("ACTIVE_OBJECT_ACTIVITYGROUND_ID").getPos(k);
				//size_t aoTrMatrix_posInFile_LastRow = AOTrMatrixMap.getPos(k + 3);//5 = 1 riga tag + 4 righe numeriche
				if (ActivityGroundID_posInFile > collettore.pos_start && ActivityGroundID_posInFile < collettore.pos_end)
				{
					//AOTrMatrix è una matrice di 4 righe, quindi devo prendere 4 stringhe
					string activityGroundID = TAGLIST.at("ACTIVE_OBJECT_ACTIVITYGROUND_ID").getLine(k + 1);
					collettore.activityGroundID = activityGroundID;

				}
			}



			/*itero su tutti gli oggetti dei collettori*/
			for (int j = 0; j < TAGLIST.at("AOobjectName").getSize(); j++)
			{
				size_t objectPosInFile = TAGLIST.at("AOobjectName").getPos(j);
				size_t NextObjectPosInFile = TAGLIST.at("AOobjectName").getPos(j + 1);

				/*quando la posizione dell'oggetto nel file, è contenuta dentro il range di posizione iniziale-finale
				di un collettore, allora carico quell'oggetto*/
				if (objectPosInFile > collettore.pos_start && objectPosInFile < collettore.pos_end)
				{
					collettore.AOobjects.push_back(AODataStructure());
					collettore.AOobjects.back().ObjectName = TAGLIST.at("AOobjectName").getLine(j);

					//ora inserisco AOPosition : per ogni tag di AOposition devo verificare che il tag sia contenuto tra il nome dell'oggetto j e j+1
					for (int k = 0; k < TAGLIST.at("AOposition").getSize(); k++)
					{
						size_t aoposition_posInFile = TAGLIST.at("AOposition").getPos(k);

						if (aoposition_posInFile > objectPosInFile && aoposition_posInFile < NextObjectPosInFile)
						{
							string AOpositionStringFormat = TAGLIST.at("AOposition").getLine(k);//il tag sta in k il valore in k+1;

							std::array<float, 3> pos = stringToVec3(AOpositionStringFormat);

							collettore.AOobjects.back().AOposition = pos;

						}
					}

					// LOADING ORIENTATION
					for (int k = 0; k < TAGLIST.at("AOorientation").getSize(); k++)
					{
						size_t aoorientatino_posInFile = TAGLIST.at("AOorientation").getPos(k);

						if (aoorientatino_posInFile > objectPosInFile && aoorientatino_posInFile < NextObjectPosInFile)
						{
							string AOorientationStringFormat = TAGLIST.at("AOorientation").getLine(k);//il tag sta in k il valore in k+1;

							std::vector<float> orientation;
							stringToFloatVec(AOorientationStringFormat, orientation);

							collettore.AOobjects.back().AOorientation.w = orientation[0];
							collettore.AOobjects.back().AOorientation.x = orientation[1];
							collettore.AOobjects.back().AOorientation.y = orientation[2];
							collettore.AOobjects.back().AOorientation.z = orientation[3];

						}
					}

					//LOADING COLOR OF THE OBJECT
					for (int k = 0; k < TAGLIST.at("AOcolor").getSize(); k++)
					{
						size_t aocolor_posInFile = TAGLIST.at("AOcolor").getPos(k);

						if (aocolor_posInFile > objectPosInFile && aocolor_posInFile < NextObjectPosInFile)
						{
							string AOcolorStringFormat = TAGLIST.at("AOcolor").getLine(k);//il tag sta in k il valore in k+1;

							std::vector<float> color;
							stringToFloatVec(AOcolorStringFormat, color);
							collettore.AOobjects.back().AOcolor[0] = color[0];
							collettore.AOobjects.back().AOcolor[1] = color[1];
							collettore.AOobjects.back().AOcolor[2] = color[2];
							collettore.AOobjects.back().AOcolor[3] = color[3];

						}
					}


					//LOADING SIZE OF THE OBJECT
					for (int k = 0; k < TAGLIST.at("DOsize").getSize(); k++)
					{
						size_t dosize_posInFile = TAGLIST.at("DOsize").getPos(k);

						if (dosize_posInFile > objectPosInFile && dosize_posInFile < NextObjectPosInFile)
						{
							string DOsizeStringFormat = TAGLIST.at("DOsize").getLine(k);//il tag sta in k il valore in k+1;

							std::vector<float> size;
							stringToFloatVec(DOsizeStringFormat, size);
							for (int i = 0; i < size.size(); i++)
								collettore.AOobjects.back().AOsize.push_back(size[i]);

						}
					}

					//LOADING APPLICATION OBJECT IS ON FLAG
					for (int k = 0; k < TAGLIST.at("AOisOnFlag").getSize(); k++)
					{
						size_t isonflag_posInFile = TAGLIST.at("AOisOnFlag").getPos(k);

						if (isonflag_posInFile > objectPosInFile && isonflag_posInFile < NextObjectPosInFile)
						{
							string isOnStringFormat = TAGLIST.at("AOisOnFlag").getLine(k);//il tag sta in k il valore in k+1;
							if (isOnStringFormat == "1")
								collettore.AOobjects.back().isOn = true;
							else
								collettore.AOobjects.back().isOn = false;


						}
					}

					//LOADING OBJECT COLLECTOR IS ON FLAG
					for (int k = 0; k < TAGLIST.at("OCisOnFlag").getSize(); k++)
					{
						size_t isonflag_posInFile = TAGLIST.at("OCisOnFlag").getPos(k);

						if (isonflag_posInFile > collettore.pos_start && isonflag_posInFile < collettore.pos_end)
						{
							string isOnStringFormat = TAGLIST.at("OCisOnFlag").getLine(k);//il tag sta in k il valore in k+1;
							if (isOnStringFormat == "1")
								collettore.isOn = true;
							else
								collettore.isOn = false;


						}
					}



					//ora inserisco AOTrMatrix : per ogni tag di AOTrMatrix devo verificare che il tag sia contenuto tra il nome dell'oggetto j e j+1
					for (int k = 0; k < TAGLIST.at("AOTrMatrix").getSize(); k++)
					{
						size_t aoTrMatrix_posInFile = TAGLIST.at("AOTrMatrix").getPos(k);
						size_t aoTrMatrix_posInFile_LastRow = TAGLIST.at("AOTrMatrix").getPos(k + 3);//5 = 1 riga tag + 4 righe numeriche
						if (aoTrMatrix_posInFile > objectPosInFile && aoTrMatrix_posInFile_LastRow < NextObjectPosInFile)
						{
							//AOTrMatrix è una matrice di 4 righe, quindi devo prendere 4 stringhe
							string row1 = TAGLIST.at("AOTrMatrix").getLine(k);
							string row2 = TAGLIST.at("AOTrMatrix").getLine(k + 1);
							string row3 = TAGLIST.at("AOTrMatrix").getLine(k + 2);
							string row4 = TAGLIST.at("AOTrMatrix").getLine(k + 3);

							collettore.AOobjects.back().AOTrMatrix = stringToMat4(row1 + " " + row2 + " " + row3 + " " + row4);

						}
					}



				}
			}

			collectors.push_back(collettore);
		}
	}





	ActiveObjectLoader::ActiveObjectLoader(ifstream& in)
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



			loadAllCollectorsMap(TAGLIST);
			loadCollectorMapsIntoDataStructure();


		}
	}
}

