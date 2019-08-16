// Use cl (from Windows SDK) like "cl rdtsc_win.cpp"

#include <stdio.h>
#include <intrin.h>

#pragma intrinsic(__rdtsc)

typedef unsigned long long ull;

void pafish_check()
{
	int arr[4];
    ull r1 = __rdtsc(); //rdtsc();
    __cpuid(arr, 0);
    ull r2 = __rdtsc();
    std::cout << std::dec << r2 - r1 << std::endl;
}

int main()
{
    std::cout << "0x" << std::hex << __rdtsc() << std::endl;
    pafish_check();
    std::cin.get();
    return 0;
}