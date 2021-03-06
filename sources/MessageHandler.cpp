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

	fifo_ = std::fopen(pathToFifo.c_str(), "r+");
	if ( fifo_ == nullptr ) {
		throw Exception("file '" + pathToFifo + "' can not open: " + Exception::getSystemErrorMessage());
	}//end of if 
	setbuf(fifo_, nullptr); // отменяюем буферизацию
}//end of MessageHandler::MessageHandler()

MessageHandler::~MessageHandler() {
	std::fclose(fifo_);

	for (const auto it: clientHandles_) {
		std::fclose(it.second);
	}
}//end of  MessageHandler::~MessageHandler()

Command* MessageHandler::getRequest() noexcept {
	static char buf[MAX_SIZE] = {0};

	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(fileno(fifo_), &readset);
	if ( ::select(fileno(fifo_)+1, &readset, NULL, NULL, NULL) < 0 ) {
		return nullptr;
	}//end of if 

	std::fgets(buf, sizeof(buf), fifo_);
	std::string message(buf);

	log_->write("recive message: " + message, Logger::ADD_TIME | Logger::ADD_LN);

	//если получили такое сообщение, то вероятнее всего работа закончена
	if ( message == "quit\n" ) {
		return nullptr;
	}//end of if 

	std::string clientId;
	std::string commandId;
	std::vector<std::string> args;

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

	FILE* out;
	auto it = clientHandles_.find(cm->getClientId());
	if ( it != clientHandles_.end() ) {
		out = it->second;
	} else {
		out = createConnectionWithNewClient(cm->getClientId());
	} //end of if

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

	message += "\n";

	std::fputs(message.c_str(), out);
	std::fflush(out);

	log_->write("sent message: " + message + "for " + cm->getClientId(), Logger::ADD_TIME | Logger::ADD_LN);
	delete cm;

}//end of void MessageHandler::giveAnswer()

bool MessageHandler::getClientIdFromMessage(const std::string& message, std::string& clientId) {
	clientId.clear();

	size_t pos = message.find_first_of(CLIENT_ID_PREFIX);
	if ( pos == std::string::npos ) {
		return false;
	}//end of if 

	for (size_t i = pos; (message[i] != ' ') && ( message[i] != '\n') && (i < message.size()); ++i) {
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

	for (size_t i = pos+1; (message[i] != ' ') && ( message[i] != '\n') && (i < message.size()); ++i) {
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
		if ( message[i] != ' '  && message[i] != '\n') {
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

FILE* MessageHandler::createConnectionWithNewClient(const std::string& clientId) {
	FILE* connection = nullptr;
	std::string pathToFifo = PREFIX + clientId;
	struct stat sb;
	if ( ::stat(pathToFifo.c_str(), &sb) != 0 ) {
		if (::mkfifo(pathToFifo.c_str(), 0600) < 0) {
			log_->write("fifo '" + pathToFifo + "'can not be created: " + Exception::getSystemErrorMessage(), Logger::ADD_TIME | Logger::ADD_LN);
		}
	}//end of if 

	connection = std::fopen(pathToFifo.c_str(), "w");
	if ( connection == nullptr) {
		log_->write("file '" + pathToFifo + "' can not open: " + Exception::getSystemErrorMessage(), Logger::ADD_TIME | Logger::ADD_LN);
	}//end of if 

	::setbuf(connection, nullptr);

	clientHandles_.insert(std::pair<std::string, FILE*>(clientId, connection));

	return connection;
}//end of FILE* MessageHandler::createConnectionWithNewCLient()

} /* LedControl */ 
