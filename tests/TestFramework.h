#ifndef GOOGLE_TEST_FRAMEWORK_H_
#define GOOGLE_TEST_FRAMEWORK_H_

#include "gtest/gtest.h"

template<class T, template<class U, class = std::allocator<U> > class Seq>
::testing::AssertionResult
ContainersIsEqual(Seq<T>& seq1, Seq<T>& seq2){
	if (seq1.size() != seq2.size()){
		return ::testing::AssertionFailure() << "vector lengths are not equal";
	}

	for (size_t i = 0; i < seq1.size(); ++i){
		if (seq1[i] != seq2[i]){
			return ::testing::AssertionFailure() << "elements with numbers " << i << " not equal";
		}
	}

	return ::testing::AssertionSuccess();
}//end of ::testing::AssertionResult ContainersIsEqual();

template<class T, template<class U, class = std::allocator<U> > class Seq>
::testing::AssertionResult
ContainersIsNotEqual(Seq<T>& seq1, Seq<T>& seq2){
	if (seq1.size() != seq2.size()){
		return ::testing::AssertionFailure() << "vector lengths are not equal";
	}

	int counterDifferences = 0;
	for (size_t i = 0; i < seq1.size(); ++i){
		if (seq1[i] != seq2[i]){
			++counterDifferences;
		}
	}

	if (!counterDifferences){
		return ::testing::AssertionFailure() << "arrays is equal";
	}

	return ::testing::AssertionSuccess();
}//end of ::testing::AssertionResult ContainersIsNotEqual();

template<class T, template<class U, class = std::allocator<U> > class Seq>
::testing::AssertionResult
ContainerFilledWithSpecifiedValues(Seq<T>& seq, T val){
	for (size_t i = 0; i < seq.size(); ++i){
		if (seq[i] != val){
			return ::testing::AssertionFailure() << "value differs from reference";
		}
	}

	return ::testing::AssertionSuccess();
}//end of ::testing::AsseriontResult ContainerFilledWithSpecifiedValues();

#endif /* end of include guard: GOOGLE_TEST_FRAMEWORK_H_ */
