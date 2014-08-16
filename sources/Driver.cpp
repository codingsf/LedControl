#include "Driver.h"

#include <cstdlib>
#include <ctime>
#include <assert.h>

namespace LedControl {

const std::string Driver::FAIL = "";

Driver::Driver(): state_("off"), color_("blue"), rate_("0") {
	std::srand(time(0));
}//end of Driver::Driver()

bool Driver::setState(const std::string& newState) noexcept {
	assert(newState == "on" || newState == "off");

	int fate = std::rand() % MERCY_OF_FATE;
	if ( fate == 0 ) {
		return false;
	}//end of if 

	state_ = newState;
	return true;
}//end of bool Driver::setState()

const std::string& Driver::getState() const noexcept {
	int fate = std::rand() % MERCY_OF_FATE;
	if ( fate == 0 ) {
		return FAIL;
	}//end of if 

	return state_;
}//end of const std::string& Driver::getState()

bool Driver::setColor(const std::string& newColor) noexcept {
	assert(newColor == "green" || newColor == "red" || newColor == "blue");

	int fate = std::rand() % MERCY_OF_FATE;
	if ( fate == 0 ) {
		return false;
	}//end of if 

	color_ = newColor;
	return true;
}//end of bool Driver::setColor()

const std::string& Driver::getColor() const noexcept {
	int fate = std::rand() % MERCY_OF_FATE;
	if ( fate == 0 ) {
		return FAIL;
	}//end of if 

	return color_;
}//end of const std::string& Driver::getColor()

bool Driver::setRate(const std::string& newRate) noexcept {
	assert(newRate == "0" || newRate == "1" || newRate == "2" || newRate == "3" || newRate == "4" || newRate == "5");

	int fate = std::rand() % MERCY_OF_FATE;
	if ( fate == 0 ) {
		return false;
	}//end of if 

	rate_ = newRate;
	return true;
}//end of bool Driver::setRate()

const std::string& Driver::getRate() const noexcept {
	int fate = std::rand() % MERCY_OF_FATE;
	if ( fate == 0 ) {
		return FAIL;
	}//end of if 

	return rate_;
}//end of const str::string& Driver::getRate()

} /* LedControl */ 
