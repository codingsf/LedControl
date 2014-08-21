#include "Server.h"


namespace LedControl {

const std::string Server::LAST_DATA = "last_data";

class Server::SignalHandler {
/*
 * класс, реализующий корректное завершение потоков в случае прихода сигнала
 * Реализован в виде простейшего синглтона.
 * В целом работа класса сводится к рассылке сообщений об окончании работы в
 * зарегестрированные каналы.
 */
public:
	~SignalHandler (){}

	static SignalHandler* instance() {
		static SignalHandler sh;
		return &sh;
	}

	/*
	 * зарегестрировать канал.
	 * Принимаемые параметры:
	 * - fifo - дескриптор канала
	 */
	void registerPipe(FILE* fifo){
		trackPipes_.push_back(fifo);
	}

	/*
	 * проверить пришел ли сигнал об окончании работы
	 */
	bool isFinished() {
		return isFinished_;
	}

	/*
	 * разослать сообщения об окончании работы в зарегестрированные каналы
	 */
	void finishWork(){
		isFinished_ = true;
		for (auto it: trackPipes_) {
			std::fputs("quit\n", it);
			std::fflush(it);
		}
	}

private:
	SignalHandler (): isFinished_(false) {}

	volatile bool isFinished_; //работа закончена
	std::vector<FILE*> trackPipes_; //отслеживаемые каналы. На все каналы из этого массива будет передаваться сщщбщение "quit\n"
};//end of declaration class Server::SignalHandler


Server::Server(MessageHandler* mh, Logger* log): sh_(SignalHandler::instance()), numberOfThreads_(0), mh_(mh), log_(log) {
	//маскируем все сигналы кроме SIGINT и устанавливаем обработчик
	sigset_t sset;
	::sigfillset(&sset);
	::sigdelset(&sset, SIGINT);
	::sigprocmask(SIG_SETMASK, &sset, nullptr);
	struct sigaction sa;
	sa.sa_handler = handleSignal;
	::sigaction(SIGINT, &sa, 0);

}//end of Server::Server()

void Server::getRequests() noexcept {
	static LastDataCommand lastCommand(LAST_DATA);
	while ( !sh_->isFinished() ) {
		Command* cm = mh_->getRequest();
		if ( cm != nullptr ) {
			taskQueue_.enqueue(cm);
		}//end of if 
	}//end of while

	for (size_t i = 0; i < numberOfThreads_ - 1; ++i) {
		taskQueue_.enqueue(&lastCommand);
	}//end of for
}//end of void Server::getRequests()

void Server::setAnswers() noexcept {
	while ( sh_->isFinished() != true ) {
		Command* cm = taskQueue_.dequeue();
		if ( cm->getClientId() != LAST_DATA ) {
			mh_->giveAnswer(cm);
		} // end of if
	}//end of while
}//end of void Server::setAnswers()

void Server::run(size_t numberOfThreads) {
	log_->write("server starting...", Logger::ADD_TIME | Logger::ADD_LN);

	//ограничиваем максимальное число потоков 10-ю
	numberOfThreads_ = numberOfThreads;
	if ( numberOfThreads_ > 10 ) {
		numberOfThreads_ = 10;
	}//end of if 

	sh_->registerPipe(mh_->getFifoDescriptor());

	if ( numberOfThreads_ > 1 ) {
		std::vector<std::thread> threads(numberOfThreads_);
		threads[0] = std::thread(&Server::getRequests, this);
		for (size_t i = 1; i < threads.size(); ++i) {
			threads[i] = std::thread(&Server::setAnswers, this);
		}//end of for

		log_->write("server started!", Logger::ADD_TIME | Logger::ADD_LN);

		std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	} else {
		while ( sh_->isFinished() != true ) {
			log_->write("server started!", Logger::ADD_TIME | Logger::ADD_LN);

			Command* cm = mh_->getRequest();
			if ( mh_ != nullptr ) {
				mh_->giveAnswer(cm);
			}//end of if 
		}//end of while
	}

	log_->write("server shutdown...", Logger::ADD_TIME | Logger::ADD_LN);
}//end of void Server::run()

void handleSignal(int) {
	Server::SignalHandler* sh = Server::SignalHandler::instance();
	sh->finishWork();
}

} /* LedControl */ 
