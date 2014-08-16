#ifndef LED_CONTROL_MESSAGE_HANDLER_TEST_H_
#define LED_CONTROL_MESSAGE_HANDLER_TEST_H_

#include "../sources/MessageHandler.h"

#include "TestFramework.h"

#include <thread>

namespace LedControl {

class MessageHandlerTest: public ::testing::Test {
public:
	std::string clientId1_;
	std::string clientId2_;
	std::string message1_;
	std::string message2_;
	std::string m1_;
	std::string m2_;

	virtual void SetUp() {
		Driver driver;
		Logger* log = Logger::initialize();
		CommandFactory cf("./tests_support/test1.conf", &driver, log);
		MessageHandler mh("led1", &cf, log); 

		m1_ = "pid123 set-state on";
		m2_ = "pid456 set-state off";
		pid_t pid = ::fork();

		if(pid == 0){
			std::ofstream out("/tmp/led1", std::fstream::out);
			out << m1_ << std::endl;
			out << m2_ << std::endl;
			::_exit(0);
		} else {
			clientId1_ = mh.getRequest(message1_);

			clientId2_ = mh.getRequest(message2_);
		}
	}

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
	EXPECT_STREQ(m1_.c_str(), message1_.c_str());

	EXPECT_STREQ(m2_.c_str(), message2_.c_str());
}

TEST_F(MessageHandlerTest, should_return_clientId){
	EXPECT_STREQ("pid123", clientId1_.c_str());

	EXPECT_STREQ("pid456", clientId2_.c_str());
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_TEST_H_ */
