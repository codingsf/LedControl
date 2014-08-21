#include "GetState.h"

CommandGetState::CommandGetState(LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments)
: reciver_(reciver), clientId_(clientId)
{
	setArguments(arguments);
}//end of  CommandGetState::CommandGetState()

void CommandGetState::setArguments(const std::vector<std::string>& newArguments) {
	if ( newArguments.size() > 0 ) {
		throw LedControl::Exception("too many arguments for command 'get-led-state'");
	}//end of if 
}//end of void CommandGetState::setArguments()

bool CommandGetState::excute(std::string& result) {
	result = reciver_->getState();
	if ( result == "" ) {
		return false;
	}//end of if 

	return true;
}
