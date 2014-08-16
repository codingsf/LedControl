#ifndef LED_CONTROL_COMMAND_H_
#define LED_CONTROL_COMMAND_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include <vector>
#include <string>

namespace LedControl {

class Command {
/*
 * абстрактный класс, представляющий интерфейс для конкретных команд
*/
public:
	virtual ~Command (){}

	/*
	 * установить новый ID клиента 
	 * Принимаемые парамеры:
	 * newClientId - ID нового клиента
	 */
	virtual void setClientId(const std::string& newClientId) = 0;

	/*
	 * получить ID клиента
	 */
	virtual const std::string& getClientId() const = 0;

	/*
	 * установить аргументы
	 */
	virtual void setArguments(const std::vector<std::string>& newArguments) = 0;

	/*
	 * выполнить команду
	 * Принимаемые параметры:
	 * - result - сюда будет записан результат выполения
	 * Возвращаемые параметры:
	 * true если команда выполнилась успешно
	 */
	virtual bool excute(std::string& result) = 0;

protected:
	Command (){}
};//end of declaration class Command

} // LedControl

#endif /* end of include guard: LED_CONTROL_COMMAND_H_ */

