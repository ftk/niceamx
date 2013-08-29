#ifndef PAWN_MARH_DEBUG
#define PAWN_MARH_DEBUG

#include <string>
#include <ostream>
#include "marh_param.hpp"

namespace pawn
{


template<typename T>
struct param_to_string
{
    inline static std::string to_string(T p)
    {
        //return std::to_string(p);
        return boost::lexical_cast<std::string>(p);
    }
};

template<>
struct param_to_string<std::string&>
{
    inline static std::string to_string(const std::string&)
    {
        return "\"\"";
    }
};
template<>
struct param_to_string<const std::string&>
{
    inline static std::string to_string(const std::string& p)
    {
        return '"' + p + '"';
    }
};

template<>
struct param_to_string<string_len>
{
    inline static std::string to_string(string_len)
    {
        return "256";
    }
};


// params


template <typename Arg1, typename... Args>
struct params_to_string : public params_to_string<Args...>
{
    inline static std::string to_string(Arg1 a1, Args... args)
    {
        return param_to_string<Arg1>::to_string(a1) + ", " + params_to_string<Args...>::to_string(args...);
    }
};

template <typename ArgLast>
struct params_to_string<ArgLast>
{
    inline static std::string to_string(ArgLast a)
    {
        return param_to_string<ArgLast>::to_string(a);
    }
};
/*
template <>
struct params_to_string<void>
{
    inline static std::string to_string()
    {
        return "";
    }
};*/
/*
template<typename... Args>
inline void enum_params(std::ostream& s, Args... args)
{

}

template <int param_id, typename Arg1, typename... Args>
inline std::ostream& operator << (std::ostream& s, const marh_param_t<param_id, Arg1, Args...>& marh)
{
    s << marh.name << '(';
    enum_params(s, args...);
    s << ')';
}*/

} // pawn


#endif
