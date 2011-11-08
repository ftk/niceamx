#ifndef SAMP_DEMARSHALING_HPP
#define SAMP_DEMARSHALING_HPP

#include <string>
#include <cassert>

#include "SDK/amx/amx.h"

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
            assert(params[0] >= static_cast<cell>(param_id * sizeof(cell)));
            val = static_cast<T>(params[param_id + 1]);
        }
        T get()
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
            assert(params[0] >= static_cast<cell>(param_id * sizeof(cell)));
            val = 0 != params[param_id + 1];
        }
        bool get()
        {
            return val;
        }
    };

    template<int param_id>
    class demarh_t<param_id, std::string>
    {
        std::string val;
    public:
        demarh_t(AMX* amx, cell* params)
        {
            assert(params[0] >= static_cast<cell>(param_id * sizeof(cell)));
            char buff[129];
            cell* cstr;

            amx_GetAddr(amx, params[param_id + 1], &cstr);
            amx_GetString(buff, cstr, 0, sizeof(buff)/sizeof(buff[0]));
            val = std::string(buff);
            
        }
        std::string& get()
        {
            return val;
        }
    };

} // namespace pawn {

#endif // SAMP_DEMARSHALING_HPP
