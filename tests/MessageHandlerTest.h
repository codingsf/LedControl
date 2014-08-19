#ifndef LED_CONTROL_MESSAGE_HANDLER_TEST_H_
#define LED_CONTROL_MESSAGE_HANDLER_TEST_H_

#include "../sources/MessageHandler.h"

#include "TestFramework.h"

#include <cstring>

namespace LedControl {

class MessageHandlerTest: public ::testing::Test {
public:
	std::string m1_;
	std::string m2_;

	virtual void SetUp() {
		m1_ = "pid123 set-state on\n";
		m2_ = "pid456 set-state off\n";
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

TEST_F(MessageHandlerTest, should_return_command){
	Command* cm1;
	Command* cm2;
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 

	pid_t pid = ::fork();
	if(pid == 0){
		FILE* out = std::fopen("/tmp/led1", "w");
		std::fputs(m1_.c_str(), out);
		::fflush(out);
		std::fputs(m2_.c_str(), out);
		::fflush(out);
		std::fclose(out);
		::_exit(0);
	} else {
		cm1 = mh.getRequest();
		cm2 = mh.getRequest();
	}

	EXPECT_TRUE(cm1 != nullptr);
	EXPECT_TRUE(cm2 != nullptr);

	EXPECT_STREQ("pid123", cm1->getClientId().c_str());

	EXPECT_STREQ("pid456", cm2->getClientId().c_str());
}

TEST_F(MessageHandlerTest, should_return_nullptr_if_message_doesnt_have_clientId){
	Command* cm;
	std::string message("set-state on");
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 

	pid_t pid = ::fork();
	if(pid == 0){
		std::ofstream out("/tmp/led1", std::fstream::out);
		out << message << std::endl;
		::_exit(0);
	} else {
		cm = mh.getRequest();
	}

	EXPECT_TRUE(cm == nullptr);
}

TEST_F(MessageHandlerTest, should_return_unknown_command_object_if_message_doesnt_have_commandId){
	Command* cm;
	std::string message("pid1");
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 

	pid_t pid = ::fork();
	if(pid == 0){
		std::ofstream out("/tmp/led1", std::fstream::out);
		out << message << std::endl;
		::_exit(0);
	} else {
		cm = mh.getRequest();
	}

	std::string result;
	cm->excute(result);
	EXPECT_STREQ("no command identifier", result.c_str());
}

TEST_F(MessageHandlerTest, should_return_unknown_command_object_if_message_has_errors){
	Command* cm;
	std::string message("pid1 bad-state on");
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 

	pid_t pid = ::fork();
	if(pid == 0){
		std::ofstream out("/tmp/led1", std::fstream::out);
		out << message << std::endl;
		::_exit(0);
	} else {
		cm = mh.getRequest();
	}

	std::string result;
	cm->excute(result);
	EXPECT_STREQ("Command 'bad-state' is unknown", result.c_str());
}

TEST_F(MessageHandlerTest, should_get_client_id_from_message){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 
	std::string clientId1;
	mh.getClientIdFromMessage(m1_, clientId1);
	EXPECT_STREQ("pid123", clientId1.c_str());

	std::string clientId2;
	mh.getClientIdFromMessage(m2_, clientId2);
	EXPECT_STREQ("pid456", clientId2.c_str());
}

TEST_F(MessageHandlerTest, should_get_command_id_from_message){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 
	std::string cId1;
	mh.getCommandIdFromMessage(m1_, cId1);
	EXPECT_STREQ("set-state", cId1.c_str());

	std::string cId2;
	mh.getCommandIdFromMessage(m2_, cId2);
	EXPECT_STREQ("set-state", cId2.c_str());
}

TEST_F(MessageHandlerTest, should_get_arguments_from_message){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory cf("./tests_support/test1.conf", &driver, log);
	MessageHandler mh("led1", &cf, log); 
	std::vector<std::string> args1;
	mh.getArgumentsFromMessage(m1_, args1);
	EXPECT_TRUE(!args1.empty());
	EXPECT_TRUE(args1.size() == 1);
	for (auto it: args1) {
		EXPECT_STREQ("on", it.c_str());
	}//end of for

	std::vector<std::string> args2;
	mh.getArgumentsFromMessage(m2_, args2);
	EXPECT_TRUE(!args2.empty());
	EXPECT_TRUE(args2.size() == 1);
	for (auto it: args2) {
		EXPECT_STREQ("off", it.c_str());
	}//end of for
}

TEST_F(MessageHandlerTest, should_write_answer_in_fifo){
	pid_t pid = ::fork();
	if ( pid == 0) {
		Driver driver;
		Logger* log = Logger::initialize();
		CommandFactory cf("./tests_support/test1.conf", &driver, log);
		std::vector<std::string> args;
		args.push_back("on");
		Command* cm = cf.create("set-state", "pid1", args);
		MessageHandler mh("led1", &cf, log); 
		mh.giveAnswer(cm);
		_exit(0);
	} else {
		char ans[100];
		FILE* in = nullptr;
		while ( in == nullptr ) {
			in = std::fopen("/tmp/pid1", "r");
		}//end of while
		std::fgets(ans, sizeof(ans), in);
		EXPECT_TRUE(std::strcmp(ans,"OK\n") || std::strcmp(ans,"FAILED\n"));
		std::fclose(in);
	}
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_MESSAGE_HANDLER_TEST_H_ */
