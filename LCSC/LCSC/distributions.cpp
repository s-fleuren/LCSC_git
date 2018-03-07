#include "stdafx.h"
#include <math.h>


namespace lcsc {

	uint64_t uniform_int_distribution::sample() {
		return (uint64_t)engine_.next_int(min_, max_);
	}

	double uniform_real_distribution::sample() {
		double value = engine_.next_double();
		value = min_ + (max_ - min_) * value;
		return value;
	}

	double exponential_distribution::sample() {
		double u = engine_.next_double();
		return -log(u) / lambda_;
	}

	double normal_distribution::sample() {
	//http://www.columbia.edu/~ks20/4703-Sigman/4703-07-Notes-ARM.pdf
		double y2 = exp_dis_.sample();
		double y = y2 - pow(y1_ - 1, 2) / 2;
		while (y < 0)
		{
			y1_ = exp_dis_.sample();
			y2 = exp_dis_.sample();
			y = y2 - pow(y1_ - 1, 2) / 2;
		}
		double z = y1_;
		if (engine_.next_double() < 0.5)
		{
			z = -z;
		}
		y1_ = y;
		return sigma_ * z + mean_;
	}
}


