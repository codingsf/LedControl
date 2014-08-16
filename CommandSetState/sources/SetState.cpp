/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/
#include "SetState.h"

CommandSetState::CommandSetState(LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments)
: reciver_(reciver), clientId_(clientId)
{
	setArguments(arguments);
}//end of  CommandSetState::CommandSetState()

void CommandSetState::setArguments(const std::vector<std::string>& newArguments) {
	if ( newArguments.size() > 1 ) {
		throw LedControl::Exception("too many arguments for command 'set-state'");
	}//end of if 

	if ( newArguments.empty() ) {
		throw LedControl::Exception("command 'set-state' need one argument");
	}//end of if 

	if ( newArguments[0] != "on" || newArguments[0] != "off" ) {
		throw LedControl::Exception("bad argument for command 'set-state'");
	}//end of if 

	arguments_ = newArguments;
}//end of void CommandSetState::setArguments()

bool CommandSetState::excute(std::string& result) {
	result = "";
	return reciver_->setState(arguments_[0]);
}
