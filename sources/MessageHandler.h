#ifndef LED_CONTROL_MESSAGE_HANDLER_H_
#define LED_CONTROL_MESSAGE_HANDLER_H_

/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "Defines.h"
#include "Logger.h"
#include "Exception.h"
#include "MessageQueue.h"
#include "CommandFactory.h"

#include <cstring>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace LedControl {

class MessageHandler {
/*
 * Класс MessageHandler реализует обработку сообщений,
 * поступающих от клиентов.
*/
	struct Task{ //задача
		std::string pid_; //идентификатор клиента
		std::string identifier_; //идентификатор команды
		std::vector<std::string> arguments_;
	};

public:
	MessageHandler (const std::string& serverName, CommandFactory* cf, Logger* log);
	~MessageHandler ();

private:
	static const std::string PREFIX;

	CommandFactory* cf_;
	Logger* log_;
	bool isFinished_; //true - если работа закончена.
	int mainDesc_; //дескриптор главного канала. Именно в этот канал клиенты будут посылать сообщения
	MessageQueue<Task> queue_;
};//end of declaration class MessageHandler

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_H_ */
