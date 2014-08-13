#ifndef LED_CONTROL_MESSAGE_QUEUE_H_
#define LED_CONTROL_MESSAGE_QUEUE_H_
/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include <deque>
#include <mutex>

template<class T> class MessageQueue {
/*
 * Данный класс реализует очередь с поддержкой многопоточности
 */
public:

	/*
	 * добавить сообщение(задачу) в очередь
	 */
	void put(const T& item){
		std::lock_guard<std::mutex> guard(lock_);
		queue_.push_back(item);
	}

	/*
	 * извлечь задачу из очереди
	 */
	const T& get(){
		std::lock_guard<std::mutex> guard(lock_);
		return queue_.pop_front();
	}
	
	/*
	 * проверить пуста ли очередь
	 */
	bool empty(){
		std::lock_guard<std::mutex> guard(lock_);
		return queue_.empty();
	}

private:
	std::deque<T> queue_;
	std::mutex lock_;
};

#endif /* end of include guard: LED_CONTROLLER_MESSAGE_QUEUE_H_ */

