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

Command* MessageHandler::getRequest() noexcept {
	std::string message;
	std::string clientId;
	std::string commandId;
	std::vector<std::string> args;
	std::getline(fifo_, message);
	if (!getClientIdFromMessage(message, clientId)) {
		return nullptr;
	}

	if (!getCommandIdFromMessage(message, commandId)) {
		Command* uc = new UnknownCommand;
		uc->setClientId(clientId);
		args.push_back("no command identifier");
		uc->setArguments(args);
		return uc;
	}

	getArgumentsFromMessage(message, args);

	Command* cm = nullptr;
	try {
		cm = cf_->create(commandId, clientId, args);
	} catch (const Exception& e) {
		Command* uc = new UnknownCommand;
		uc->setClientId(clientId);
		args.clear();
		args.push_back(e.what());
		uc->setArguments(args);
		return uc;
	}

	return cm;
}//end of void MessageHandler::getRequest()

void MessageHandler::giveAnswer(Command* cm) noexcept {
	std::string pathToFifo = PREFIX + cm->getClientId();
	struct stat sb;
	if ( ::stat(pathToFifo.c_str(), &sb) != 0 ) {
		if (::mkfifo(pathToFifo.c_str(), 0600) < 0) {
			log_->write("fifo '" + pathToFifo + "'can not be created: " + Exception::getSystemErrorMessage(), Logger::ADD_TIME | Logger::ADD_LN);
		}
	}//end of if 

	std::fstream out(pathToFifo.c_str(), std::fstream::in | std::fstream::out);
	if ( !out.is_open() ) {
		log_->write("file '" + pathToFifo + "' can not open: " + Exception::getSystemErrorMessage(), Logger::ADD_TIME | Logger::ADD_LN);
	}//end of if 

	std::string message;
	std::string result;
	bool status = cm->excute(result);
	if ( status ) {
		message += "OK";
	} else {
		message += "FAILED";
	}

	if ( !result.empty() ) {
		message += " ";
		message += result;
	}//end of if

	out << message << std::endl;
	out.close();
}//end of void MessageHandler::giveAnswer()

bool MessageHandler::getClientIdFromMessage(const std::string& message, std::string& clientId) {
	clientId.clear();

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
	comId.clear();

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
	args.clear();

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

	if ( !arg.empty() ) {
		args.push_back(arg);
	}//end of if 
}//end of void MessageHandler::getArgumentsFromMessage()

} /* LedControl */ 
