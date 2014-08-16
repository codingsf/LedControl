#include "MessageHandler.h"

#include <iostream>

namespace LedControl {

const std::string MessageHandler::PREFIX = "/tmp/";

MessageHandler::MessageHandler(const std::string& serverName, CommandFactory* cf, Logger* log): cf_(cf), log_(log), isFinished_(false) {
	log_->write("server starting...", Logger::ADD_TIME | Logger::ADD_LN);

	//создаем файл fifo, если его еще нет и открываем его
	std::string pathToFifo = PREFIX + serverName;
	struct stat sb;
	if ( ::stat(pathToFifo.c_str(), &sb) != 0 ) {
		if (::mkfifo(pathToFifo.c_str(), 0600) < 0) {
			throw Exception(Exception::getSystemErrorMessage());
		}
	}//end of if 

	mainDesc_ = ::open(pathToFifo.c_str(), O_RDWR);
	if(mainDesc_ < 0) {
		throw Exception(Exception::getSystemErrorMessage());
	}

	log_->write("server started!", Logger::ADD_TIME | Logger::ADD_LN);

	//устанавливаем способы обработки сигналов
	//sigset_t sset;
	//::sigfillset(&sset);
	//::sigdelset(&sset, SIGINT);
	//::sigprocmask(SIG_SETMASK, &sset, 0);
	//struct sigaction sa;
	//SignalHandler sh(this);
	////sa.sa_handler = &sh;
	//::sigaction(SIGINT, &sa, 0);
}//end of MessageHandler::MessageHandler()

void MessageHandler::getRequest() {

}//end of void MessageHandler::getRequest()

MessageHandler::~MessageHandler() {
	::close(mainDesc_);
}//end of  MessageHandler::~MessageHandler()

} /* LedControl */ 
