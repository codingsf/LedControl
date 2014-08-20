/*
 * Данная утилита представляет собой реализацию части системы управления
 * светодиодом камеры.
 * Система построена на основе клиент серверной архитектуры.
 * Данная утилита реализует сервер.
 * В задачи утилиты входит прием и обработка запросов, ответ на запросы клиентов.
 * Архитектура утилиты основана на паттерне "Команда" и состоит классов:
 * - MessageHandler - прием и передача сообщений на обработку, выдача ответов ('инициатор' в рамках паттерна команда)
 * - Logger - ведение журнала
 * - Exception - класс исключений
 * - Command - абстрактный интерфейс команд
 * - CommandFactory - фабрика команд ( реализует загрузку динамических библиотек и создание объектов конкретных команд из них)
 * - Driver - класс, реализующий непосрественное управление светодиодом камеры ( 'получатель' в рамках паттерна команда)
 * - MessageQueue - очередь сообщений/заданий
 * - Server - класс, реализующий управление потоками
 * - UnknownComand - фиктивная команда для передачи ошибок клиентам
 * - LastDataCommand - фиктивная команда для передачи сообщения потоком об окончании работ.
 * - SetStateCommand - класс реализующий команду 'set-state' (содержится в отдельной библиотеке и подгрудается динамически)
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "Server.h"

#include <iostream>

using namespace LedControl;

void helpText(std::ostream& out){
	out << "Usage:\n:"
		<< "\tled_control -n <server name> -c <path to config file> [-l <path to log file>] [-t [number of threads]\n"
		<< "\tled_control -h\n"
		<< "Parameters:\n"
		<< "\t-h - display this text\n"
		<< "\t-n - server name, e.g. led_control -n led1 (required parameter)\n"
		<< "\t-c - path to config file, e.g. led_control -c \"/home/user/led_control.conf (required parameter)\n"
		<< "\t-t - number of threads, e.g. led_control -t 2 (by default 2)\n"
		<< "\t-l - .log file path(by default - \"./led_control_log.txt\"), e.g. led_control -l \"/home/user/log.txt\"\n"
		<< "Note. Order of parameters is not important. However if string of parameters has parameter \"-h\", that display this text and program ending\n";
}


#ifndef __LED_CONTROL_TEST__
int main(int argc, char *argv[]){
	if (argc == 1) {
		helpText(std::cout);
	}/* end of if */

	std::string pathToLogFile = "";
	std::string pathToConfigFile = "";
	std::string serverName = "";
	int commandNeeds = 0;
	size_t numberOfThreads = 2;

	for (int i = 1; i < argc; ++i) {
		if (std::strncmp(argv[i], "-c", std::strlen(argv[i])) == 0) {
			++i;
			if ( i > argc ) {
				std::cout  << "not enough parameters\n";
			}//end of if 

			pathToConfigFile = argv[i];
			++commandNeeds;
			continue;
		}/* end of if */

		if (std::strncmp(argv[i], "-t", std::strlen(argv[i])) ==0) {
			++i;
			if ( i > argc ) {
				std::cout  << "not enough parameters\n";
			}//end of if 

			numberOfThreads = std::atoi(argv[i]);
			continue;
		}/* end of if */

		if (std::strncmp(argv[i], "-l", std::strlen(argv[i])) == 0) {
			++i;
			if ( i > argc ) {
				std::cout  << "not enough parameters\n";
			}//end of if 

			pathToLogFile = argv[i];
			continue;
		}/* end of if */

		if (std::strncmp(argv[i], "-h", std::strlen(argv[i])) == 0) {
			helpText(std::cout);
			return 0;
		}/* end of if */

		if (std::strncmp(argv[i], "-n", std::strlen(argv[i])) == 0) {
			++i;
			if ( i > argc ) {
				std::cout  << "not enough parameters\n";
			}//end of if 

			serverName = argv[i];
			++commandNeeds;
			continue;
		}/* end of if */

		std::cout  << "bad parameter - " << argv[i] << "\n";
		return 1;
	}//end of for

	if (commandNeeds < 2) {
		std::cout << "necessary parameters are missing\n";
		return 1;
	}/* end of if */

	try {
		Logger* log = Logger::initialize(pathToLogFile);
		Driver reciver;
		CommandFactory cm(pathToConfigFile, &reciver, log);
		MessageHandler mh(serverName, &cm, log);
		Server s(&mh);
		s.run(numberOfThreads);
	} catch (const Exception& e) {
		std::cerr << "Error! " << e.what() << "\n";
		return 1;
	} catch (const std::exception& e) {
		std::cerr << "Error! " << e.what() << "\n";
	} catch (...) {
		return 1;
		std::cerr << "Unknown error!\n" << "\n";
		return 1;
	}

	return 0;
}
#endif
