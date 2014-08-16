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

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_TEST_H_ */
