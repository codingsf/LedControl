#ifndef LED_CONTROL_MESSAGE_QUEUE_H_
#define LED_CONTROL_MESSAGE_QUEUE_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "Command.h"

#include <deque>
#include <mutex>
#include <condition_variable>

namespace LedControl {

class MessageQueue {
/*
 * Данный класс реализует потокобезопасную очередь команд 
 */
public:
	/*
	 * добавить сообщение(задачу) в очередь
	 */
	void enqueue(Command* newCommand);

	/*
	 * извлечь задачу из очереди
	 */
	Command* dequeue();
	
private:
	std::deque<Command*> queue_;
	std::mutex lock_;
	std::condition_variable dataCondition_;
};

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROLLER_MESSAGE_QUEUE_H_ */

