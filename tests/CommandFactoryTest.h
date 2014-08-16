#ifndef LED_CONTROL_COMMAND_FACTORY_TEST_H_
#define LED_CONTROL_COMMAND_FACTORY_TEST_H_

/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "../sources/CommandFactory.h"

#include "TestFramework.h"

namespace LedControl {

class CommandFactoryTest: public ::testing::Test {
public:
	virtual void SetUp() {}
	virtual void TearDown() {}
};//end of declaration class CommandFactoryTest: public ::testing::Test

TEST_F(CommandFactoryTest, should_throw_exception_if_config_file_can_not_be_opened){
	Driver driver;
	Logger* log = Logger::initialize();
	EXPECT_NO_THROW(CommandFactory c("./tests_support/test1.conf", &driver, log));
	EXPECT_THROW(CommandFactory c1("./tests_support/nofile", &driver, log), Exception);
}

TEST_F(CommandFactoryTest, should_throw_exception_if_data_not_complete){
	Driver driver;
	Logger* log = Logger::initialize();
	EXPECT_THROW(CommandFactory c("./tests_support/test2.conf", &driver, log), Exception);
}

TEST_F(CommandFactoryTest, should_throw_exception_if_config_has_bad_path_to_lib){
	Driver driver;
	Logger* log = Logger::initialize();
	EXPECT_THROW(CommandFactory c("./tests_support/test3.conf", &driver, log), Exception);
}

TEST_F(CommandFactoryTest, should_throw_exception_if_lib_doesnt_have_func_create){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory c("./tests_support/test4.conf", &driver, log);
	std::string clientId = "pid2";
	std::vector<std::string> args;
	args.push_back("on");
	EXPECT_THROW(c.create("bad-lib", clientId, args), Exception);
}

TEST_F(CommandFactoryTest, should_return_pointer_on_concrete_command_object){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory c("./tests_support/test1.conf", &driver, log);

	std::string clientId = "pid2";
	std::vector<std::string> args;
	args.push_back("on");
	Command* cm = c.create("set-state", clientId, args);
	EXPECT_TRUE(cm != nullptr);

	Command* cm1 = c.create("set-state", clientId, args);
	EXPECT_TRUE(cm == cm1);

	cm = c.create("bad-identifier", clientId, args);
	EXPECT_TRUE(cm == nullptr);
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_COMMAND_FACTORY_TEST_H_ */

