#ifndef DEFINES_H_
#define DEFINES_H_

#ifdef __LED_CONTROL_TEST__
#include "gtest/gtest_prod.h"
#endif

#ifdef __LED_CONTROL_DEBUG__
#define TRACE(arg, out) {out << #arg << std::endl; arg;}
#else
#define TRACE(arg, out)
#endif

#ifdef __LED_CONTROL_DEBUG__
#define PRINTSEQ(log, seq, size) {\
	log->addMessage("------------------------------", Logger::ADD_TIME | Logger::ADD_LN) \
	log->addMessage("file: ", Logger::ADD_TIME); \
	log->addMessage(__FILE__); \
	log->addMessage(", str. "); \
	log->addMessage(__LINE__); \
	log->addMessage(": "); \
	log->addMessage(#seq); \
	log->addMessage(":", Logger::ADD_LN); \
	for(size_t i = 0; i < (size); ++i){ \
		log->addMessage("el #"); \
		log->addMessage(i); \
		log->addMessage(": "); \
		log->addMessage(seq[i], Logger::ADD_LN); \
	log->addMessage("------------------------------", ADD_TIME) \
	} \
}
#else
#define PRINTSEQ(log, seq, size)
#endif

#ifdef __LED_CONTROL_DEBUG__
#define PRINTVAL(log, val) {\
	log->addMessage("file: ", Logger::ADD_TIME); \
	log->addMessage(__FILE__); \
	log->addMessage(", str. "); \
	log->addMessage(__LINE__); \
	log->addMessage(": "); \
	log->addMessage(#val); \
	log->addMessage(" - "); \
	log->addMessage(val, Logger::ADD_LN); \
}
#else
#define PRINTVAL(log, val)
#endif

#endif /* end of include guard: DEFINES_H_ */
