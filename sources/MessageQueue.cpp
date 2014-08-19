#include "MessageQueue.h"

namespace LedControl {

void MessageQueue::enqueue(Command* newCommand) {
	std::lock_guard<std::mutex> guard(lock_);
	queue_.push_back(newCommand);
	dataCondition_.notify_one();
}//end of void MessageQueue::enqueue()

Command* MessageQueue::dequeue() {
	std::unique_lock<std::mutex> guard(lock_);
	dataCondition_.wait(guard, [this] {return !queue_.empty();} );
	Command* cm = queue_.front();
	queue_.pop_front();
	return cm;
}//end of Command* MessageQueue::dequeue()


} /* LedControl */ 
