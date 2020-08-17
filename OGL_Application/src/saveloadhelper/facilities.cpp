#include<log.h>
#include<array>
using namespace std;

namespace saveloadNS {


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