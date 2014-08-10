#ifndef LED_CONTROL_LOGGER_TEST_H_
#define LED_CONTROL_LOGGER_TEST_H_

#include "../sources/Logger.h"

#include "TestFramework.h"

#include <unistd.h>
#include <cstdio>

namespace LedControl {

class LoggerTest: public ::testing::Test {
public:
	virtual void SetUp() {}
	virtual void TearDown() {}
};//end of declaration class LoggerTest: public ::testing::Test

TEST_F(LoggerTest, should_create_file_in_default_path){
	Logger logger( "" );
	struct stat sb;
	EXPECT_TRUE(stat("./led_control_log.txt", &sb) == 0);
	std::remove("./led_control_log.txt");
}

TEST_F(LoggerTest, should_create_file_in_given_path){
	Logger logger( "/tmp/log.txt" );
	struct stat sb;
	EXPECT_TRUE(stat("/tmp/log.txt", &sb) == 0);
	std::remove("/tmp/log.txt");
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_LOGGER_TEST_H_ */
