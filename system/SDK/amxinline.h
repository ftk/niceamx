#ifndef AMXINLINE_H
#define AMXINLINE_H

#include "amx/amx.h"
#include <cstddef>
#include <cstring>

namespace pawn {

static inline unsigned char * amx_data(const AMX * amx)
{
	return (amx->data!=NULL) ? amx->data : 
        amx->base + static_cast<std::ptrdiff_t>(reinterpret_cast<AMX_HEADER *>(amx->base)->dat);
}


static inline void amx_allot(AMX * amx, int cells, cell& amx_addr)
{
    amx_addr = amx->hea;
    amx->hea += sizeof(cell) * cells;
}

static inline void amx_release(AMX * amx, cell amx_addr)
{
    if (amx->hea > amx_addr)
        amx->hea = amx_addr;
}

static inline cell * amx_get_addr(const AMX * amx, cell amx_addr)
{
    return reinterpret_cast<cell *>(amx_data(amx) + static_cast<std::ptrdiff_t>(amx_addr));
}



inline void amx_set_string(AMX * amx, cell amx_addr, const char * src, std::size_t len)
{
    const char * src_it = src;

    cell * dst_it = amx_get_addr(amx, amx_addr),
            * dst_end = dst_it + static_cast<std::ptrdiff_t>(len + 1);

    while(dst_it != dst_end)
    {
        *dst_it = static_cast<unsigned char>(*src_it);
        if(!*src_it) break;
        ++dst_it; ++src_it;
    }
    if(dst_it == dst_end)
        *(dst_it-1) = 0;
}

inline int amx_get_string(const AMX * amx, cell amx_addr, char * dst, std::size_t len)
{
    char * dst_it = dst;
    const char * dst_end = dst + static_cast<std::ptrdiff_t>(len + 1);

    const cell * src_it = amx_get_addr(amx, amx_addr);

    while(dst_it != dst_end)
    {
        *dst_it = static_cast<unsigned char>(*src_it);
        if(!*src_it) break;
        ++dst_it; ++src_it;
    }
    if(dst_it == dst_end)
        *(dst_it-1) = '\0';
    return(dst_it - dst);
}




inline void cell_to_float(float * dst, const cell * src)
{
    static_assert(sizeof(float) == sizeof(cell), "Unsupported cell/float size");
    memcpy(dst, src, sizeof(float));
}

inline void float_to_cell(cell * dst, const float * src)
{
    static_assert(sizeof(float) == sizeof(cell), "Unsupported cell/float size");
    memcpy(dst, src, sizeof(float));
}


} //

#endif // AMXINLINE_H
