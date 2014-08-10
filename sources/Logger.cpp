#include "Logger.h"

namespace LedControl {

Logger::Logger(const std::string& pathToLogFile) {
	if ( pathToLogFile == "" ) { 
		logFile_.open("./led_control_log.txt", std::ofstream::out | std::ofstream::app);
	} else {
		logFile_.open(pathToLogFile, std::ofstream::out | std::ofstream::app);
	}//end of if
}//end of Logger::Logger()

Logger* Logger::initialize(const std::string& pathToLogFile) {
	static Logger logger(pathToLogFile);
	return &logger;
}//end of Logger* Logger::initialize()

} /* LedControl */ 
