#include "stdafx.h"

namespace lcsc {
	double hit_or_miss_integration::integrate(int n) {
		double counter = 0;
		double sample_x;
		double sample_y;
		for (int i = 0; i < n; i++)
		{
			sample_x = engine_.next_double();
			sample_y = engine_.next_double();
			if (f_(sample_x) > 1 or f_(sample_x) < 0)
			{
				printf("Warning: the value f(%f) = %f lies outside the range [0,1]\n",
					sample_x, f_(sample_x));
			}
			if (sample_y <= f_(sample_x))
			{
				counter++;
			}
		}
		return counter / n;
	}

}