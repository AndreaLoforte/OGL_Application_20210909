#ifndef H_LOG
#define H_LOG

#include<string>
#include<fstream>
#include<application.h>
#include<vector>
#include<direct.h>
#include<windows.h>
#include<map>
namespace fpcameraNS {
	class Transformation;
}



namespace exceptionNS{

	class TestClass : public std::runtime_error
	{
	public:
		TestClass(char const* const message) throw();
		char const* what() const throw();
	};



	
}//namespace exception




namespace logNS {

#define DELIMITER "NEWOBJECT"	



	class Logger {
	public:
		static std::map<std::string, bool> isFirstWrite;
		static std::string LOGDIR;
		static std::string STOREDDATADIR;
		static std::string PROJECTDIR;
		static std::string PROJECTMAINDIR;
		static bool FIRST_LOG_ACCESS;
		static bool FIRST_DATAPROJECT_ACCESS;
		static std::vector<std::string> files_fullpath;
		static std::vector<std::string> log_list;
		static std::vector<std::string> MatrixComponent;
		static std::ofstream storedDatafile;
		static std::string projectsListFilename;

	
		Logger() {

			MatrixComponent.push_back(" xx : ");
			MatrixComponent.push_back("	xy : ");
			MatrixComponent.push_back("	xz : ");
			MatrixComponent.push_back("	xw : ");
			MatrixComponent.push_back(" yx : ");
			MatrixComponent.push_back("	yy : ");
			MatrixComponent.push_back("	yz : ");
			MatrixComponent.push_back("	yw : ");
			MatrixComponent.push_back(" zx : ");
			MatrixComponent.push_back("	zy : ");
			MatrixComponent.push_back("	zz : ");
			MatrixComponent.push_back("	zw : ");
			MatrixComponent.push_back(" wx : ");
			MatrixComponent.push_back("	wy : ");
			MatrixComponent.push_back("	wz : ");
			MatrixComponent.push_back("	ww : ");

		}

		static void writeLog(std::string, int, int, int, std::string = "log.txt");
		static void writeLog(std::string, std::string, int, std::string);
		static void writeLog(std::string, std::string, std::string);
		static void writeLog(std::string, std::string = "log.txt");
		static void writeLog(std::string, int i, std::string, std::string = "log.txt");
		static void saveData(std::string data, std::string filename);
		static std::tm localtime_xp(std::time_t time);
		static std::string time_stamp(const std::string& fmt = "%F %T");
		static void clean();
		static char* stringToChar(std::string);
		static void initLogger();
		static void exploreFolder(std::string);
		static void writeLogSIS(std::string, int i, std::string);
		//static void LoadData(ApplicationObject*,std::string filename);
		static vmath::mat4 LoadMatrix(std::ifstream&);
		static void FormatProjectData(std::string filename);
		static std::vector<std::string>* matrix44ToStringVecPoint(vmath::mat4, std::string);
		static std::string matrix44ToString(vmath::mat4, std::string);
		static void writeMatrixLog(vmath::mat4 mat, std::string);
		static bool openFile(std::string);
		static void closeFile(std::string);
		static void saveCameraData3f(std::string, std::string, GLfloat[3], std::string);
		static void saveCameraData1f(std::string, std::string, GLfloat, std::string);
		static std::string  floatArr4ToString(GLfloat[4]);
		static std::string  floatArr3ToString(const GLfloat[3]);
		static std::string stdarray3ToString(const std::array<float, 3>&);
		static void saveMatrix44(std::ofstream&, vmath::mat4&);
		static void loadMatrix44(std::ifstream&, vmath::mat4&, std::size_t, std::size_t);
		static int checkIfstream(std::ifstream&);
		static int safeIFread(std::ifstream&,std::string&);
		static void exploreFolder(std::string dir, std::vector<std::string>& fileList);
		static bool deleteProjectData(const std::string& projectName);
		static void updateProjectsListFile();
	};


}
#endif