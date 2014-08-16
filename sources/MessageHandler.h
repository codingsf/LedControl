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

public:
//#ifdef __LED_CONTROL_TEST__
	//friend class MessageHandlerTest;
	//FRIEND_TEST(MessageHandlerTest, should_read_messages_from_pipe_and_close_connection_on_fifo_if_recive_SIGINT);
//#endif

	MessageHandler (const std::string& serverName, CommandFactory* cf, Logger* log);
	~MessageHandler ();

	void getRequest();

private:
	static const std::string PREFIX;

	CommandFactory* cf_;
	Logger* log_;
	int mainDesc_; //дескриптор главного канала. Именно в этот канал клиенты будут посылать сообщения
};//end of declaration class MessageHandler

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_H_ */
