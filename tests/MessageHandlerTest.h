#ifndef LED_CONTROL_MESSAGE_HANDLER_TEST_H_
#define LED_CONTROL_MESSAGE_HANDLER_TEST_H_

#include "../sources/MessageHandler.h"

#include "TestFramework.h"

#include <thread>

namespace LedControl {

class MessageHandlerTest: public ::testing::Test {
public:
	virtual void SetUp() {}
	virtual void TearDown() {}
};//end of declaration class MessgeHandlerTest: public ::testing::Test

TEST_F(MessageHandlerTest, should_create_fifo){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler("led1", &cf, log); 
	struct stat sb;
	EXPECT_TRUE(::stat("/tmp/led1", &sb) == 0);
}

//TEST_F(MessageHandlerTest, should_read_messages_from_pipe_and_close_connection_on_fifo_if_recive_SIGINT){
	//Driver driver;
	//Logger* log = Logger::initialize();
	//CommandFactory cf("./tests_support/test1.conf", &driver, log);
	//MessageHandler mh("led1", &cf, log); 
	//std::thread t(&MessageHandler::getRequest, &mh);
	//t.join();

	//pid_t pid = ::vfork();
	//if(pid == 0){
		//int fd = ::open("/tmp/led1", O_WRONLY);
		//char m1[] = "pid123 test1";
		//char m2[] = "pid456 test2";
		//::write(fd, m1, sizeof(m1));
		//::write(fd, m2, sizeof(m2));
		//pid_t ppid = ::getppid();
		//::kill(ppid, SIGINT);
		//::close(fd);
		//::_exit(0);
	//} else {
		//EXPECT_FALSE(mh.queue_.empty());
		//if (!mh.queue_.empty()) {
			//MessageHandler::Task t1 = mh.queue_.get();
			//EXPECT_STREQ("pid123", t1.pid_.c_str());
			//EXPECT_STREQ("test1", t1.identifier_.c_str());

			//MessageHandler::Task t2 = mh.queue_.get();
			//EXPECT_STREQ("pid456", t1.pid_.c_str());
			//EXPECT_STREQ("test2", t1.identifier_.c_str());
		//}
	//}
//}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_TEST_H_ */
