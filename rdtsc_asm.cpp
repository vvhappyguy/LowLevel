// Use g++ (from MINGW gcc 6.3.0) like "g++ rdtsc_asm.cpp" or "g++ .\rdtsc_asm.cpp -static -static-libgcc -static-libstdc++ -o avg_rdtsc.exe" if you want static linking libs

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

static inline unsigned long long rdtsc_diff_vmexit() {
	unsigned long long ret, ret2;
	unsigned eax, edx;
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	/* vm exit forced here. it uses: eax = 0; cpuid; */
	__asm__ volatile("cpuid" : /* no output */ : "a"(0x00));
	/**/
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret2  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	return ret2 - ret;
}

int cpu_rdtsc_force_vmexit() {
	int i;
	unsigned long long avg = 0;
	for (i = 0; i < 10; i++) {
		avg = avg + rdtsc_diff_vmexit();
	}
	avg = avg / 10;
    std::cout << "AVG: " << std::dec << avg << std::endl;
	return (avg < 1000 && avg > 0) ? FALSE : TRUE;
}

int main()
{
    std::cout << "RDTSC 1:" << std::hex << rdtsc() << std::endl;
    cpu_rdtsc_force_vmexit();
    std::cout << "RDTSC 2:" << std::hex << rdtsc() << std::endl;
    return 0;
}