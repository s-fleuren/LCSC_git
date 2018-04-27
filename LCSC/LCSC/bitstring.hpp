#pragma once

namespace lcsc {

	template <typename T>
	class bitstring {
	public:
		bitstring(T variable, int n) :
			bits_(0)
		{}

		T genotype();

	private:
		T bits_; //Fix this later
	};

}