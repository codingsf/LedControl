#ifndef LED_CONTROL_EXCEPTION_TEST_H_
#define LED_CONTROL_EXCEPTION_TEST_H_

/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "../sources/Exception.h"

#include "TestFramework.h"

namespace LedControl {

class LedControlExceptionTest: public ::testing::Test {
/*
 * Тестовый класс для класса Exception
*/

public:
	virtual void SetUp() {}

	virtual void TearDown() {}
};//end of declaration class LedControlExceptionTest

TEST_F(LedControlExceptionTest, returnSystemErrorMessage){
	errno = EACCES;
	EXPECT_STREQ("Permission denied", Exception::getSystemErrorMessage());
}

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_EXCEPTION_TEST_H_ */
