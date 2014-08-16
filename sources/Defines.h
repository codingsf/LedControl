#ifndef DEFINES_H_
#define DEFINES_H_

#ifdef __LED_CONTROL_TEST__
#include "gtest/gtest_prod.h"
#endif

#ifdef __LED_CONTROL_DEBUG__
#include <iostream>
#endif

#ifdef __LED_CONTROL_DEBUG__
#define TRACE(arg, out) {out << #arg << std::endl; arg;}
#else
#define TRACE(arg, out)
#endif

#ifdef __LED_CONTROL_DEBUG__
#define PRINTSEQ(log, seq, size) {\
	log->write("------------------------------", Logger::ADD_TIME | Logger::ADD_LN) \
	log->write("file: ", Logger::ADD_TIME); \
	log->write(__FILE__); \
	log->write(", str. "); \
	log->write(__LINE__); \
	log->write(": "); \
	log->write(#seq); \
	log->write(":", Logger::ADD_LN); \
	for(size_t i = 0; i < (size); ++i){ \
		log->write("el #"); \
		log->write(i); \
		log->write(": "); \
		log->write(seq[i], Logger::ADD_LN); \
	log->write("------------------------------", ADD_TIME) \
	} \
}
#else
#define PRINTSEQ(log, seq, size)
#endif

#ifdef __LED_CONTROL_DEBUG__
#define PRINTVAL(log, val) {\
	log->write("file: ", Logger::ADD_TIME); \
	log->write(__FILE__); \
	log->write(", str. "); \
	log->write(__LINE__); \
	log->write(": "); \
	log->write(#val); \
	log->write(" - "); \
	log->write(val, Logger::ADD_LN); \
}
#else
#define PRINTVAL(log, val)
#endif

#endif /* end of include guard: DEFINES_H_ */
