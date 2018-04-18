#pragma once

#include <functional>
#include <vector>

namespace lcsc {
	class numerical_integration
	{
	public:
		virtual double integrate(int n) = 0;
	};

	class hit_or_miss_integration : public numerical_integration
	{
	public:
		hit_or_miss_integration(rng_engine &engine, std::function<double(double)> f, double domain_min, double domain_max,
			double range_min, double range_max) :
			engine_(engine), f_(f), domain_min_(domain_min), domain_max_(domain_max), range_min_(range_min), range_max_(range_max) {}
		double integrate(int n) override;

	private:
		rng_engine & engine_;
		std::function<double(double)> f_;
		double domain_min_;
		double domain_max_;
		double range_min_;
		double range_max_;
	};

	class multi_dimensional_hit_or_miss_integration : public numerical_integration
	{
	public:
		multi_dimensional_hit_or_miss_integration(rng_engine &engine, std::function<double(std::vector<double>)> f,
			std::vector<double> domain_min, std::vector<double> domain_max,
			double range_min, double range_max) :
			engine_(engine), f_(f), domain_min_(domain_min), domain_max_(domain_max), range_min_(range_min), range_max_(range_max) {}
		double integrate(int n) override;

	private:
		rng_engine & engine_;
		std::function<double(std::vector<double>)> f_;
		std::vector<double> domain_min_;
		std::vector<double> domain_max_;
		double range_min_;
		double range_max_;
	};

	class simple_sampling_integration : public numerical_integration
	{
	public:
		simple_sampling_integration(rng_engine &engine, std::function<double(double)> f, double domain_min, double domain_max) :
			engine_(engine), f_(f), domain_min_(domain_min), domain_max_(domain_max) {}
		double integrate(int n) override;

	private:
		rng_engine & engine_;
		std::function<double(double)> f_;
		double domain_min_;
		double domain_max_;
	};

	class multi_dimensional_simple_sampling_integration : public numerical_integration
	{
	public:
		multi_dimensional_simple_sampling_integration(rng_engine &engine, std::function<double(std::vector<double>)> f, 
			std::vector<double> domain_min, std::vector<double> domain_max) :
			engine_(engine), f_(f), domain_min_(domain_min), domain_max_(domain_max) {}
		double integrate(int n) override;

	private:
		rng_engine & engine_;
		std::function<double(std::vector<double>)> f_;
		std::vector<double> domain_min_;
		std::vector<double> domain_max_;
	};
}