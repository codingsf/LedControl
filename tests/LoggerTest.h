#ifndef LED_CONTROL_LOGGER_TEST_H_
#define LED_CONTROL_LOGGER_TEST_H_

#include "../sources/Logger.h"

#include "TestFramework.h"

#include <unistd.h>
#include <cstdio>
#include <ctime>

namespace LedControl {

class LoggerTest: public ::testing::Test {
public:
	virtual void SetUp() {}
	virtual void TearDown() {}
};//end of declaration class LoggerTest: public ::testing::Test

TEST_F(LoggerTest, should_create_file_in_default_path){
	//если файл существует, предварительно удалим его
	struct stat sb;
	if(stat("./led_control_log.txt", &sb) == 0){
		std::remove("./led_control_log.txt");
	}

	{
		Logger logger( "" );
		EXPECT_TRUE(stat("./led_control_log.txt", &sb) == 0);
	}

	std::remove("./led_control_log.txt");
}

TEST_F(LoggerTest, should_create_file_in_given_path){
	{
	Logger logger( "/tmp/log.txt" );
	struct stat sb;
	EXPECT_TRUE(stat("/tmp/log.txt", &sb) == 0);
	}

	std::remove("/tmp/log.txt");
	struct stat sb;
	EXPECT_TRUE(stat("/tmp/log.txt", &sb) != 0);
}

TEST_F(LoggerTest, should_open_file_with_saving_previous_data){
	std::ofstream out("/tmp/log.txt");
	out << "test";
	out.close();

	{
		Logger logger( "/tmp/log.txt");
	}
	
	std::ifstream in("/tmp/log.txt");
	std::string str;
	in >> str;

	EXPECT_STREQ("test", str.c_str());

	in.close();
	std::remove("/tmp/log.txt");
}

TEST_F(LoggerTest, should_add_new_message_in_log){
	std::string standardMessage = "test";
	{
		Logger* logger = new Logger("/tmp/log.txt");
		logger->addMessage(standardMessage);
		delete logger;
	}

	std::string testString;
	std::ifstream in("/tmp/log.txt");
	std::getline(in, testString);

	EXPECT_STREQ(standardMessage.c_str(), testString.c_str());

	in.close();
	std::remove("/tmp/log.txt");
}

TEST_F(LoggerTest, should_add_current_date_before_message){
	std::string standardMessage;
	{
		Logger* logger = new Logger( "/tmp/log.txt");
		time_t t;
		struct tm *timeinfo;
		std::time(&t);
		timeinfo = std::localtime(&t);
		char strTime[100];
		std::strftime(strTime, 100, "%m-%d-%y %R", timeinfo);
		standardMessage = std::string("[") + std::string(strTime) + std::string("] test");
		logger->addMessage("test", Logger::ADD_TIME);
		delete logger;
	}

	std::string testString;
	std::ifstream in("/tmp/log.txt");
	std::getline(in, testString);

	EXPECT_STREQ(standardMessage.c_str(), testString.c_str());

	in.close();
	std::remove("/tmp/log.txt");
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_LOGGER_TEST_H_ */
