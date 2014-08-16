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

TEST_F(MessageHandlerTest, should_read_message_from_pipe){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 

	char m1[] = "pid123 set-state on";
	char m2[] = "pid456 set-state off";
	pid_t pid = ::fork();

	if(pid == 0){
		std::ofstream out("/tmp/led1", std::fstream::out);
		out << m1 << std::endl;
		out << m2 << std::endl;
		::_exit(0);
	} else {
		std::string message = mh.getRequest();
		EXPECT_STREQ(m1, message.c_str());

		message = mh.getRequest();
		EXPECT_STREQ(m2, message.c_str());
	}
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_TEST_H_ */
