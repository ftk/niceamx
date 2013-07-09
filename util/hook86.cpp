#include "hook86.h"


#ifdef WIN32
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/mman.h>
#include <time.h>
#include <alloca.h>
#include <stdlib.h>
#include <unistd.h>

#endif

#include <cstring>
#include <algorithm>

#include <boost/cstdint.hpp>

namespace util {

bool unprotect(void * addr, std::size_t size)
{
#ifndef WIN32
    std::size_t page_size = getpagesize();
    std::ptrdiff_t aligned_addr = ((reinterpret_cast<std::ptrdiff_t>(addr) / page_size) * page_size);
    std::size_t count = (size / page_size) * page_size + page_size * 2;
    return !mprotect(reinterpret_cast <void*>(aligned_addr), count, PROT_READ | PROT_WRITE | PROT_EXEC);
#else
    DWORD old;
    return VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &old);
#endif
}

bool set_hook_x86(void * from, void * to, char mem[5])
{
    static_assert(sizeof(char *) == 4, "not on x86");

    *((unsigned char *)mem) = 0xE9;

    // mem[1...4] now holds (to-from-5)
    // little endian only (?)
    //*((char **)(mem + 1)) = (char *)((char *)to - (char *)from) - 5;
    boost::uint32_t off = boost::uint32_t((char *)to - (char *)from) - 5;
    ::memcpy(mem + 1, &off, 4);

    if(unprotect(from, 5))
    {
        std::swap_ranges(mem, mem + 5, (char *) from);
        return true;
    }
    return false;
}

bool set_hook_x86(void * from, void * to)
{
    char mem[5];
    return set_hook_x86(from, to, mem);
}


} // util
