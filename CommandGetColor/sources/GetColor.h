#ifndef LED_CONTROL_COMMAND_GET_COLOR_H_
#define LED_CONTROL_COMMAND_GET_COLOR_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "../../sources/Command.h"
#include "../../sources/Driver.h"
#include "../../sources/Exception.h"

#include <iostream>

class CommandGetColor: public LedControl::Command {
/*
 * класс, реализующий передачу команды драйверу светодиода
*/
public:
	CommandGetColor(const CommandGetColor&) = delete;
	CommandGetColor& operator=(const CommandGetColor&) = delete;
	CommandGetColor(CommandGetColor&&) = delete;
	CommandGetColor& operator=(CommandGetColor&&) = delete;

	/*
	 * может генерировать ислючения типа LedControl::Exception
	 */
	explicit CommandGetColor (LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments);

	~CommandGetColor () {}

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
};//end of declaration class CommandGetColor: public Command

extern "C" LedControl::Command* create(LedControl::Driver* reciver, const std::string& clientId, const std::vector<std::string>& arguments) {
	return new CommandGetColor(reciver, clientId, arguments);
}

#endif /* end of include guard: LED_CONTROL_COMMAND_GET_COLOR_H_ */
