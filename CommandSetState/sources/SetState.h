#ifndef LED_CONTROL_COMMAND_SET_STATE_H_
#define LED_CONTROL_COMMAND_SET_STATE_H_

#include "../../sources/Command.h"
#include "../../sources/Driver.h"
#include "../../sources/Exception.h"

#include <iostream>

class CommandSetState: public LedControl::Command {
/*
 * класс, реализующий передачу команды драйверу светодиода
*/
public:
	explicit CommandSetState (LedControl::Driver* reciver) : reciver_(reciver) {}
	~CommandSetState () {}

	virtual bool excute(const std::vector<std::string>& arguments);
private:
	LedControl::Driver* reciver_;
};//end of declaration class CommandSetState: public Command

extern "C" LedControl::Command* create(LedControl::Driver* reciver){
	return new CommandSetState(reciver);
}

#endif /* end of include guard: LED_CONTROL_COMMAND_SET_STATE_H_ */
