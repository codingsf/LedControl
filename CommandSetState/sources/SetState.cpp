/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/
#include "SetState.h"

//namespace LedControl {

bool CommandSetState::excute(const std::vector<std::string>& arguments) {
	if ( arguments.size() > 1 ) {
		throw LedControl::Exception("too many arguments for command 'set-state'");
	}//end of if 

	if ( arguments.empty() ) {
		throw LedControl::Exception("command 'set-state' need one argument");
	}//end of if 

	if ( arguments[0] != "on" || arguments[0] != "off" ) {
		throw LedControl::Exception("bad argument for command 'set-state'");
	}//end of if 

	return reciver_->setState(arguments[0]);
}


//extern "C" Command* create(LedControl::Driver* reciver) {
	//return new CommandSetState(reciver);
//}//end of Command* create()
