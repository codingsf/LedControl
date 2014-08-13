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

TEST_F(CommandFactoryTest, should_fill_command_list){
	Driver driver;
	Logger* log = Logger::initialize();
	CommandFactory c("./tests_support/test1.conf", &driver, log);
	std::map<std::string, Command*>::iterator it = c.commandList_.begin();
	EXPECT_STREQ("set-state", it->first.c_str());
	EXPECT_TRUE(it->second != 0);
	EXPECT_TRUE(c.handles_.size() == 1);
}

TEST_F(CommandFactoryTest, should_throw_exception_if_config_has_bad_path_to_lib){
	Driver driver;
	Logger* log = Logger::initialize();
	EXPECT_THROW(CommandFactory c("./tests_support/test2.conf", &driver, log), Exception);
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_COMMAND_FACTORY_TEST_H_ */

