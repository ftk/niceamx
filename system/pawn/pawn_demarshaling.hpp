#ifndef SAMP_DEMARSHALING_HPP
#define SAMP_DEMARSHALING_HPP

#include <string>
#include <cstring>
#include <cassert>

#include "SDK/amx/amx.h"
#include "SDK/amxinline.h"

#include "util/utils.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


namespace pawn {
    //Демаршалинг pawn аргументов

    //Класс аргумента
    template<int param_id, typename T>
    class demarh_t
    {
        T val;
    public:
        demarh_t(AMX* amx, cell* params)
        {
            val = static_cast<T>(params[param_id + 1]);
        }
        T get() const
        {
            return val;
        }
    };

    template<int param_id>
    class demarh_t<param_id, bool>
    {
        bool val;
    public:
        demarh_t(AMX* amx, cell* params)
        {
            val = 0 != params[param_id + 1];
        }
        bool get() const
        {
            return val;
        }
    };
    
    template<int param_id>
    class demarh_t<param_id, float>
    {
        float val;
        static_assert(sizeof(float) == sizeof(cell), "Unsupported cell size");
    public:
        demarh_t(AMX* amx, cell* params)
        {
            memcpy(&val, &params[param_id + 1], sizeof(float));
        }
        float get() const
        {
            return val;
        }
    };
    template<int param_id>
    class demarh_t<param_id, const std::string&>
    {
        std::string val;
    public:
        demarh_t(AMX* amx, cell* params)
        {
            char buff[129];

            //amx_GetAddr(amx, params[param_id + 1], &cstr);
            //amx_GetString(buff, cstr, 0, sizeof(buff)/sizeof(buff[0]));
            amx_get_string(amx, params[param_id + 1], buff, util::arrayof(buff));
            val = std::string(buff);
            //val.resize(129);
            //int len = amx_get_string(amx, params[param_id + 1], &(val[0]), 130);
            //val.resize(len-1);

        }
        const std::string& get() const
        {
            return val;
        }
    };
    template<int param_id>
    class demarh_t<param_id, std::string&>
    {
        std::string val;
        cell * cstr;
    public:
        demarh_t(AMX* amx, cell* params)
        {
            char buff[129];
            cstr = amx_get_addr(amx, params[param_id + 1]);
            amx_get_string(amx, params[param_id + 1], buff, sizeof(buff)/sizeof(buff[0]));
            val = std::string(buff);
            
        }
        
        virtual ~demarh_t()
        {
            //strncpy(cstr, val.c_str(), 128);
            const char * valstr = val.c_str();
            while((*(cstr++) = *(valstr++) & 0x000000FF))
              continue;
            //amx_set_string(amx, params[param_id + 1], val.data(), val.size());
        }
        
        std::string& get()
        {
            return val;
        }
    };

} // namespace pawn {

#endif // SAMP_DEMARSHALING_HPP
