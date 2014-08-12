#ifndef LED_CONTROL_COMMAND_FACTORY_H_
#define LED_CONTROL_COMMAND_FACTORY_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "Command.h"
#include "Driver.h"
#include "Exception.h"

#include <map>

namespace LedControl {

class CommandFactory {
/*
 * Данный класс предназначен для создания объектов конкретных
 * команд по заданному идентификатору.
 * Классы, реализующие конкретные команды, должны содержаться
 * в отдельных модулях, собранных в виде динамических библиотек.
 * Каждая такая библиотека должна содержать функцию Create(),
 * возвращающую указатель на абстрактный класс Command.
 * Первоначальная загрузка идентификаторов и соответствующих путей
 * к динамическим библиотекам конкретных команд производится из
 * конфигурационного файла.
 * Конфигурационный файл представляет из себя набор строк, состоящих
 * из символов латинского алфавита и символов '/' (для путей)
 * и разделенных символом перевода строки.
 * Не четные строки содержат идентификаторы.
 * Четные - пути к динамическим библиотекам.
*/

public:
	explicit CommandFactory (Driver* reciver);
	~CommandFactory ();

	/*
	 * создать объект конкретной команды.
	 * Принимаемые параметры:
	 * - identifier - идентификатор команды
	 * Возвращаемый параметр:
	 * указатель на конкретную команду. Может быть нулевым,
	 * если команда не найдена.
	*/
	Command* create(const std::string& identifier) const;
private:
	Driver* reciver_;
	std::map<std::string, Command*> commandList_;
};//end of declaration class CommandFactory

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_COMMAND_FACTORY_H_ */

