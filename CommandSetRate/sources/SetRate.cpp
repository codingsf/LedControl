#include "SetRate.h"

CommandSetRate::CommandSetRate(LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments)
: reciver_(reciver), clientId_(clientId)
{
	setArguments(arguments);
}//end of  CommandSetRate::CommandSetRate()

void CommandSetRate::setArguments(const std::vector<std::string>& newArguments) {
	if ( newArguments.size() > 1 ) {
		throw LedControl::Exception("too many arguments for command 'set-led-rate'");
	}//end of if 

	if ( newArguments.empty() ) {
		throw LedControl::Exception("command 'set-led-rate' need one argument");
	}//end of if 

	if ( newArguments[0] != "0" && newArguments[0] != "1" && newArguments[0] != "2" && newArguments[0] != "3" && newArguments[0] != "4" && newArguments[0] != "5" ) {
		throw LedControl::Exception("bad argument for command 'set-led-rate'");
	}//end of if 

	arguments_ = newArguments;
}//end of void CommandSetRate::setArguments()

bool CommandSetRate::excute(std::string& result) {
	result = "";
	return reciver_->setRate(arguments_[0]);
}
