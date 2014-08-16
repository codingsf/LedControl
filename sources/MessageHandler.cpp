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

std::string MessageHandler::getRequest(std::string& message) {
	message.clear();
	std::getline(fifo_, message);
	std::string clientId;
	if (!getClientIdFromMessage(message, clientId)) {
		return "";
	}

	return clientId;
}//end of void MessageHandler::getRequest()

bool MessageHandler::getClientIdFromMessage(const std::string& message, std::string& clientId) {
	size_t pos = message.find(CLIENT_ID_PREFIX);
	if ( pos == std::string::npos ) {
		return false;
	}//end of if 

	for (size_t i = pos; (message[i] != ' ') && (i < message.size()); ++i) {
		clientId += message[i];
	}//end of for

	return true;
}//end of bool MessageHandler::getClientIdFromMessage()


} /* LedControl */ 
