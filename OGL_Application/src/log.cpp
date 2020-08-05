#include<log.h>
#include<applicationObject.h>
#include<assets.h>
#include<textRenderer.h>
#include<fpcamera.h>

namespace exceptionNS {

	using namespace std;

	TestClass::TestClass(char const* const message) throw()
		: std::runtime_error(message)
	{

	}

	char const * TestClass::what() const throw()
	{
		return exception::what();
	}



}

namespace logNS {


	std::string Logger::LOGDIR{ Application::getApplicationRootDir() + "/OGL_Application/log_and_savings/" };
	std::string Logger::STOREDDATADIR{ LOGDIR + "savedProjectData/" };
	std::vector<std::string> Logger::files_fullpath{ LOGDIR };
	std::vector<std::string> Logger::log_list;
	bool Logger::FIRST_LOG_ACCESS = true;
	bool Logger::FIRST_DATAPROJECT_ACCESS = true;
	std::vector<std::string> Logger::MatrixComponent;
	std::ofstream Logger::storedDatafile;
	std::map<std::string, bool> Logger::isFirstWrite;


	using namespace std;




	void Logger::saveMatrix44(std::ofstream& out, vmath::mat4& mat) {

		out << mat[0][0] << " ";
		out << mat[0][1] << " ";
		out << mat[0][2] << " ";
		out << mat[0][3] << " ";
		out << std::endl;
		out << mat[1][0] << " ";
		out << mat[1][1] << " ";
		out << mat[1][2] << " ";
		out << mat[1][3] << " ";
		out << std::endl;
		out << mat[2][0] << " ";
		out << mat[2][1] << " ";
		out << mat[2][2] << " ";
		out << mat[2][3] << " ";
		out << std::endl;
		out << mat[3][0] << " ";
		out << mat[3][1] << " ";
		out << mat[3][2] << " ";
		out << mat[3][3] << " ";


	}

	int Logger::checkIfstream(std::ifstream& in)
	{
		if (in.rdstate() == in.goodbit)
		{
			Logger::writeLog("input file stream state is goodbit : No errors (zero value iostate)");
			return 0;
		}

		if (in.rdstate() == in.eofbit)
		{
			Logger::writeLog("input file stream state is eofbit : End-of-File reached on input operation");
			return 100;
		}
		if (in.rdstate() == in.failbit)
		{
			Logger::writeLog("input file stream state is failbit : Logical error on i/o operation");
			return -1;
		}
	
		if (in.rdstate() == in.badbit)
		{
			Logger::writeLog("input file stream state is goodbit : Read/writing error on i/o operation");
			return -2;
		}
		return 0;

	}

	int Logger::safeIFread(std::ifstream& in, std::string& s)
	{
		std::size_t prev_pos = in.tellg();
		std::string flush;
		in >> s;
		if (checkIfstream(in) != 0)
		{
			in.clear();
			in.seekg(prev_pos);
			in >> flush;//vado oltre la riga in prev_pos
			in >> flush;//vado oltre la riga che ha rotto infile
			if (checkIfstream(in) == 0)
				return 0;
			else return -1;
		}
		return 0;
		


	}
	


	void Logger::loadMatrix44(std::ifstream& in, vmath::mat4& mat, std::size_t start_from, std::size_t stop_at) {

		logNS::Logger::checkIfstream(in);
		logNS::Logger::writeLog("4");

		vmath::mat4 mat2;
		std::string s1,s2,s3,s4;
		float f1,f2,f3,f4;
		vmath::vec4 vec4;
		in >>s1; f1= std::stof(s1); 
		in >>s2; f2= std::stof(s2); 
		in >>s3; f3= std::stof(s3); 
		in >>s4; f4= std::stof(s4); 
		vec4 = vmath::vec4(f1, f2, f3, f4);
		mat[0] = vec4;
		in >>s1; f1= std::stof(s1);
		in >>s2; f2= std::stof(s2);
		in >>s3; f3= std::stof(s3);
		in >>s4; f4= std::stof(s4);
		vec4 = vmath::vec4(f1, f2, f3, f4);
		mat[1] = vec4;
		in >>s1; f1= std::stof(s1); 
		in >>s2; f2= std::stof(s2); 
		in >>s3; f3= std::stof(s3); 
		in >>s4; f4= std::stof(s4); 
		vec4 = vmath::vec4(f1, f2, f3, f4);
		mat[2] = vec4;
		in >>s1; f1= std::stof(s1); 
		in >>s2; f2= std::stof(s2); 
		in >>s3; f3= std::stof(s3); 
		in >>s4; f4= std::stof(s4); 
		vec4 = vmath::vec4(f1, f2, f3, f4);
		mat[3] = vec4;



	}







	vmath::mat4 Logger::LoadMatrix(std::ifstream& in) {

		vmath::mat4 loadedMatrix;
		std::string s;

		std::getline(in, s);
		while (s == "")
			std::getline(in, s);//salto tutte le righe vuote


		for (int i = 0; i < 4; i++)
		{
			
			for (int j = 0; j < 4; j++)
			{
				std::size_t from = s.find(MatrixComponent[j + 4 * i]);
				from += MatrixComponent[j+4*i].length(); //spazio + xx + spazio + : + spazio = 6 caratteri
				std::size_t to;
				std::string matrixElement;
				if (j < 3)
				{
					to = s.find(MatrixComponent[j + 1 + 4 * i]);
					matrixElement = s.substr(from, to - 1);
				}

				if (j == 3)
				{
					matrixElement = s.substr(from);
				}



				loadedMatrix[i][j] = std::stof(matrixElement);
				

			}
			std::getline(in, s);//vado alla riga successiva
		}//FOR


		return loadedMatrix;
	}



	void Logger::saveData(std::string data, std::string filename) {
		static std::ofstream log;
		if (FIRST_DATAPROJECT_ACCESS) {
			log.open(STOREDDATADIR + filename);
			
			log.clear();
			log << time_stamp() << std::endl;
			log << data << DELIMITER <<std::endl;
			log.close();
			FIRST_DATAPROJECT_ACCESS = false;
		}
		else {
			log.open(STOREDDATADIR + filename, std::ofstream::out | std::ofstream::app);
			log << data << DELIMITER << std::endl;
			log.close();
		}

	}

	bool Logger::openFile(std::string filename) {
		
			return true;

	}

	void Logger::closeFile(std::string filename) {
	
	}


	void Logger::FormatProjectData(std::string filename) {
		static std::ofstream log;
			log.open(STOREDDATADIR + filename);
			log.clear();
			log.close();
			
	}


	void Logger::saveCameraData3f(std::string cameraID, std::string cameraAttribute, GLfloat data[3], std::string filename) {

		saveData(textRendererNS::NEWLINE , filename);
		saveData(cameraID, filename);
		saveData(cameraAttribute, filename);
		saveData(floatArr3ToString(data), filename);

}
	void Logger::saveCameraData1f(std::string cameraID, std::string cameraAttribute, GLfloat data, std::string filename) {

		saveData(textRendererNS::NEWLINE, filename);
		saveData(cameraID, filename);
		saveData(cameraAttribute, filename);
		saveData(std::to_string(data), filename);

	}


	std::string Logger::floatArr3ToString(const GLfloat arr[3]) {

		std::string array{
			std::to_string(arr[0]) + " " +
			std::to_string(arr[1]) + " " +
			std::to_string(arr[2]) };

		return array;
	}
	std::string Logger::stdarray3ToString(const std::array<float,3>& arr) {

		std::string array{
			std::to_string(arr[0]) + " " +
			std::to_string(arr[1]) + " " +
			std::to_string(arr[2]) };

		return array;
	}


	
	std::string Logger::floatArr4ToString(GLfloat arr[4]) {

		std::string array{ 
			std::to_string(arr[0])+" "+
			std::to_string(arr[1])+" "+
			std::to_string(arr[2])+" "+
			std::to_string(arr[3]) };
		return array;
	}

	std::vector<std::string>* Logger::matrix44ToStringVecPoint(vmath::mat4 matrix, std::string matrixName) {

		static std::vector<std::string> string_vec;
		string_vec.clear();

	
		std::string text;

		text.append(textRendererNS::NEWLINE2+ matrixName);

		for (int i = 0; i < 4; i++) 
		{
			text.append(textRendererNS::NEWLINE);
			for (int j = 0; j < 4; j++) 
			{
				text.append(MatrixComponent[j+4*i] + std::to_string(matrix[i][j]));

			}
		}

		text.append("^^");

		
		std::string s;
		std::string::iterator c;
		//c = text.begin();
		for (c = text.begin(); c != text.end(); c++)
		{

			if (*c == '^')
			{
				string_vec.push_back(s);
				s.clear();
				continue;
			}
			s.push_back(*c);
		}

		return &string_vec;

	}




	std::string Logger::matrix44ToString(vmath::mat4 matrix, std::string matrixName) {

		std::vector<std::string>* string_vec = matrix44ToStringVecPoint(matrix, matrixName);
	
		std::string result;

		for (int i = 0; i < string_vec->size(); i++)
		{
			result.append((*string_vec)[i]);//aggiungo stringa del vettore (ovvero riga della matrice)
			result.push_back(*textRendererNS::NEWLINE.c_str());//aggiungo alla stringa il carattere per andare a capo
			//ricorda :append aggiunge una stringa ad un'altra, push_back aggiunge un carattere ad una stringa (una stringa è un vettore di caratteri)
		}
		return result;

	}



	
 
	void Logger::writeMatrixLog(vmath::mat4 mat, std::string filename) {


		files_fullpath.push_back(LOGDIR + filename);
		static std::ofstream log;
		if (FIRST_LOG_ACCESS) {
			log.open(LOGDIR + filename);
			log << time_stamp() << std::endl;
			log.open(LOGDIR + filename, std::ofstream::out | std::ofstream::app);
			for (int i = 0; i < 4; i++)
			{
				log << std::endl;
				for (int j = 0; j < 4; j++)
					log << std::to_string(mat[i][j]) << " ";
			}

			log.close();
			FIRST_LOG_ACCESS = false;
		}
		else {
			
			log.open(LOGDIR + filename, std::ofstream::out | std::ofstream::app);
			for (int i = 0; i < 4; i++) 
			{
				log << std::endl;				
				for (int j = 0; j < 4; j++)
					log << std::to_string(mat[i][j]) << " ";
			}
			
			log.close();
		}

}






void Logger::writeLog(std::string Log, std::string filename) {
	files_fullpath.push_back(LOGDIR+filename);
		static std::ofstream log;
		if (FIRST_LOG_ACCESS) {
			log.open(LOGDIR+filename);
			log << time_stamp() << std::endl;
			log << Log << " " << std::endl;
			log.close();
			FIRST_LOG_ACCESS = false;
		}
		else {
			log.open(LOGDIR + filename, std::ofstream::out | std::ofstream::app);
			log << Log <<std::endl;
			log.close();
		}

	}





void Logger::writeLog(std::string Log, int i1, int i2, int i3, std::string filename ) {
	files_fullpath.push_back(LOGDIR + filename);
	static std::ofstream log;
	if (FIRST_LOG_ACCESS) {
		log.open(LOGDIR + filename);
		log << time_stamp() << std::endl;
		log << Log << " |" <<i1<<" |"<<i2<<" |"<<i3<< std::endl;
		log.close();
		FIRST_LOG_ACCESS = false;
	}
	else {
		log.open(LOGDIR + filename, std::ofstream::out | std::ofstream::app);
		log << Log << " |" << i1 << " |" << i2 << " |" << i3 <<std::endl;
		log.close();
	}

}





	void Logger::writeLog(std::string Log, std::string Log2, std::string filename) {
		static std::ofstream log;
		files_fullpath.push_back(LOGDIR + filename);
		if (isFirstWrite.find(filename) == isFirstWrite.end()) {
			log.open(LOGDIR + filename);
			log.clear();
			log << time_stamp() << std::endl;
			log << Log << " : " << Log2 << std::endl;
			log.close();
			isFirstWrite[filename] = true;
		}	else {
			log.open(LOGDIR + filename, std::ofstream::out | std::ofstream::app);
			log << Log << " : " << Log2 <<std::endl;
			log.close();
		}

	}


	void Logger::writeLog(std::string Log, std::string Log2, int i, std::string filename) {
		files_fullpath.push_back(LOGDIR + filename);
		static std::ofstream log;
		if (FIRST_LOG_ACCESS) {
			log.open(LOGDIR + filename);
			log << time_stamp() << std::endl;
			log << Log << " : " << i << " " << Log2 << std::endl;
			log.close();
			FIRST_LOG_ACCESS = false;
		}
		else {
			log.open(LOGDIR+filename, std::ofstream::out | std::ofstream::app);
			log << Log << " : " << i << " " << Log2 << std::endl;
			log.close();
		}


	}






	void Logger::writeLog(std::string Log, int i, std::string Log2, std::string filename ) {
		files_fullpath.push_back(LOGDIR + filename);
		static std::ofstream log;
		if (FIRST_LOG_ACCESS) {
			log.open(LOGDIR + filename);
			log << time_stamp() << std::endl;
			log << Log << " : " << i << " " << Log2 <<std::endl;
			log.close();
			FIRST_LOG_ACCESS = false;
		}
		else {
			log.open(LOGDIR + filename, std::ofstream::out | std::ofstream::app);
			log << Log << " : " << i << " " << Log2 << std::endl;
			log.close();
		}

	}

	
	void Logger::writeLogSIS(std::string Log, int i, std::string filename) {
		files_fullpath.push_back(LOGDIR + filename);
		static std::ofstream log;
		if (FIRST_LOG_ACCESS) {
			log.open(LOGDIR + filename);
			log << time_stamp() << std::endl;
			log << Log << " : " << i << " " << std::endl;
			log.close();
			FIRST_LOG_ACCESS = false;
		}
		else {
			log.open(LOGDIR + filename, std::ofstream::out | std::ofstream::app);
			log << Log << " : " << i << " " << "                |" << time_stamp() << std::endl;
			log.close();
		}

	}




	char * Logger::stringToChar(std::string word)
	{
		char * arr = new char[word.length()];

		int i = 0;
		for (i; i < word.length(); i++)
			arr[i] = word[i];
		arr[i] = '\0';

		return arr;
	}

	void Logger::clean() {

		
		exploreFolder(LOGDIR);

		for(std::vector<std::string>::iterator it = log_list.begin(); it < log_list.end(); it++)
		{
			std::string filename = *it;
			std::string fullpath = LOGDIR + filename;
			int status = std::remove(fullpath.c_str());

			if (status == 0)
			{
				std::cout << "file " << filename << " deleted successfully..!!\n";
			}
			else
			{
				std::cout << "Unable to delete file " << filename << "\n";
				perror("Error Message ");
			}
		}
	}


	void Logger::exploreFolder(std::string dir) {
		//funzione che mette nel vettore log_list i nomi di tutti i file/cartelle presenti nella directory
			
			WIN32_FIND_DATA data;
			HANDLE hFind = FindFirstFile(dir.append("*.*").c_str(), &data);      // DIRECTORY
			int i = 0;
			if (hFind != INVALID_HANDLE_VALUE) {
				do {
					char *c = data.cFileName;
					std::string filename(c);
					if (std::strcmp(filename.c_str(), ".") != 0 && std::strcmp(filename.c_str(), "..") != 0)
					{
						log_list.push_back(filename);
						std::cout << log_list.at(i++) << std::endl;
					}
				} while (FindNextFile(hFind, &data));
				FindClose(hFind);
			}
	}

	void Logger::exploreFolder(std::string dir, std::vector<std::string>& fileList) 
	{
		//funzione che mette nel vettore log_list i nomi di tutti i file/cartelle presenti nella directory

		WIN32_FIND_DATA data;
		HANDLE hFind = FindFirstFile(dir.append("*.*").c_str(), &data);      // DIRECTORY
		int i = 0;
		if (hFind != INVALID_HANDLE_VALUE) 
		{
			do {
				char *c = data.cFileName;
				std::string filename(c);
				if (std::strcmp(filename.c_str(), ".") != 0 && std::strcmp(filename.c_str(), "..") != 0)
				{
					fileList.push_back(filename);
					std::cout << fileList.at(i++) << std::endl;
				}
			} while (FindNextFile(hFind, &data));
			FindClose(hFind);
		}
	}




	void Logger::initLogger() {

		clean();
		writeLog("  INITIALIZATION  ");
		writeLog("Application directory : ", Application::application_root_dir, "log.txt");
	}


	//---------------------------------------------------


	std::tm Logger::localtime_xp(std::time_t timer)
	{
		std::tm bt{};
#if defined(__unix__)
		localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
		localtime_s(&bt, &timer);
#else
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		bt = *std::localtime(&timer);
#endif
		return bt;
	}

	// default = "YYYY-MM-DD HH:MM:SS"
	std::string Logger::time_stamp(const std::string& fmt)
	{
		auto bt = localtime_xp(std::time(0));
		char buf[64];
		return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
	}

	


}//namespace