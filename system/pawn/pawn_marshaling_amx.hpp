#ifndef PAWN_MARSHALING_AMX_HPP
#define PAWN_MARSHALING_AMX_HPP
#include "SDK/amx/amx.h"
#include <string>
#include <vector>

namespace pawn {
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Классы описания методов
    class marh_amx_t;

    // Колекция описателей. Используется для инициализации/финализации группы
    class marh_collection_t {
    public:
        typedef std::vector<marh_amx_t*> marhs_t;
        marhs_t marhs;

        void add(marh_amx_t* item)
        {
            marhs.push_back(item);
        }
    };

    class marh_amx_t {
    private:
        std::string const name;
    protected:
        AMX* amx;
        AMX_NATIVE fn;

        marh_amx_t(std::string const& name, marh_collection_t& marh_collection): name(name), amx(0), fn(0) 
        {
          marh_collection.add(this);
        }
        marh_amx_t(std::string const& name) : name(name), amx(0), fn(0) 
        {}

    public:
        // В случае ошибки возращает false
        bool init(AMX* new_amx)
        {
            if (new_amx) {
                fn = marh_find_function(new_amx, name);
                if (fn) {
                    amx = new_amx;
                    return true;
                }
            }
            return false;
        }


    public:
        //Возращает адрес метода павн по его имени или 0 в случае неудачи
        static AMX_NATIVE marh_find_function(AMX* amx, std::string const& name)
        {
            if(!amx) {
                return NULL;
            }

            int index;
            if(amx_FindNative(amx, name.c_str(), &index) != AMX_ERR_NONE)
			{
                //The command cannot be found.
                return NULL;
            }

            // Proceed with locating the memory address for this function;
            AMX_HEADER *hdr = (AMX_HEADER *)amx->base;
            unsigned int call_addr = (unsigned int)((AMX_FUNCSTUB *)
                ((char *)(hdr) + (hdr)->natives + hdr->defsize * index))->address;


            return (AMX_NATIVE)call_addr;
        }

    };

    

} // namespace pawn {

#endif // PAWN_MARSHALING_AMX_HPP
