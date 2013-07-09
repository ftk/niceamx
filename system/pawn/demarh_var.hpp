#ifndef DEMARH_VAR_HPP
#define DEMARH_VAR_HPP

#include "signal.hpp"
#include "pawn_demarshaling.hpp"

#include <tuple>
#include <cassert>


namespace pawn {


template <int I, typename... Args>
struct get_type
{
    // get_type<1, int, float, double>::type == float
    using type = typename std::tuple_element<I, std::tuple<Args...> >::type;
};

template <int N, typename... TArgs>
struct arg_pack
{
    typedef typename get_type<N-1, TArgs...>::type arg_type;

    template <typename Callable, typename... Args>
    static inline int apply(Callable& fun, AMX * amx, cell * params, Args... args)
    {
        static_assert(sizeof...(TArgs) == N + sizeof...(Args), "Wrong arguments");

        demarh_t<N-1, arg_type> arg(amx, params);

        return arg_pack<N-1, TArgs...>::apply(fun, amx, params, arg.get(), args...);
    }
};

template <typename... TArgs>
struct arg_pack<0, TArgs...>
{

    template <typename Callable, typename... Args>
    static inline int apply(Callable& fun, AMX * /*amx*/, cell * /*params*/, Args... args)
    {
        static_assert(sizeof...(TArgs) == sizeof...(Args), "Wrong arguments");
        // all demarshalled arguments are now in args...
        return fun(args...);
    }
};


template <typename... TArgs>
inline int arg_pack_helper(signals::signal<TArgs...>& f, AMX * amx, cell * params)
{
    assert(params[0] == sizeof...(TArgs) * sizeof(cell));
    return arg_pack<sizeof...(TArgs), TArgs...>::apply(f, amx, params);
}





} // pawn


#endif // DEMARH_VAR_HPP

