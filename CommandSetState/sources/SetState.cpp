/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "../../sources/Command.h"
#include "../../sources/Driver.h"
#include "../../sources/Exception.h"

namespace LedControl {

class CommandSetState: public Command {
/*
 * класс, реализующий передачу команды драйверу светодиода
*/
public:
	explicit CommandSetState (Driver* reciver) : reciver_(reciver) {}
	~CommandSetState () {}

	bool excute(const std::vector<std::string>& arguments) {
		if ( arguments.size() > 1 ) {
			throw Exception("too many arguments for command 'set-state'");
		}//end of if 

		if ( arguments.empty() ) {
			throw Exception("command 'set-state' need one argument");
		}//end of if 

		if ( arguments[0] != "on" || arguments[0] != "off" ) {
			throw Exception("bad argument for command 'set-state'");
		}//end of if 

		return reciver_->setState(arguments[0]);
	}

private:
	Driver* reciver_;
};//end of declaration class CommandSetState: public Command

Command* create(Driver* reciver) {
	return new CommandSetState(reciver);
}//end of Command* create()

} /* LedControl */
