/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/
#include "SetColor.h"

CommandSetColor::CommandSetColor(LedControl::Driver* reciver,
								const std::string& clientId,
								const std::vector<std::string>& arguments)
: reciver_(reciver), clientId_(clientId)
{
	setArguments(arguments);
}//end of  CommandSetColor::CommandSetColor()

void CommandSetColor::setArguments(const std::vector<std::string>& newArguments) {
	if ( newArguments.size() > 1 ) {
		throw LedControl::Exception("too many arguments for command 'set-led-color'");
	}//end of if 

	if ( newArguments.empty() ) {
		throw LedControl::Exception("command 'set-led-color' need one argument");
	}//end of if 

	if ( newArguments[0] != "green" && newArguments[0] != "red" && newArguments[0] != "blue" ) {
		throw LedControl::Exception("bad argument for command 'set-led-color'");
	}//end of if 

	arguments_ = newArguments;
}//end of void CommandSetColor::setArguments()

bool CommandSetColor::excute(std::string& result) {
	result = "";
	return reciver_->setColor(arguments_[0]);
}
