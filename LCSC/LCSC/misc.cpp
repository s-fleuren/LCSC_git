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


}// namespace lcsc