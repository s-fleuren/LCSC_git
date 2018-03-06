// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main() {
	uint64_t seed = 17544;
	auto engine = lcsc::xorshift(seed);
	for (int i = 0; i < 20; i++)
	{
		printf("%d\n", engine.next_int(7,9));
	}
	printf("Press any key to exit");
	getchar();
}

