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
#include <ctime>
#include <mutex>

namespace LedControl {

class Logger {
/*
 * Класс, реализующий функции журнала.
 * Класс реализует простейшую форму паттрена "синглтон".
*/

public:
#ifdef __LED_CONTROL_TEST__
	friend class LoggerTest;
	FRIEND_TEST(LoggerTest, should_add_new_message_in_log);
	FRIEND_TEST(LoggerTest, should_create_file_in_default_path);
	FRIEND_TEST(LoggerTest, should_create_file_in_given_path);
	FRIEND_TEST(LoggerTest, should_open_file_with_saving_previous_data);
	FRIEND_TEST(LoggerTest, should_add_current_date_before_message);
#endif

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

	/*
	 * инициализировать лог.
	 * Принимаемые параметры:
	 * - pathToFile - путь к лог-файлу (может быть пустым).
	 *   В случае если передан пустой путь, создается файл с именем "led_control_log.txt"
	 *   в той же директории, где расположен исполняемый файл.
	*/
	static Logger* initialize( const std::string& pathToFile = "" );


	/*
	 * добавить сообщение в лог
	*/
	//template <class T> Logger& operator<<(const T& message){
		//time_t currentTime;
		//struct tm *timeinfo;
		//std::time(&currentTime);
		//timeinfo = std::localtime(&currentTime);
		//char strTime[100];
		//std::strftime(strTime, 100, "%m-%d-%y %R", timeinfo);
		//logFile_ << '[' << strTime << "] " << message << "\n";
		//return *this;
	//}
	template<class T> void addMessage(const T& message);

private:
	Logger (const std::string& pathToLogFile);

	std::ofstream logFile_;
	std::mutex m_;
};//end of declaration class Logger

template<class T> void Logger::addMessage(const T& message) {
	std::lock_guard<std::mutex> guard(m_);
	logFile_ << message;
}//end of template<class T> void addMessage()

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_LOGGER_H_ */
