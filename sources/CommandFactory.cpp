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
	for (auto it: commandList_) {
		delete it.second;
	}

	for (auto it: handles_) {
		dlclose(it.second);
	}//end of for

}//end of  CommandFactory::~CommandFactory()

Command* CommandFactory::create(const std::string& identifier, const std::string& clientId, const std::vector<std::string>& arguments) {
	auto it = commandList_.find(identifier);
	if ( it != commandList_.end() ) {
		Command* cm = it->second;
		cm->setClientId(clientId);
		cm->setArguments(arguments);

		return cm;
	}//end of if 

	auto handle = handles_.find(identifier);
	if ( handle == handles_.end() ) {
		return nullptr;
	}//end of if 

	pCreate createFunc = reinterpret_cast<pCreate>(dlsym(handle->second, CREATE_FUNC_NAME.c_str()));
	if ( createFunc == 0 ) {
		throw Exception ("invalid config file or lib");
	}//end of if 

	Command* cm = (*createFunc)(reciver_, clientId, arguments);
	commandList_.insert(std::pair<std::string, Command*>(identifier, cm));

	return cm;
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

		handles_.insert(std::pair<std::string, void*>(commandName, libHandle));

		commandName.clear();
		pathToLib.clear();
	}//end of while
}//end of void CommandFactory::getDataFromConfigFile()

} /* LedControl */ 
