#ifndef PAWN_MARH_VAR
#define PAWN_MARH_VAR

#include "config.h"

#include "SDK/amx/amx.h"
#include "marh_param.hpp"
#include "marh_debug.hpp"
#include "pawn_marshaling_amx.hpp"

#include <cassert>



namespace pawn {



// specialization for 2+ arguments

template <int param_id, typename Arg1, typename... Args>
class marh_params_t : public marh_params_t<param_id + 1, Args...>
{
private:
	marh_param_t<param_id, Arg1> param;
	
	typedef marh_params_t<param_id + 1, Args...> base;
public:
	
    marh_params_t(const std::string& name, marh_collection_t& marh_collection) : base(name, marh_collection)
    {
        //base::format[param_id] = marh_param_t<param_id, Arg1>::format;
    }
	marh_params_t(const std::string& name) : base(name) {}

    //using base::marh_params_t;
	
	inline int call(Arg1 a1, Args... args)
	{
		int result;
		
		param.precall(base::amx, base::cells, a1);
		
		result = base::call(args...);
		
		param.postcall(base::amx, base::cells, a1);
		
		return result;
	}
    static_assert(sizeof...(Args) + param_id + 1 == base::params_count, "params count does not match");

    inline std::string to_string(Arg1 a1, Args... args)
    {
        return base::name + '(' + params_to_string<Arg1, Args...>::to_string(a1, args...) + ')';
    }

};

// specialization for 1 argument

template <int param_id, typename ArgLast>
class marh_params_t<param_id, ArgLast> : public marh_params_t<param_id + 1, void>
{
private:
	marh_param_t<param_id, ArgLast> param;
	
    typedef marh_params_t<param_id + 1, void> base;
public:

    marh_params_t(const std::string& name, marh_collection_t& marh_collection) : base(name, marh_collection)
    {
        //base::format[param_id] = marh_param_t<param_id, ArgLast>::format;
    }
	marh_params_t(const std::string& name) : base(name) {}

    //using base::marh_params_t;

	inline int call(ArgLast arg)
	{
		int result;
		
		param.precall(base::amx, base::cells, arg);
		
		result = base::call();
		
		param.postcall(base::amx, base::cells, arg);
		
		return result;
	}
    static_assert(param_id + 1 == base::params_count, "params count does not match");

    inline std::string to_string(ArgLast a)
    {
        return base::name + '(' + params_to_string<ArgLast>::to_string(a) + ')';
    }

};

// specialization for no arguments

template <int param_id>
class marh_params_t<param_id, void> : public marh_amx_t
{
public:
    enum { params_count = param_id };
protected:
    //AMX * amx;
    cell cells[params_count + 1];
    //AMX_NATIVE fn;

    //static char format[params_count + 1];

public:
    marh_params_t(const std::string& name) : marh_amx_t(name)
    {
        cells[0] = params_count * sizeof(cell);
        //format[params_count] = '\0';
    }
    marh_params_t(const std::string& name, marh_collection_t& marh_collection) : marh_amx_t(name, marh_collection)
    {
        cells[0] = params_count * sizeof(cell);
        //format[params_count] = '\0';
    }


    inline int call()
    {
        assert(fn && "null fn");
        assert(amx && "null amx");
        return fn(amx, cells);
    }

    inline std::string to_string()
    {
        return name + "()";
    }

};



template <typename Arg1 = void, typename... Args>
using marh_t = marh_params_t<0, Arg1, Args...>;

//using marh0_t = marh_params0_t<0>;

} // namespace pawn

#endif
