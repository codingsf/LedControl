#include "GetColor.h"

CommandGetColor::CommandGetColor(LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments)
: reciver_(reciver), clientId_(clientId)
{
	setArguments(arguments);
}//end of  CommandGetColor::CommandGetColor()

void CommandGetColor::setArguments(const std::vector<std::string>& newArguments) {
	if ( newArguments.size() > 0 ) {
		throw LedControl::Exception("too many arguments for command 'get-led-color'");
	}//end of if 
}//end of void CommandGetColor::setArguments()

bool CommandGetColor::excute(std::string& result) {
	result = reciver_->getColor();
	if ( result == "" ) {
		return false;
	}//end of if 

	return true;
}
