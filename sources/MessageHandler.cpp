#include "MessageHandler.h"

namespace LedControl {

const std::string MessageHandler::PREFIX = "/tmp/";
const std::string MessageHandler::CLIENT_ID_PREFIX = "pid";

MessageHandler::MessageHandler(const std::string& serverName, CommandFactory* cf, Logger* log)
: cf_(cf),
log_(log)
{
	//создаем файл fifo, если его еще нет и открываем его
	std::string pathToFifo = PREFIX + serverName;
	struct stat sb;
	if ( ::stat(pathToFifo.c_str(), &sb) != 0 ) {
		if (::mkfifo(pathToFifo.c_str(), 0600) < 0) {
			throw Exception(Exception::getSystemErrorMessage());
		}
	}//end of if 

	fifo_.open(pathToFifo.c_str(), std::fstream::in | std::fstream::out);
	if ( !fifo_.is_open() ) {
		throw Exception("file '" + pathToFifo + "' can not open: " + Exception::getSystemErrorMessage());
	}//end of if 
}//end of MessageHandler::MessageHandler()

MessageHandler::~MessageHandler() {
	fifo_.close();
}//end of  MessageHandler::~MessageHandler()

Command* MessageHandler::getRequest() {
	std::string message;
	std::string clientId;
	std::string commandId;
	std::vector<std::string> args;
	std::getline(fifo_, message);
	if (!getClientIdFromMessage(message, clientId)) {
		return nullptr;
	}

	if (!getCommandIdFromMessage(message, commandId)) {
		return nullptr;
	}

	getArgumentsFromMessage(message, args);

	return nullptr;
}//end of void MessageHandler::getRequest()

bool MessageHandler::getClientIdFromMessage(const std::string& message, std::string& clientId) {
	size_t pos = message.find_first_of(CLIENT_ID_PREFIX);
	if ( pos == std::string::npos ) {
		return false;
	}//end of if 

	for (size_t i = pos; (message[i] != ' ') && (i < message.size()); ++i) {
		clientId += message[i];
	}//end of for

	return true;
}//end of bool MessageHandler::getClientIdFromMessage()

bool MessageHandler::getCommandIdFromMessage(const std::string& message, std::string& comId) {
	size_t pos = message.find_first_of(" ");
	if ( pos == std::string::npos ) {
		return false;
	}//end of if 

	for (size_t i = pos+1; (message[i] != ' ') && (i < message.size()); ++i) {
		comId += message[i];
	}//end of for

	return true;
}//end of bool MessageHandler::getCommandIdFromMessage()

void MessageHandler::getArgumentsFromMessage(const std::string& message, std::vector<std::string>& args) {
	size_t pos = message.find(" ");
	if ( pos == std::string::npos ) {
		return;
	}//end of if 

	pos = message.find(" ", pos+1);
	if ( pos == std::string::npos ) {
		return;
	}//end of if 

	std::string arg;
	for (size_t i = pos+1; i < message.size(); ++i) {
		if ( message[i] != ' ' ) {
			arg += message[i];
		} else {
			args.push_back(arg);
			arg.clear();
		}
	}//end of for
}//end of void MessageHandler::getArgumentsFromMessage()

} /* LedControl */ 
