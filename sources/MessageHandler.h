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
#include <signal.h>

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
	}; //end of struct Task

	class SignalHandler {
	public:
		SignalHandler (MessageHandler* mh): mh_(mh) {}
		~SignalHandler () {}

		//void operator()(int val){
			//mh_->finishWork();
			//val = 0;
		//}
	
	private:
		MessageHandler* mh_;
	};//end of declaration class SignalHandler

public:
#ifdef __LED_CONTROL_TEST__
	friend class MessageHandlerTest;
	FRIEND_TEST(MessageHandlerTest, should_read_messages_from_pipe_and_close_connection_on_fifo_if_recive_SIGINT);
#endif

	MessageHandler (const std::string& serverName, CommandFactory* cf, Logger* log);
	~MessageHandler ();

	void getRequest();

	void finishWork(){
		isFinished_ = true;
	}
private:
	static const std::string PREFIX;

	CommandFactory* cf_;
	Logger* log_;
	volatile bool isFinished_; //true - если работа закончена.
	int mainDesc_; //дескриптор главного канала. Именно в этот канал клиенты будут посылать сообщения
	MessageQueue<Task> queue_;
};//end of declaration class MessageHandler

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_H_ */
