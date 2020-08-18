#ifndef SAVELOADHELPER
#define SAVELOADHELPER
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<vmath.h>
#include<array>
#include<mymathlib.h>
using namespace std;
namespace saveloadNS {

	
	void stringToFloatVec(string s, vector<float>& vec);
	vmath::mat4 stringToMat4(string m);
	std::array<float, 3> stringToVec3(string s);

	/*it's a Map to hold together the string content
	of the file, with information of the cursor position
	for each row (cursor position depends on number of chars in the line)*/

	class FileMap {
	public:
		FileMap(){}
		FileMap(const string s):fileMapID(s){}
		string fileMapID;
		/*collect each line of the file*/
		vector<string> fileLines;
		/*for each line, collect the 
		respective cursor position*/
		vector<std::fpos_t> filePos;
		unsigned size = 0;
		unsigned charnumber = 0;
		void insert(string s, size_t pos);

		/*get the i-th line in the file*/
		string getLine(unsigned i);
		/*get the cursor position at line i*/
		size_t getPos(unsigned i);
		/*get the map size*/
		unsigned& getSize();
		unsigned& getCharNumber()
		{
			for (int i = 0; i < fileLines.size(); i++)
				charnumber += fileLines[i].length();
			return charnumber;
		}
		/*funzione che ritorna tutte le stringhe della 
		mappa contenute dentro il range specificato*/
		vector<string> getContentInRange(size_t, size_t);

		void popLastElement();
	};


	
	/*definition of a class used only to generate hineritance*/
	class FileHelper {
	public:
		FileMap fileMap;
		string s;
		unsigned totalLines = 0;
		unsigned totalChars = 0;
		void loadLine(const string& TAG, FileMap& fmTarget);
		void  loadAllCollectorsMap(map<string, FileMap>& TAGLIST);

		const string TAG_ENDCOLLECTOR = "END----";
		const string TAG_TYPEMATRIX = "Matrix";
	};





	

	


}




#endif