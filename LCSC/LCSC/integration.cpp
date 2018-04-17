#include "stdafx.h"

namespace lcsc {
	double hit_or_miss_integration::integrate(int n) {
		double counter = 0;
		double sample_x;
		double sample_y;
		for (int i = 0; i < n; i++)
		{
			sample_x = engine_.next_double(domain_min_, domain_max_);
			sample_y = engine_.next_double(range_min_, range_max_);
			if (f_(sample_x) > range_max_ or f_(sample_x) < range_min_)
			{
				printf("Warning: the value f(%f) = %f lies outside the specified range.\n",
					sample_x, f_(sample_x));
			}
			if (sample_y <= f_(sample_x))
			{
				counter++;
			}
		}
		return (range_max_- range_min_) * (domain_max_ - domain_min_) * counter / n;
	}

	double simple_sampling_integration::integrate(int n)
	{
		double sum = 0;
		double sample_x;
		for (int i = 0; i < n; i++)
		{
			sample_x = engine_.next_double(domain_min_, domain_max_);
			sum += f_(sample_x);
		}
		return (domain_max_ - domain_min_) * sum / n;
	}

	double multi_dimensional_hit_or_miss_integration::integrate(int n)
	{
		double counter = 0;
		std::vector<double> sample_x;
		double sample_y;
		for (int i = 0; i < n; i++)
		{
			sample_x = engine_.next_multi_double(domain_min_, domain_max_);
			sample_y = engine_.next_double(range_min_, range_max_);
			if (f_(sample_x) > range_max_ or f_(sample_x) < range_min_)
			{
				printf("Warning: the value f(x) = %f lies outside the specified range.\n",
					f_(sample_x));
			}
			if (sample_y <= f_(sample_x))
			{
				counter++;
			}
		}
		double factor = 1;
		for (std::size_t i = 0; i < domain_min_.size(); i++)
		{
			factor *= domain_max_[i] - domain_min_[i];
		}
		return (range_max_ - range_min_) * factor * counter / n;
	}

	double multi_dimensional_simple_sampling_integration::integrate(int n)
	{
		double sum = 0;
		std::vector<double> sample_x;
		for (int i = 0; i < n; i++)
		{
			sample_x = engine_.next_multi_double(domain_min_, domain_max_);
			sum += f_(sample_x);
		}
		double factor = 1;
		for (std::size_t i = 0; i < domain_min_.size(); i++)
		{
			factor *= domain_max_[i] - domain_min_[i];
		}
		return factor * sum / n;
	}

}