#ifndef LED_CONTROL_EXCEPTION_H_
#define LED_CONTROL_EXCEPTION_H_

/*
 * developer: Kuksov Pavel
 * mail: aimed.fire@gmail.com
*/

#include "Defines.h"

#include <exception>
#include <string>
#include <cstring>

#include <errno.h>

namespace LedControl {

class Exception: public std::exception {
/*
 * Класс исключений
*/

public:
	Exception (const std::string& errorMessage): errorMessage_(errorMessage) {}

	/*
	 * Вернуть системное сообщение об ошибке
	*/
	static char* getSystemErrorMessage() { return std::strerror(errno); }

	const char* what() const noexcept { return errorMessage_.c_str(); }

	~Exception () noexcept {};
private:
	std::string errorMessage_;
};//end of declaration class Exception

} /* LedControl */ 

#endif /* end of include guard: LED_CONTROL_EXCEPTION_H_ */

