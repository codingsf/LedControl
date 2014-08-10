#ifndef LED_CONTROL_LOGGER_H_
#define LED_CONTROL_LOGGER_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "Defines.h"
#include "Exception.h"

#include <fstream>
#include <string>

namespace LedControl {

class Logger {
/*
 * Класс, реализующий функции журнала.
 * Класс реализует простейшую форму паттрена "синглтон".
*/

public:
#ifdef __LED_CONTROL_TEST__
	friend class LoggerTest;
	FRIEND_TEST(LoggerTest, should_create_file_in_default_path);
#endif

	/*
	 * инициализировать лог.
	 * Принимаемые параметры:
	 * - pathToFile - путь к лог-файлу (может быть пустым).
	 *   В случае если передан пустой путь, создается файл с именем "led_control_log.txt"
	 *   в той же директории, где расположен исполняемый файл.
	*/
	static Logger* initialize( const std::string& pathToFile = "" );


private:
	Logger (const std::string& pathToLogFile);

	std::ofstream logFile_;
};//end of declaration class Logger

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_LOGGER_H_ */
