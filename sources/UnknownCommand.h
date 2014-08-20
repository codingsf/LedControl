#ifndef LED_CONTROL_UNKNOWN_COMAND_H_
#define LED_CONTROL_UNKNOWN_COMAND_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
 */

#include "Command.h"

namespace LedControl {

class UnknownCommand: public Command {
/*
 * Данный класс представляет собой фиктивную команду, предназначенную для 
 * передачи ошибок клиентам.
 * Чтобы передать текст ошибки клиенту необходимо установить ID клиента и
 * скопировать текст ошибки в 0-ой элемент массива параметров.
 */
public:
	/*
	 * установить новый ID клиента 
	 * Принимаемые парамеры:
	 * newClientId - ID нового клиента
	 */
	void setClientId(const std::string& newClientId) {
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
	 */
	void setArguments(const std::vector<std::string>& newArguments) {
		arguments_ = newArguments;
	}

	/*
	 * выполнить команду
	 */
	bool excute(std::string& result) {
		result = arguments_[0];
		return false;
	}

private:
	std::string clientId_;
	std::vector<std::string> arguments_;
};//end of declaration class UnknownCommand: public Command

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_UNKNOWN_COMAND_H_ */
