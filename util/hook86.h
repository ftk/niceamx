#ifndef UTIL_HOOK86_H
#define UTIL_HOOK86_H

#include <cstddef>


namespace util {

bool unprotect(void * addr, std::size_t size);


bool set_hook_x86(void * from, void * to, char mem[5]);
bool set_hook_x86(void * from, void * to);


} // util

#endif

