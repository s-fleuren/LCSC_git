#pragma once

namespace lcsc {

	template <typename T>
	class bitstring {
	public:
		bitstring(T variable, int n) :
		{}

		T genotype();

	private:
		std::vector<uint8_t> bits_;
	};

}