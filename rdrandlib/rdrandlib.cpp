//------------------------------------------------------------------------------------
// Copyright (c) 2014 Dilshan R Jayakody. [jayakody2000lk@gmail.com]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//------------------------------------------------------------------------------------

#include "stdafx.h"
#include "rdrandlib.h"

#define RDRAND_MASK	0x40000000
#define CPUID_SIZE 0x20

RDRANDLIB_API UCHAR __stdcall GenerateRandomSet(USHORT setSize, UINT *setBuffer)
{
	int cpuInfo[4] = { 0, 0, 0, 0 };
	char cpuIDString[CPUID_SIZE];

	__cpuid(cpuInfo, 0);
	memset(cpuIDString, 0, sizeof(cpuIDString));

	*((int*)cpuIDString) = cpuInfo[1];
	*((int*)(cpuIDString + 4)) = cpuInfo[3];
	*((int*)(cpuIDString + 8)) = cpuInfo[2];

	if (strcmp(cpuIDString, "GenuineIntel") != 0)
	{
		return RDRAND_NOT_SUPPORT;
	}

	__cpuid(cpuInfo, 1);
	if ((cpuInfo[2] & RDRAND_MASK) != RDRAND_MASK)
	{
		return RDRAND_NOT_SUPPORT;
	}

	for (INT tmpPos = 0; tmpPos < setSize; tmpPos++)
	{
		__asm 
		{
			xor eax, eax
			xor edx, edx
			xor ecx, ecx

			mov	eax, DWORD PTR tmpPos
			mov	ecx, DWORD PTR setBuffer
			lea	edx, DWORD PTR [ecx + eax * 4]

			__asm _emit 0x0F
			__asm _emit 0xC7
			__asm _emit 0xF0

			jc rdrand_result
			jmp rdrand_exit

		rdrand_result:
			mov[edx], eax

		rdrand_exit:
		};
	}

	return RDRAND_SUPPORT;
}