#ifndef UTIL_HASH_HPP
#define UTIL_HASH_HPP

#include <boost/cstdint.hpp>

namespace util {


// to lower/upper case
constexpr inline bool is_lower_ascii(char c)
{
    return c > 0x60 && c < 0x7B;
}
constexpr inline bool is_upper_ascii(char c)
{
    return c > 0x40 && c < 0x5B;
}
// а - я
constexpr inline bool is_lower_1251_32(unsigned char c)
{
    return c > 0xDF;// && c <= 0xFF;
}
constexpr inline bool is_upper_1251_32(unsigned char c)
{
    return c > 0xBF && c < 0xE0;
}
// ё
constexpr inline bool is_lower_1251_33(unsigned char c)
{
    return c == 0xB8;
}
constexpr inline bool is_upper_1251_33(unsigned char c)
{
    return c == 0xA8;
}

constexpr inline char to_lower_ascii(char c)
{
    return is_upper_ascii(c) ? (c|0x20) : c;
}
constexpr inline char to_upper_ascii(char c)
{
    return is_lower_ascii(c) ? (c&0xDF) : c;
}

constexpr inline char to_lower_1251_32(unsigned char c)
{
    return is_upper_1251_32(c) ? (c|0x20) : c;
}
constexpr inline char to_upper_1251_32(unsigned char c)
{
    return is_lower_1251_32(c) ? (c&0xDF) : c;
}

constexpr inline char to_lower_1251_33(unsigned char c)
{
    return is_upper_1251_33(c) ? 0xB8 : c;
}
constexpr inline char to_upper_1251_33(unsigned char c)
{
    return is_lower_1251_33(c) ? 0xA8 : c;
}



//template <typename T>
constexpr inline unsigned char to_lower(unsigned char ch)
{
    // supports cp1251 and ascii
    return (ch >= 'A' && ch <= 'Z') ? (ch - 'A' + 'a') :
           // cp1251
           ((ch >= 0xC0 && ch <= 0xDF) ? (ch + 0x20) :
           ((ch == 0xA8) ? 0xB8 : ch));
}

//template <typename T>
constexpr inline unsigned char to_upper(unsigned char ch)
{
    // supports cp1251 and ascii
    return (ch >= 'a' && ch <= 'z') ? (ch - 'a' + 'A') :
           // cp1251
           ((ch >= 0xE0 /*&& ch <= 0xFF*/) ? (ch - 0x20) :
           ((ch == 0xB8) ? 0xA8 : ch));
}


typedef boost::uint64_t hash_t;

// https://github.com/elanthis/constexpr-hash-demo/blob/master/test.cpp

static constexpr hash_t fnv1a_basis = 14695981039346656037ULL;
static constexpr hash_t fnv1a_prime = 1099511628211ULL;

// compile-time hash helper function
constexpr inline hash_t const_hash_one(char c, const char* remain, hash_t value)
{
    return c == 0 ? value : const_hash_one(remain[0], remain + 1, (value ^ c) * fnv1a_prime);
}

constexpr inline hash_t const_hash_one_nocase(char c, const char* remain, hash_t value)
{
    return c == 0 ? value : const_hash_one_nocase(to_lower(remain[0]), remain + 1, (value ^ c) * fnv1a_prime);
}


// compile-time hash
constexpr inline hash_t const_hash(const char * str)
{
    return const_hash_one(str[0], str + 1, fnv1a_basis);
}
constexpr inline hash_t const_hash_nocase(const char * str)
{
    return const_hash_one_nocase(to_lower(str[0]), str + 1, fnv1a_basis);
}



// run-time hash
inline hash_t hash_rt(const char* str)
{
	hash_t hash = fnv1a_basis;
	while (*str) 
	{
		hash ^= *(str++);
		hash *= fnv1a_prime;
	}
	return hash;
}

inline hash_t hash_rt_nocase(const char* str)
{
    hash_t hash = fnv1a_basis;
    while (*str)
    {
        hash ^= to_lower(*(str++));
        hash *= fnv1a_prime;
    }
    return hash;
}


template <hash_t N>
struct const_test
{
	enum
	{
		value = N
	};
};




} // util


#endif //
