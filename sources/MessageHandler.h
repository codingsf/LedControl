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
#include "UnknownCommand.h"

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
 * Обработка запросов происходит следующим образом.
 * В момент создания объекта класс MessageHandler открывается
 * канал с именем '/tmp/<serverName>' (если он не существует, то
 * создается).
 * Если из канала удается считать сообщение и оно не содержит ошибок,
 * то создается объект команды.
 * Если задана команда, то она выполняется, а результат ее выполения
 * записывается в канал '/tmp/<clientId>' (если он не существовал, то создается)
 *
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

	/*
	 * Получить запрос:
	 * Возвращаемое значение:
	 * - Указатель на объект конкретной команды. Может быть равен nullptr если
	 *   в полученном запросе и передан ID клиента
	 *   Примечание:
	 *   Вместе с указателем передается и владение
	 */
	Command* getRequest() noexcept;

	/*
	 * выдать ответ
	 * Принимаемые параметры:
	 * - cm - команда, результат выполения которой надо вернуть
	 * Примичание:
	 * Функция открывает канал с именем '/tmp/<clientId>' 
	 * (если он не сущестовал, то создает его) и записывает туда результат выполения команды
	 */
	void giveAnswer(Command* cm) noexcept;

private:
	static const std::string PREFIX;
	static const std::string CLIENT_ID_PREFIX;

	CommandFactory* cf_;
	Logger* log_;
	std::fstream fifo_;
	//std::map

	bool getClientIdFromMessage(const std::string& message, std::string& clientId);
	bool getCommandIdFromMessage(const std::string& message, std::string& comId);
	void getArgumentsFromMessage(const std::string& message, std::vector<std::string>& args);
};//end of declaration class MessageHandler

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_H_ */
