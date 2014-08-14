#include "ExceptionTest.h"
#include "LoggerTest.h"
#include "CommandFactoryTest.h"
#include "MessageHandlerTest.h"

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}//end of main
