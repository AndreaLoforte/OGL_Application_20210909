#include<saveloadhelper.h>
#include<log.h>

using namespace std;

namespace saveloadNS {


	FileHelper::FileHelper(ifstream& in) 
	{

		if (in.is_open())
		{
			while (!in.eof() && in.tellg() != -1)
			{
				getline(in, s);
				size_t cursor_pos = in.tellg();
				size_t lineLength = s.length();
				size_t line_beg = cursor_pos - lineLength - 2; //2 extra char "\n"
				fileMap.insert(s, line_beg);

			}

			totalLines = fileMap.getSize();

			countChar();
			if (totalChars == 0)
			{
				FileIsEmpty = true;
				return;
			}


			countChar();
	
		}


	}



	void FileHelper::countChar() {
		string s;
		for (int i = 0; i < getTotalLines(); i++)
		{
			s = fileMap.getLine(i);
			getTotalChars() += s.length();
		}

	}




	void FileHelper::writeFile(ofstream& out)
	{
		for (int i = 0; i < totalLines; i++)
		{
			out << fileMap.getLine(i) << std::endl;
		}

		out.close();
	}


	void FileHelper::printCollectors() {

		/*for (int i = 0; i < collectors.size(); i++)
		{
			std::cout << collectors.at(i).collectorsID << std::endl;
			std::cout << collectors.at(i).pos_start << " " << collectors.at(i).pos_end << std::endl;
			for (int j = 0; j < collectors.at(i).AOobjects.size(); j++)
				std::cout << collectors.at(i).AOobjects[j].ObjectName << std::endl;
		}*/

	}


	void stringToFloatVec(string s, vector<float>& vec)
	{
		string firstNum;

		size_t first_separator = s.find_first_of(" ");

		if (first_separator == 0)
		{
			s = s.substr(1);
			first_separator = s.find_first_of(" ");
		}

		if (s.size() == 0)
			return;


		firstNum = s.substr(0, first_separator);
		vec.push_back(std::stof(firstNum));

		if (first_separator != string::npos)
			s = s.substr(first_separator + 1);
		else
			return;



		return stringToFloatVec(s, vec);

	}


	std::array<float, 3> stringToVec3(string s) {
		array<float, 3> arr;

		string num1, num2, num3;

		//sono 3 numeri separati da uno spazio.

		size_t sep;

		sep = s.find_first_of(" ");
		num1 = s.substr(0, sep);

		s = s.substr(sep + 1);//qui ho gli altri due numeri

		sep = s.find_first_of(" ");
		num2 = s.substr(0, sep);

		s = s.substr(sep + 1);//qui ho l'ultimo numero
		num3 = s;

		arr[0] = std::stof(num1);
		arr[1] = std::stof(num2);
		arr[2] = std::stof(num3);

		return arr;
	}



	vmath::mat4 stringToMat4(string m)
	{
		vector<float> matrix;
		stringToFloatVec(m, matrix);

		vmath::mat4 mat;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mat[i][j] = matrix[j + 4 * i];

		return mat;


	}
	





}