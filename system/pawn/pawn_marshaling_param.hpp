#ifndef PAWN_MARSHALING_PARAM_HPP
#define PAWN_MARSHALING_PARAM_HPP
#include "SDK/amx/amx.h"
#include <string>
#include <cstring>


namespace pawn {
    // Классы параметров
    class string_len {
    public:
        enum {val = 256};
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //Данный класс не должен использоваться, а должны использоваться соответствующие специализации
    template<int param_id, typename T>
    class marh_param_t {
    public:
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, int> {
        int val;
    public:
        typedef int connect_type;

        marh_param_t():val(-1) {}

        void connect(connect_type val) {
            this->val = val;
        }
        void precall(AMX* amx, cell* params) {
            params[param_id + 1] = val;
        }
        void postcall(AMX* amx, cell* params) {
        }

        static std::string get_pawn_call_arg() { return "vi"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, unsigned int> {
        unsigned int val;
    public:
        //typedef unsigned int& connect_type;
        typedef unsigned int connect_type;

        marh_param_t():val(-1) {}

        void connect(connect_type val) {
            this->val = val;
        }
        void precall(AMX* amx, cell* params) {
            params[param_id + 1] = val;
        }
        void postcall(AMX* amx, cell* params) {
        }

        static std::string get_pawn_call_arg() { return "vi"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, bool> {
        bool val;
    public:
        //typedef bool& connect_type;
        typedef bool connect_type;

        marh_param_t():val(false) {}

        void connect(connect_type val) {
            this->val = val;
        }
        void precall(AMX* amx, cell* params) {
            params[param_id + 1] = val ? 1 : 0;
        }
        void postcall(AMX* amx, cell* params) {
        }

        static std::string get_pawn_call_arg() { return "vi"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, float> {
        float val;
    public:
        typedef float connect_type;

        marh_param_t():val(-1.0f) {}

        void connect(connect_type val) {
            this->val = val;
        }
        void precall(AMX* amx, cell* params) {
            //params[param_id + 1] = amx_ftoc(val);
            memcpy(&params[param_id + 1], &val, sizeof(float));
        }
        void postcall(AMX* amx, cell* params) {
        }

        static std::string get_pawn_call_arg() { return "vf"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, std::string const&> {
        std::string val;
        cell* phys_addr;
    public:
        typedef std::string const& connect_type;

        marh_param_t(): phys_addr(0) {}

        void connect(connect_type val) {
            this->val = val;
        }
        void precall(AMX* amx, cell* params_t) {
            int len = val.length() + 1;
            amx_Allot(amx, len, params_t + param_id + 1, &phys_addr);
            amx_SetString(phys_addr, val.c_str(), 0, 0, len);
        }
        void postcall(AMX* amx, cell* params_t) {
            amx_Release(amx, params_t[param_id + 1]);
            phys_addr = 0;
        }

        static std::string get_pawn_call_arg() { return "vs"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, std::string&> {
        std::string* val_ptr;
        cell* phys_addr;
    public:
        typedef std::string& connect_type;

        marh_param_t():val_ptr(0), phys_addr(0) {}

        void connect(connect_type val) {
            val_ptr = &val;
        }
        void precall(AMX* amx, cell* params_t) {
            amx_Allot(amx, string_len::val, params_t + param_id + 1, &phys_addr);
        }
        void postcall(AMX* amx, cell* params_t) {
            char buff[string_len::val];

            fix_ru();
            amx_GetString(buff, phys_addr, 0, string_len::val);
            *val_ptr = std::string(buff);

            amx_Release(amx, params_t[param_id + 1]);
            val_ptr = 0;
            phys_addr = 0;
        }
        inline void fix_ru() {
            // Устнаняем проблему с отрицательными буквами (русскими)
            for (cell* it = phys_addr,* end = phys_addr + string_len::val; *it && it < end; ++it) {
                *it &= 0x000000FF;
            }
        }

        static std::string get_pawn_call_arg() { return "vs"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, string_len> {
    public:
        typedef int connect_type;

        marh_param_t() {}

        void connect(connect_type) {}
        void precall(AMX* amx, cell* params) {
            params[param_id + 1] = string_len::val;
        }
        void postcall(AMX* amx, cell* params) {}

        static std::string get_pawn_call_arg() { return "vi"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, int&> {
        int* val_ptr;
        cell* phys_addr;
    public:
        typedef int& connect_type;

        marh_param_t():val_ptr(0), phys_addr(0) {}

        void connect(connect_type val) {
            val_ptr = &val;
        }
        void precall(AMX* amx, cell* params) {
            amx_Allot(amx, 1, params + param_id + 1, &phys_addr);
        }
        void postcall(AMX* amx, cell* params) {
            *val_ptr = *phys_addr;

            amx_Release(amx, params[param_id + 1]);
            val_ptr = 0;
            phys_addr = 0;
        }

        static std::string get_pawn_call_arg() { return "vi"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, unsigned int&> {
        unsigned int* val_ptr;
        cell* phys_addr;
    public:
        typedef unsigned int& connect_type;

        marh_param_t():val_ptr(0), phys_addr(0) {}

        void connect(connect_type val) {
            val_ptr = &val;
        }
        void precall(AMX* amx, cell* params) {
            amx_Allot(amx, 1, params + param_id + 1, &phys_addr);
        }
        void postcall(AMX* amx, cell* params) {
            *val_ptr = *phys_addr;

            amx_Release(amx, params[param_id + 1]);
            val_ptr = 0;
            phys_addr = 0;
        }

        static std::string get_pawn_call_arg() { return "vi"; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<int param_id>
    class marh_param_t<param_id, float&> {
        float* val_ptr;
        cell* phys_addr;
    public:
        typedef float& connect_type;

        marh_param_t():val_ptr(0), phys_addr(0) {}

        void connect(connect_type val) {
            val_ptr = &val;
        }
        void precall(AMX* amx, cell* params) {
            amx_Allot(amx, 1, params + param_id + 1, &phys_addr);
        }
        void postcall(AMX* amx, cell* params) {
            //*val_ptr = amx_ctof(*phys_addr);
            memcpy(val_ptr, phys_addr, sizeof(float));

            amx_Release(amx, params[param_id + 1]);
            val_ptr = 0;
            phys_addr = 0;
        }

        static std::string get_pawn_call_arg() { return "vf"; }
    };
} // namespace pawn {
#endif // PAWN_MARSHALING_PARAM_HPP
