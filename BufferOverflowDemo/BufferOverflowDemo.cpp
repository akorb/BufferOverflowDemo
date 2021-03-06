// BufferOverflowDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

__declspec(noinline) // prevent inlining
void neverCalled() {
	puts("Hacked!");
	getchar(); // shouldn't be there if you actually hack something ;)
	exit(0);
}


__declspec(noinline) // prevent inlining
void usualMethod() {

	// This works even if ASRL is used
	// A real world hack should use something more generic
	// but this is just a demonstration
	int func = (int)neverCalled;

	// 12, 13, 14, 15: Return address
	//  8,  9, 10, 11: Backup of ebp
	//  4,  5,  6,  7: Space for func variable (4 Byte = 1 int)
	//  0,  1,  2,  3: Space for buffer variable (4 Byte = 4 chars)

	// Overwrite the return address on the stack with too high array accesses
	char buffer[4];
	buffer[12] = (func >> (8 * 0)) & 0xff;
	buffer[13] = (func >> (8 * 1)) & 0xff;
	buffer[14] = (func >> (8 * 2)) & 0xff;
	buffer[15] = (func >> (8 * 3)) & 0xff;
}

int main()
{
#if _DEBUG 
	puts("This works only in Release Mode");
	getchar();
#else 
	usualMethod();
#endif

	return 0;
}

