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
#define PRINTSEQ(seq, size, out) {\
out << "------------------------------\n"; \
out << "file: " << __FILE__ << ", str. " << __LINE__ << ":" << #seq << ":" << "\n"; \
for(size_t i = 0; i < (size); ++i){ \
out << "el #" << i << ": " << seq[i] << "\n"; \
} \
out << "------------------------------\n"; \
}
#else
#define PRINTSEQ(seq, size, out)
#endif

#ifdef __LED_CONTROL_DEBUG__
#define PRINTVAL(val, out) {out << "file: " << __FILE__ << ", str. " << __LINE__ << ": " << #val << " - " << val << "\n";}
#else
#define PRINTVAL(val, out)
#endif

#endif /* end of include guard: DEFINES_H_ */
