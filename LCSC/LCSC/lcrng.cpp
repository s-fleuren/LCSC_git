#include "stdafx.h"

namespace lcsc {

	double lcrng::next() {
		x_ = (a_*x_ + c_) % m_;
		return x_ / (m_ + 0.0);
	}

} // namespace lcsc
