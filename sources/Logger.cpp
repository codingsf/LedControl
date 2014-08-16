#include "Logger.h"

namespace LedControl {

Logger::Logger(const std::string& pathToLogFile) {
	std::string path = pathToLogFile;
	if ( path == "" ) { 
		path = "./led_control_log.txt";
	} //end of if

	logFile_.open(path, std::ofstream::out | std::ofstream::app);
	if ( !logFile_.is_open() ) {
		throw Exception("file '" + pathToLogFile + "' can not open: " + Exception::getSystemErrorMessage());
	}//end of if 
}//end of Logger::Logger()

Logger* Logger::initialize(const std::string& pathToLogFile) {
	static Logger logger(pathToLogFile);
	return &logger;
}//end of Logger* Logger::initialize()

} /* LedControl */ 
