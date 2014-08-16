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
#ifdef __LED_CONTROL_TEST__
	friend class MessageHandlerTest;
	FRIEND_TEST(MessageHandlerTest, should_get_command_id_from_message);
	FRIEND_TEST(MessageHandlerTest, should_get_client_id_from_message);
	FRIEND_TEST(MessageHandlerTest, should_get_arguments_from_message);
#endif

	MessageHandler (const std::string& serverName, CommandFactory* cf, Logger* log);
	~MessageHandler ();

	Command* getRequest();

private:
	static const std::string PREFIX;
	static const std::string CLIENT_ID_PREFIX;

	CommandFactory* cf_;
	Logger* log_;
	std::fstream fifo_;

	bool getClientIdFromMessage(const std::string& message, std::string& clientId);
	bool getCommandIdFromMessage(const std::string& message, std::string& comId);
	void getArgumentsFromMessage(const std::string& message, std::vector<std::string>& args);
};//end of declaration class MessageHandler

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_H_ */
