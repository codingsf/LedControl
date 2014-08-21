#ifndef LED_CONTROL_SERVER_H_
#define LED_CONTROL_SERVER_H_

/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
 */

#include "MessageHandler.h"
#include "MessageQueue.h"
#include "LastDataCommand.h"

#include <thread>
#include <algorithm>

#include <sys/signal.h>

namespace LedControl {

class Server {
/*
 * класс, реализующий запуск и контроль задач
 */
public:
	Server (MessageHandler* mh, Logger* log);

	/*
	 * получать запросы
	 * Примечание:
	 * функция в цикле ждет запросов от клиентов.
	 * Проверяет корректность запросов и в случае если запрос корректен
	 * помещает в очередь сообщений объект-команду
	 */
	void getRequests() noexcept;

	/*
	 * выдавать ответы:
	 * Примечание:
	 * функция ожидет поступления задач в очередь сообщений. Выполняет их,
	 * формирует ответ и посылает его клиенту.
	 */
	void setAnswers() noexcept;


	/*
	 * функция запускает работу сервера
	 * Принимаемые параметры:
	 * numberOfThreads - количество потоков.
	 * один из <numberOfThreads> потоков прослушывает канал, на который
	 * поступают сообщения от клиентов, а остальные <numberOfThreads>-1 потоков
	 * обрабатывают поступившие запросы.
	 */
	void run(size_t numberOfThreads);

private:
	friend void handleSignal(int);

	static const std::string LAST_DATA; //команда с таким ID клиента посылается, как сигнал окончания работы

	class SignalHandler;
	SignalHandler* sh_; //обработчик сигналов

	size_t numberOfThreads_;
	MessageHandler* mh_;
	Logger* log_;
	MessageQueue taskQueue_;
};//end of declaration class Server

/*
 * функция-обработчик сигнала
 */
void handleSignal(int);

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_SERVER_H_ */

