#include "GetRate.h"

CommandGetRate::CommandGetRate(LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments)
: reciver_(reciver), clientId_(clientId)
{
	setArguments(arguments);
}//end of  CommandGetRate::CommandGetRate()

void CommandGetRate::setArguments(const std::vector<std::string>& newArguments) {
	if ( newArguments.size() > 0 ) {
		throw LedControl::Exception("too many arguments for command 'get-led-rate'");
	}//end of if 
}//end of void CommandGetRate::setArguments()

bool CommandGetRate::excute(std::string& result) {
	result = reciver_->getRate();
	if ( result == "" ) {
		return false;
	}//end of if 

	return true;
}
