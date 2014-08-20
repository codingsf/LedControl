#ifndef LAST_DATA_COMMAND_H_
#define LAST_DATA_COMMAND_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
 */

#include "Command.h"

namespace LedControl {

class LastDataCommand: public Command {
/*
 * Данный класс представляет собой фиктивную команду, сигнализирующую потоку
 * о том, что работа закончена
 */
public:

	LastDataCommand(const std::string& text): clientId_(text) {}

	/*
	 * установить новый ID клиента 
	 * Принимаемые парамеры:
	 * newClientId - ID нового клиента
	 */
	void setClientId(const std::string&) {
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
	void setArguments(const std::vector<std::string>&) {
	}

	/*
	 * выполнить команду
	 */
	bool excute(std::string& result) {
		result.clear();
		return true;
	}

private:
	std::string clientId_;
};//end of declaration class LastDataCommand: public Command

} /* LedControl */ 

#endif /* end of include guard: LAST_DATA_COMMAND_H_ */

