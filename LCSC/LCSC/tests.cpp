#include "stdafx.h"
#include "tests.hpp"
#include <vector>
#include <string>

namespace lcsc {

	void histogram::test(const uint64_t n) {
		std::vector<uint64_t> bins(M_);
		for (uint64_t i = 0; i < n; i++)
		{
			double sample = engine_.next_double();
			uint64_t bin = (uint64_t)(sample*M_);
			bins[bin] += 1;
		}
		uint64_t j = 0;
		while (bins[j] == 0)
		{
			std::cout << "y_" << j + 1 << ":" << "\n";
			j++;
		}
		auto s = std::string(10, '*');
		std::cout << "y_" << j + 1 << ":" << s << "\n";
		for (uint64_t i = j + 1; i < M_; i++)
		{
			int x = (int)(10.0*bins[i] / bins[0] + 0.5);
			auto s = std::string(x, '*');
			std::cout << "y_" << i + 1 << ":" << s << "\n";
		}
		system("pause");
	}
}