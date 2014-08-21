#ifndef LED_CONTROLLER_DRIVER_H_
#define LED_CONTROLLER_DRIVER_H_

/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include <string>

namespace LedControl {

class Driver {
/*
 * Класс, релизующий непосредственное управление светодиодом камеры
 * Данные класс разработан в расчете на то, что в него поступают уже проверенные данные
*/
public:
	Driver(); 

	/*
	 * включить светодиод
	 * Принимаемые параметры:
	 * - newState - новое состояние.
	 * Может принимать значения "on", "off"
	*/
	bool setState(const std::string& newState) noexcept;

	/*
	 * запросить состояние светодиода
	 * Возвращаемое значение:
	 * результат выполнения команды или пустая строка
	*/
	const std::string& getState() const noexcept;

	/*
	 * установить цвет светодиода
	 * Принимаемые параметры:
	 * - newColor - новый цвет.
	 * Может принимать значения "red", "green", "blue".
	 *
	*/
	bool setColor(const std::string& newColor) noexcept;

	/*
	 * запросить цвет светодиода
	 * Возвращаемое значение:
	 * результат выполнения команды или пустая строка
	*/
	const std::string& getColor() const noexcept;

	/*
	 * установить частоту мерцания светодиода
	 * Принимаемые параметры:
	 * - newRate - новая частота в Герцах.
	 * Может принимать значения "0", "1", "2", "3", "4".
	*/
	bool setRate(const std::string& newRate) noexcept;

	/*
	 * запросить частоту мерцания светодиода
	 * Возвращаемое значение:
	 * результат выполнения команды или пустая строка
	*/
	const std::string& getRate() const noexcept;

	~Driver() noexcept {}
private:
	static const int MERCY_OF_FATE = 10;
	static const std::string FAIL;
	std::string state_;
	std::string color_;
	std::string rate_;
};//end of declaration class Driver

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROLLER_DRIVER_H_ */

