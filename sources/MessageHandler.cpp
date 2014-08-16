#include "MessageHandler.h"

namespace LedControl {

const std::string MessageHandler::PREFIX = "/tmp/";

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

std::string MessageHandler::getRequest() {
	std::string buf;
	std::getline(fifo_, buf);

	return buf;
}//end of void MessageHandler::getRequest()

MessageHandler::~MessageHandler() {
	fifo_.close();
}//end of  MessageHandler::~MessageHandler()

} /* LedControl */ 
