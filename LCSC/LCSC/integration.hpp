#pragma once

#include <functional>

namespace lcsc {
	class numerical_integration
	{
	public:
		virtual double integrate(int n) = 0;
	};

	class hit_or_miss_integration : public numerical_integration
	{
	public:
		hit_or_miss_integration(rng_engine &engine, std::function<double(double)> f) :
			engine_(engine), f_(f){}
		double integrate(int n) override;

	private:
		rng_engine & engine_;
		std::function<double(double)> f_;
	};
}