#ifndef LED_CONTROL_SERVER_TEST_H_
#define LED_CONTROL_SERVER_TEST_H_

/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
 */

#include "../sources/Server.h"

#include "TestFramework.h"

#include <thread>

namespace LedControl {

class ServerTest: public ::testing::Test {
public:
	virtual void SetUp(){}
	virtual void TearDown(){}
};//end of declaration class ServerTest: ::testing::Test

TEST_F(ServerTest, should_finish_work_if_get_SIGINT){
		Logger* log = Logger::initialize();
		Driver reciver;
		CommandFactory cm("./tests_support/test1.conf", &reciver, log);
		MessageHandler mh("led1", &cm, log);
		Server s(&mh, log);
	pid_t pid = ::fork();
	if (pid != 0){
		s.run(2);
		_exit(0);
	}
	else {
		::usleep(300000);
		::kill(::getppid(), SIGINT);
	}

	EXPECT_TRUE(true);
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_SERVER_TEST_H_ */

