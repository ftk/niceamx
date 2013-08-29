#ifndef PAWN_MARH_PARAM
#define PAWN_MARH_PARAM

#include "SDK/amx/amx.h"

#include "SDK/amxinline.h"

#include <cstring>
#include <string>


#include <boost/lexical_cast.hpp>


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

namespace pawn {



static_assert(sizeof(cell) == sizeof(float), "Unsupported cell size");

// Классы параметров
struct string_len 
{
    enum {val = 256};
    //static const int val = 256;
    
    string_len(int) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////
//Данный класс не должен использоваться, а должны использоваться соответствующие специализации
template<int param_id, typename T>
class marh_param_t {
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////
template<int param_id>
class marh_param_t<param_id, int> 
{
public:
    inline void precall(AMX* amx, cell* params, int val) 
    {
        params[param_id + 1] = val;
    }
    inline void postcall(AMX* amx, cell* params, int val) 
    {
    }

    static const char format = 'i';
};

template<int param_id>
class marh_param_t<param_id, unsigned int> 
{
public:
    inline void precall(AMX* amx, cell* params, unsigned int val) 
    {
        params[param_id + 1] = val;
    }
    inline void postcall(AMX* amx, cell* params, unsigned int val) 
    {
    }
    static const char format = 'i';
};

template<int param_id>
class marh_param_t<param_id, float> 
{
public:
    inline void precall(AMX* amx, cell* params, float val) 
    {
        memcpy(&params[param_id + 1], &val, sizeof(float));
    }
    inline void postcall(AMX* amx, cell* params, float val) 
    {
    }
    static const char format = 'f';
};

template<int param_id>
class marh_param_t<param_id, bool> 
{
public:
    inline void precall(AMX* amx, cell* params, bool val) 
    {
        params[param_id + 1] = val ? 1 : 0;
    }
    inline void postcall(AMX* amx, cell* params, bool val) 
    {
    }
    static const char format = 'i';
};


template<int param_id>
class marh_param_t<param_id, const std::string&> 
{
public:
    inline void precall(AMX* amx, cell* params_t, const std::string& val) 
    {
        int len = val.size();
        amx_allot(amx, len + 1, params_t[param_id + 1]);
        cell* phys_addr = amx_get_addr(amx, params_t[param_id + 1]);
        //amx_Allot(amx, len + 1, params_t + param_id + 1, &phys_addr);
        //amx_SetString(phys_addr, val.c_str(), 0, 0, len);
        const char * src = val.data();
        cell * it, * end;
        for(it = phys_addr, end = phys_addr + len; it != end; ++it, ++src)
        {
        	*it = static_cast<cell>(static_cast<unsigned char>(*src));
        }
        *it = 0;
    }
    inline void postcall(AMX* amx, cell* params_t, const std::string& val)
    {
        //amx_Release(amx, params_t[param_id + 1]);
        amx_release(amx, params_t[param_id + 1]);
    }
    static const char format = 's';
};

template<int param_id>
class marh_param_t<param_id, std::string&> 
{
    //cell* phys_addr;
public:
    inline void precall(AMX* amx, cell* params_t, std::string& val) 
    {
        //amx_Allot(amx, string_len::val, params_t + param_id + 1, &phys_addr);
        amx_allot(amx, string_len::val, params_t[param_id + 1]);
    }
    inline void postcall(AMX* amx, cell* params_t, std::string& val)
    {
		char buff[string_len::val];
		
        cell* phys_addr = amx_get_addr(amx, params_t[param_id + 1]);

		char * pbuf = buff;
		for (cell* it = phys_addr,* end = phys_addr + string_len::val; *it && it != end; ++it, ++pbuf)
		{
            *pbuf = static_cast<unsigned char>(*it & 0xff);
		}
		*pbuf = '\0';
		val = buff;
        amx_release(amx, params_t[param_id + 1]);
    }
    static const char format = 'S';
};

template<int param_id>
class marh_param_t<param_id, string_len> 
{
public:
    inline void precall(AMX* amx, cell* params, string_len) 
    {
        params[param_id + 1] = string_len::val;
    }
    inline void postcall(AMX* amx, cell* params, string_len) 
    {
    }
    static const char format = 'i';
};

template<int param_id>
class marh_param_t<param_id, int&> 
{
    //cell* phys_addr;
public:
    inline void precall(AMX* amx, cell* params_t, int& val) 
    {
        //amx_Allot(amx, 1, params_t + param_id + 1, &phys_addr);
        amx_allot(amx, 1, params_t[param_id + 1]);
    }
    inline void postcall(AMX* amx, cell* params_t, int& val)
    {
        val = *(amx_get_addr(amx, params_t[param_id + 1]));
        amx_release(amx, params_t[param_id + 1]);
    }
    static const char format = 'I';
};

template<int param_id>
class marh_param_t<param_id, unsigned int&> 
{
    //cell* phys_addr;
public:
    inline void precall(AMX* amx, cell* params_t, unsigned int& val) 
    {
        amx_allot(amx, 1, params_t[param_id + 1]);
    }
    inline void postcall(AMX* amx, cell* params_t, unsigned int& val)
    {
        val = *(amx_get_addr(amx, params_t[param_id + 1]));
        amx_release(amx, params_t[param_id + 1]);
    }
    static const char format = 'I';
};

template<int param_id>
class marh_param_t<param_id, float&> 
{
	cell* phys_addr;
public:
    inline void precall(AMX* amx, cell* params_t, float& val) 
    {
        //amx_Allot(amx, 1, params_t + param_id + 1, &phys_addr);
        amx_allot(amx, 1, params_t[param_id + 1]);
    }
    inline void postcall(AMX* amx, cell* params_t, float& val)
    {
        //float t;
        //memcpy(&t, phys_addr, sizeof(float));
        //val = t;
        cell_to_float(&val, amx_get_addr(amx, params_t[param_id + 1]));
		
        amx_release(amx, params_t[param_id + 1]);
    }
    static const char format = 'F';
};






} // pawn

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


#endif
