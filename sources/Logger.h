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
 * Каждая операция записи в лог происходит с захватом мьютекса. Однако
 * нет гарантии, что между двумя подряд идущими записями из одного потока
 * не вклинится запись из другого.
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

	static const int ADD_TIME = 1;
	static const int ADD_LN = 2;

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
	 * Принимаемые параметры:
	 * - message - сообщение для записи
	*/
	template<class T> void addMessage(const T& message);

	/*
	 * добавить сообщение в лог
	 * Принимаемые параметры:
	 * - message - сообщение для записи
	 * - flags - флаги. Параметр может принимать значение от 1 до 3.
	 *   Если установлен флаг ADD_TIME, то перед сообщением в лог добавится текущее время.
	 *   Если установлен флаг ADD_LN, то в конце сообщения в добавится символ перевода строки.
	*/
	template<class T> void addMessage(const T& message, int flags);

private:
	Logger (const std::string& pathToLogFile);

	std::ofstream logFile_;
	std::mutex m_;
};//end of declaration class Logger

template<class T> void Logger::addMessage(const T& message) {
	std::lock_guard<std::mutex> guard(m_);
	logFile_ << message;
}//end of template<class T> void addMessage()

template<class T> void Logger::addMessage(const T& message, int flags) {
	std::string currTime = "";
	std::string ln = "";
	if (flags & ADD_TIME) {
		time_t t;
		struct tm *timeinfo;
		std::time(&t);
		timeinfo = std::localtime(&t);
		char strTime[100];
		std::strftime(strTime, 100, "%m-%d-%y %R", timeinfo);
		currTime = std::string("[") + std::string(strTime) + std::string("]");
	} //end of if

	if ( flags & ADD_LN ) {
		ln = "\n";
	}//end of if 

	std::lock_guard<std::mutex> guard(m_);
	logFile_ << currTime << " " << message << ln;
}//end of template<class T> void Logger::addMessage()

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_LOGGER_H_ */
