
// only 1 arg 
#define MAKE_FUNC(returns,name,argtype,argname,...) \
inline returns name (const argtype * argname /* ptr */, __VA_ARGS__ ) \
{ \
return name(* argname); \
} \
returns name (const argtype & argname /* cref */, __VA_ARGS__ ) \
/* experimental */

/*
 * MAKE_FUNC(bool, func, player, p)
 * {
 * }
 */
