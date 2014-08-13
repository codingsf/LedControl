#ifndef LED_CONTROL_COMMAND_FACTORY_H_
#define LED_CONTROL_COMMAND_FACTORY_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "Command.h"
#include "Driver.h"
#include "Logger.h"

#include <map>
#include <fstream>

#include <dlfcn.h>

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
#ifdef __LED_CONTROL_TEST__
	friend class CommandFactoryTest;
	FRIEND_TEST(CommandFactoryTest, should_fill_command_list);
#endif

	/*
	 * Принимаемые параметры:
	 * - pathToConfigFile - путь к конфигурационному файлу
	 * - reciver - получатель команд
	 * - log
	 * Примечание: возможна генерация исключений типа LedControl::Exception
	 */
	explicit CommandFactory (const std::string& pathToConfigFile, Driver* reciver, Logger* log);
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
	static const std::string CREATE_FUNC_NAME; //имя функции, создающей объект класса конкретной команды
	Driver* reciver_; //получатель команд
	Logger* log_;
	std::map<std::string, Command*> commandList_;
	std::vector<void*> handles_; //дескрипторы открытых библиотек

	/*
	 * получить данные из конфигурационного файла
	 * Принимаемые параметры:
	 * config - поток вывода из конфигурационного файла.
	 * Примечания:
	 * функция может генерировать исключения типа LedControl::Exception
	 */
	void getDataFromConfigFile(std::ifstream& config);
};//end of declaration class CommandFactory

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_COMMAND_FACTORY_H_ */

