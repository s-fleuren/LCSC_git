#include "stdafx.h"
#include <intrin.h>
#include <math.h>

namespace lcsc {

	double lcrng::next_double() {
		x_ = (a_*x_ + c_) % m_;
		return (double)x_ / m_;
	}

	uint64_t lcrng::next_int(uint64_t min, uint64_t max) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t range = max - min;
		if (range >= m_)
		{
			printf("Error: range is too large. Press any key to exit.");
			getchar();
			exit(1);
		}
		if (range == m_ - 1)
		{
			x_ = (a_*x_ + c_) % m_;
			return x_;
		}
		return (uint64_t)(next_double()*range + min);
	}

	uint64_t park_miller::next_int(uint64_t min = 0, uint64_t max = (1 << 31) - 2) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t range = max - min;
		if (range >= m_)
		{
			printf("Error: range is too large. Press any key to exit.");
			getchar();
			exit(1);
		}
		if (range == m_ - 1)
		{
			x_ = (a_ * (x_ % q_) - r_ * (x_ / q_) + m_) % m_;//Schrage’s trick
			return x_ + min;
		}
		unsigned long index;
		_BitScanReverse64(&index, range);//2**index <= range < 2**(index+1)
		while (1 > 0)
		{
			x_ = (a_ * (x_ % q_) - r_ * (x_ / q_) + m_) % m_;
			uint64_t output = (x_ >> (63 - index)) + min;
			if (output <= max) return output;
		}
	}

	double park_miller::next_double() {
		uint64_t x = next_int();
		return (double)x / m_;
	}

	uint64_t xorshift::next_int(uint64_t min = 0, uint64_t max = ((uint64_t)1 << 63) - 1) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t range = max - min;
		if (range == ((uint64_t)1 << 63) - 1)
		{
			x_ ^= x_ >> 12;
			x_ ^= x_ << 25;
			x_ ^= x_ >> 27;
			return x_;
		}
		unsigned long index;
		_BitScanReverse64(&index, range);//2**index <= range < 2**(index+1)
		while (1 > 0)
		{
			x_ ^= x_ >> 12;
			x_ ^= x_ << 25;
			x_ ^= x_ >> 27;
			uint64_t output = (x_ >> (63 - index)) + min;
			if (output <= max) return output;
		}
	}

	double xorshift::next_double() {
		uint64_t x = next_int();
		uint64_t m = (((uint64_t)1 << 64) - 1);
		return (double)x / m;
	}

	uint64_t extern_rng::next_int(uint64_t min, uint64_t max)
	{
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t range = max - min;
		return (uint64_t)(next_double()*range + min);
	}
	double extern_rng::next_double()
	{
		n_++;
		return f_(n_ - 1);
	}


	//distribution samples

	double rng_engine::next_double(double min, double max)
	{
		double value = next_double();
		value = min + (max - min) * value;
		return value;
	}
	std::vector<double> rng_engine::next_multi_double(std::vector<double> min, std::vector<double> max)
	{
		std::size_t dim = min.size();
		auto output = std::vector<double>(dim);
		if (dim != max.size())
		{
			std::cout << "Warning: min and max have different dimensions.\n";
		}
		for (std::size_t i = 0; i < dim; i++)
		{
			output[i] = next_double(min[i], max[i]);
		}
		return output;
	}
	double rng_engine::next_exponential(double lambda)
	{
		double u = next_double();
		return -log(u) / lambda;
	}
	double rng_engine::next_normal(double mean, double sigma)
	{
		//http://www.columbia.edu/~ks20/4703-Sigman/4703-07-Notes-ARM.pdf
		double y1, y2;
		double y = -1;
		while (y < 0)
		{
			y1 = next_exponential(1);
			y2 = next_exponential(1);
			y = y2 - pow(y1 - 1, 2) / 2;
		}
		if (next_double() < 0.5)
		{
			y1 = -y1;
		}
		return sigma * y1 + mean;
	}

	void rng_engine::hussle(std::vector<int>& numbers)
	{
		int storage;
		uint64_t index;
		auto n = numbers.size() - 1;
		while (n > 0)
		{
			index = next_int(0, n);
			storage = numbers[n];
			numbers[n] = numbers[index];
			numbers[index] = storage;
			n--;
		}
	}
	
} // namespace lcsc
