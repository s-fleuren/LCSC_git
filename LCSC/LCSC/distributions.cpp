#include "stdafx.h"


namespace lcsc {

	uint64_t uniform_int_distribution::sample() {
		double value = engine_.next();
		value = min_ + (max_ - min_) * value;
		return (uint64_t)value;
	}

	double uniform_real_distribution::sample() {
		double value = engine_.next();
		value = min_ + (max_ - min_) * value;
		return value;
	}


}


