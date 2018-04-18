#include "stdafx.h"
#include <intrin.h>

namespace lcsc {

	int lcsc::highestOneBit(uint64_t i) {
		i |= (i >> 1);
		i |= (i >> 2);
		i |= (i >> 4);
		i |= (i >> 8);
		i |= (i >> 16);
		i |= (i >> 32);
		unsigned long index;
		_BitScanReverse64(&index, ((uint64_t)1 << 63) - 1);
		return index;
	}

	std::vector<uint64_t> primeVector(int length)
	{
		auto output = std::vector<uint64_t>(length);
		output[0] = 2;
		if (length == 1)
		{
			return output;
		}
		uint32_t n = 1;
		uint32_t upperBound = (uint32_t)(length * log(length) + length * log(log(length))) + 3;
		std::vector<uint32_t> sieve(upperBound);
		std::generate(sieve.begin(), sieve.end(), [&n]() {return n += 2; });
		uint32_t prime, index = 0;
		int i = 1;
		while (i < length)
		{
			if (sieve[index] > 0)
			{
				prime = sieve[index];
				output[i] = prime;
				i++;
				for (uint32_t j = index; j < upperBound; j += prime)
				{
					sieve[j] = 0;
				}
			}
			index++;
		}
		return output;
	}

	std::vector<double> haltonCompute(std::vector<uint64_t> & primes, int d, int n)
	{
		uint64_t prime;
		double factor;
		auto output = std::vector<double>(d);
		int nCopy;
		for (int i = 0; i < d; i++)
		{
			nCopy = n;
			output[i] = 0;
			prime = primes[i];
			factor = 1.0 / prime;
			while (nCopy != 0)
			{
				output[i] += (nCopy % prime) * factor;
				nCopy /= prime;
				factor /= prime;
			}
		}
		return output;
	}


	haltonSequence::haltonSequence(std::vector<uint64_t> & primes, int d, int length) : primes_(primes)
	{
		length_ = length;
		d_ = d;
		haltonSequence_ = std::vector<std::vector<double>>(length);
		for (int i = 1; i <= length; i++)
		{
			haltonSequence_[i - 1] = lcsc::haltonCompute(primes, d_, i);
		}
	}

	std::vector<double> haltonSequence::halton(int n)
	{
		if (n > length_)
		{
			for (int i = length_ + 1; i <= n; i++)
			{
				haltonSequence_.push_back(lcsc::haltonCompute(primes_, d_, i));
			}
			length_ = n;
		}
		return haltonSequence_[n - 1];
	}

	double haltonSequence::haltonDouble(int n)
	{
		if (n > length_*d_)
		{
			int m = (n - 1) / d_ + 1;
			for (int i = length_ + 1; i <= m; i++)
			{
				haltonSequence_.push_back(lcsc::haltonCompute(primes_, d_, i));
			}
			length_ = m;
		}
		int i = (n - 1) / d_;
		int j = (n - 1) % d_;
		return haltonSequence_[i][j];
	}

	std::function<double(int)> haltonSequence::haltonDoubleForExtern()
	{
		return [&](int n) -> double { return haltonDouble(n); };
	}

}// namespace lcsc