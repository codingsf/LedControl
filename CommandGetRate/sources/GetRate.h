#ifndef LED_CONTROL_COMMAND_GET_RATE_H_
#define LED_CONTROL_COMMAND_GET_RATE_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "../../sources/Command.h"
#include "../../sources/Driver.h"
#include "../../sources/Exception.h"

#include <iostream>

class CommandGetRate: public LedControl::Command {
/*
 * класс, реализующий передачу команды драйверу светодиода
*/
public:
	CommandGetRate(const CommandGetRate&) = delete;
	CommandGetRate& operator=(const CommandGetRate&) = delete;
	CommandGetRate(CommandGetRate&&) = delete;
	CommandGetRate& operator=(CommandGetRate&&) = delete;

	/*
	 * может генерировать ислючения типа LedControl::Exception
	 */
	explicit CommandGetRate (LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments);

	~CommandGetRate () {}

	/*
	 * установить новый ID клиента 
	 * Принимаемые парамеры:
	 * newClientId - ID нового клиента
	 */
	void setClientId(const std::string& newClientId){
		clientId_ = newClientId;
	}

	/*
	 * получить ID клиента
	 */
	const std::string& getClientId() const {
		return clientId_;
	}

	/*
	 * установить аргументы
	 * Примечание:
	 * в случае если переданы не подходящие аргументы
	 * будет сгенерировано исключение типа Ledcontrol::Exception
	 */
	void setArguments(const std::vector<std::string>& newArguments);

	/*
	 * выполнить команду
	 * Принимаемые параметры:
	 * - result - сюда будет записан результат выполения
	 * Возвращаемые параметры:
	 * true если команда выполнилась успешно
	 */
	bool excute(std::string& result);
private:
	LedControl::Driver* reciver_;
	std::string clientId_;
	std::vector<std::string> arguments_;
};//end of declaration class CommandGetRate: public Command

extern "C" LedControl::Command* create(LedControl::Driver* reciver, const std::string& clientId, const std::vector<std::string>& arguments) {
	return new CommandGetRate(reciver, clientId, arguments);
}

#endif /* end of include guard: LED_CONTROL_COMMAND_GET_RATE_H_ */
