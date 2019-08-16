// Use g++ (from MINGW gcc 6.3.0) like "g++ rdtsc_asm.cpp"

#include <iostream>

typedef unsigned long long ull;

inline ull rdtsc() {
	unsigned int lo, hi;
	asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
	return ((ull)hi << 32) | lo;
}

inline void cpuid() {
__asm__ volatile("cpuid" : /* no output */ : "a"(0x00));   
}

void pafish_check()
{
    ull r1 = rdtsc();
    cpuid();
    ull r2 = rdtsc();
    std::cout << std::dec << r2 - r1 << std::endl;
}

int main()
{
    rdtsc();
    return 0;
}