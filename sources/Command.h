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
	virtual bool excute(const std::vector<std::string>& arguments) = 0;

protected:
	Command (){}
};//end of declaration class Command

} // LedControl

#endif /* end of include guard: LED_CONTROL_COMMAND_H_ */

