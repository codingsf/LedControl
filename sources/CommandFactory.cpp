#include "CommandFactory.h"

namespace LedControl {

const std::string CommandFactory::CREATE_FUNC_NAME = "create";

CommandFactory::CommandFactory(const std::string& pathToConfigFile, Driver* reciver, Logger* log): reciver_(reciver), log_(log) {
	std::ifstream config(pathToConfigFile);
	if ( !config.is_open() ) {
		throw Exception(Exception::getSystemErrorMessage());
	}//end of if 

	getDataFromConfigFile(config);
}//end of CommandFactory::CommandFactory()

CommandFactory::~CommandFactory() {
	std::map<std::string, Command*>::iterator begin = commandList_.begin();
	std::map<std::string, Command*>::iterator end = commandList_.end();
	std::map<std::string, Command*>::iterator it;
	for ( it = begin; it != end; ++it) {
		delete it->second;
	}//end of for

	for (size_t i = 0; i < handles_.size(); ++i) {
		dlclose(handles_[i]);
	}//end of for

}//end of  CommandFactory::~CommandFactory()

Command* CommandFactory::create(const std::string& identifier) const {
	auto it = commandList_.find(identifier);
	if ( commandList_.find(identifier) != commandList_.end() ) {
		return it->second;
	}//end of if 

	return nullptr;
}//end of Command* CommandFactory::create()

void CommandFactory::getDataFromConfigFile(std::ifstream& config) {
#ifdef __LED_CONTROL_DEBUG__
#define DGetDataFromConfigFile_ 1
#else
#define DGetDataFromConfigFile_ 0
#endif

	std::string commandName;
	std::string pathToLib;
	while (std::getline(config, commandName)) {
		std::getline(config, pathToLib);

		if ( DGetDataFromConfigFile_ ) {
			PRINTVAL(log_, commandName)
			PRINTVAL(log_, pathToLib)
		}//end of if 

		if ( commandName.empty() || pathToLib.empty() ) {
			throw Exception("invalid config file: data is not complete");
		}//end of if 

		void* libHandle = dlopen(pathToLib.c_str(), RTLD_LAZY);
		if ( libHandle == 0 ) {
			throw Exception("invalid config file: " + std::string(dlerror()));
		}//end of if 

		Command* (*createFunc) () = reinterpret_cast<Command* (*) ()>(dlsym(libHandle, CREATE_FUNC_NAME.c_str()));

		if ( createFunc == 0 ) {
			throw Exception ("invalid config file or lib");
		}//end of if 

		Command* command = (*createFunc)();

		commandList_.insert(std::pair<std::string, Command*>(commandName,command));
		handles_.push_back(libHandle);

		commandName.clear();
		pathToLib.clear();
	}//end of while
}//end of void CommandFactory::getDataFromConfigFile()

} /* LedControl */ 
