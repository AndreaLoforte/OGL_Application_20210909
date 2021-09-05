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
		unsigned& getCharNumber(const ifstream& in);
		/*funzione che ritorna tutte le stringhe della 
		mappa contenute dentro il range specificato*/
		vector<string> getContentInRange(size_t, size_t);

		void popLastElement();
	};


	
	/*definition of a class used only to generate hineritance*/
	class FileHelper {
	public:
		template <typename T>
		FileHelper(ifstream& in, vector<string> tagList, T *p );
		map<string, FileMap> TAGLIST;
		FileMap fileMap;
		string s;
		unsigned totalLines = 0;
		unsigned totalChars = 0;
		bool FileIsEmpty = false;
		void setTAGLIST(const vector<string>& tagList);
		void loadLine(const string& TAG, FileMap& fmTarget);
		void loadAttributeFloat(float& f_number, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		void loadAllCollectorsMap(map<string, FileMap>& TAGLIST);
		void loadAttributeString(string& targetString, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		void loadAttributeArray(array<float, 3>& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		void loadAttributeQuaternion(mymathlibNS::Quaternion& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		void loadAttributevmathVec4(vmath::vec4& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		void loadAttributevectorFloat(vector<float>& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		void loadAttributeBool(bool& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		void loadAttributevmathMatrix4(vmath::mat4& dataStorage, const size_t& pos_start, const size_t& pos_end, FileMap& fm);
		const string TAG_TYPEMATRIX = "Matrix";

		void loadMapsIntoDataStructure(){}
	};



	template<typename T>
	FileHelper::FileHelper(ifstream& in, vector<string> tagList, T* p)
	{
		size_t cursor_pos = 0;
		size_t lineLength = 0;
		size_t line_beg = 0;

		if (in.is_open())
		{
			while (!in.eof() && (int/*casting is needed to avoid ambiguous operator !=*/)in.tellg() != -1 )
			{
				getline(in, s);
				cursor_pos = in.tellg();
				lineLength = s.length();
				line_beg = cursor_pos - lineLength - 2; //2 extra char "\n"
				if (line_beg < 0 || line_beg > 10000000)
					in.bad();
					///std::cout << "hello" << std::endl;
					//in.bad();
				else
				fileMap.insert(s, line_beg);

			

			}

			totalLines = fileMap.getSize();


			const size_t charsNumber = fileMap.getCharNumber(in);

			if (charsNumber == 0)
			{
				FileIsEmpty = true;
				return;
			}


			setTAGLIST(tagList);
			loadAllCollectorsMap(TAGLIST);
			p->loadMapsIntoDataStructure();


		}
	}




	

	


}




#endif