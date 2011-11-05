#ifndef SAMP_MARSHALING_HPP
#define SAMP_MARSHALING_HPP
#include "pawn_marshaling_amx.hpp"
#include "pawn_marshaling_param.hpp"
#include "pawn_marshaling_params.hpp"
//#include "pawn_marshaling_pp.hpp"
#include "SDK/amx/amx.h"
#include <cassert>

namespace pawn {
    //Маршалинг аргументов для вызова павн методов

    template<typename base>
    class marh_base: public marh_amx_t, protected base {
    protected:
        enum {params_count = base::params_count};
        cell cells[params_count + 1];

        marh_base(std::string const& name, marh_collection_t& marh_collection): marh_amx_t(name, marh_collection) {
            cells[0] = params_count * sizeof(cell);
        }
        marh_base(std::string const& name): marh_amx_t(name) {
            cells[0] = params_count * sizeof(cell);
        }

        int call_impl() {
            if (amx && fn) {
                int rezult;
                base::precall(amx, cells);
                rezult = fn(amx, cells);
                base::postcall(amx, cells);
                return rezult;
            }
            else {
                assert(false && "error call null amx");
                return -1;
            }
        }
    };



    //////////////////////////////////////////////////////////////////////////
    //Классы функций павн
    class marh_null_t {};
    
    template<typename t0 = marh_null_t, typename t1 = marh_null_t, typename t2 = marh_null_t, typename t3 = marh_null_t, typename t4 = marh_null_t, typename t5 = marh_null_t, typename t6 = marh_null_t, typename t7 = marh_null_t, typename t8 = marh_null_t, typename t9 = marh_null_t, typename t10 = marh_null_t, typename t11 = marh_null_t, typename t12 = marh_null_t>
    class marh_t: public marh_base<marh_params_13_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12> > {
        typedef marh_base<marh_params_13_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            , typename base::param6_t::connect_type p6
            , typename base::param7_t::connect_type p7
            , typename base::param8_t::connect_type p8
            , typename base::param9_t::connect_type p9
            , typename base::param10_t::connect_type p10
            , typename base::param11_t::connect_type p11
            , typename base::param12_t::connect_type p12
            ) {
            connect(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
            return base::call_impl();
        }
    };

    template<>
    class marh_t<marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_0_t> {
        typedef marh_base<marh_params_0_t> base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call() {
            connect();
            return base::call_impl();
        }
    };

    template<typename t0>
    class marh_t<t0, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_1_t<t0> > {
        typedef marh_base<marh_params_1_t<t0> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            ) {
                connect(p0);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1>
    class marh_t<t0, t1, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_2_t<t0, t1> > {
        typedef marh_base<marh_params_2_t<t0, t1> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            ) {
                connect(p0, p1);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2>
    class marh_t<t0, t1, t2, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_3_t<t0, t1, t2> > {
        typedef marh_base<marh_params_3_t<t0, t1, t2> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            ) {
                connect(p0, p1, p2);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3>
    class marh_t<t0, t1, t2, t3, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_4_t<t0, t1, t2, t3> > {
        typedef marh_base<marh_params_4_t<t0, t1, t2, t3> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            ) {
                connect(p0, p1, p2, p3);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4>
    class marh_t<t0, t1, t2, t3, t4, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_5_t<t0, t1, t2, t3, t4> > {
        typedef marh_base<marh_params_5_t<t0, t1, t2, t3, t4> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            ) {
                connect(p0, p1, p2, p3, p4);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5>
    class marh_t<t0, t1, t2, t3, t4, t5, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_6_t<t0, t1, t2, t3, t4, t5> > {
        typedef marh_base<marh_params_6_t<t0, t1, t2, t3, t4, t5> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            ) {
                connect(p0, p1, p2, p3, p4, p5);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6>
    class marh_t<t0, t1, t2, t3, t4, t5, t6, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_7_t<t0, t1, t2, t3, t4, t5, t6> > {
        typedef marh_base<marh_params_7_t<t0, t1, t2, t3, t4, t5, t6> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            , typename base::param6_t::connect_type p6
            ) {
                connect(p0, p1, p2, p3, p4, p5, p6);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7>
    class marh_t<t0, t1, t2, t3, t4, t5, t6, t7, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_8_t<t0, t1, t2, t3, t4, t5, t6, t7> > {
        typedef marh_base<marh_params_8_t<t0, t1, t2, t3, t4, t5, t6, t7> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            , typename base::param6_t::connect_type p6
            , typename base::param7_t::connect_type p7
            ) {
                connect(p0, p1, p2, p3, p4, p5, p6, p7);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8>
    class marh_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, marh_null_t, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_9_t<t0, t1, t2, t3, t4, t5, t6, t7, t8> > {
        typedef marh_base<marh_params_9_t<t0, t1, t2, t3, t4, t5, t6, t7, t8> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            , typename base::param6_t::connect_type p6
            , typename base::param7_t::connect_type p7
            , typename base::param8_t::connect_type p8
            ) {
                connect(p0, p1, p2, p3, p4, p5, p6, p7, p8);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9>
    class marh_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, marh_null_t, marh_null_t, marh_null_t>:
        public marh_base<marh_params_10_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9> > {
        typedef marh_base<marh_params_10_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            , typename base::param6_t::connect_type p6
            , typename base::param7_t::connect_type p7
            , typename base::param8_t::connect_type p8
            , typename base::param9_t::connect_type p9
            ) {
                connect(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10>
    class marh_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, marh_null_t, marh_null_t>:
        public marh_base<marh_params_11_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10> > {
        typedef marh_base<marh_params_11_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            , typename base::param6_t::connect_type p6
            , typename base::param7_t::connect_type p7
            , typename base::param8_t::connect_type p8
            , typename base::param9_t::connect_type p9
            , typename base::param10_t::connect_type p10
            ) {
                connect(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
                return base::call_impl();
        }
    };

    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10, typename t11>
    class marh_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, marh_null_t>:
        public marh_base<marh_params_12_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11> > {
        typedef marh_base<marh_params_12_t<t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11> > base;
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): base(name, marh_collection) {}
        marh_t(std::string const& name): base(name) {}
        int call(
              typename base::param0_t::connect_type p0
            , typename base::param1_t::connect_type p1
            , typename base::param2_t::connect_type p2
            , typename base::param3_t::connect_type p3
            , typename base::param4_t::connect_type p4
            , typename base::param5_t::connect_type p5
            , typename base::param6_t::connect_type p6
            , typename base::param7_t::connect_type p7
            , typename base::param8_t::connect_type p8
            , typename base::param9_t::connect_type p9
            , typename base::param10_t::connect_type p10
            , typename base::param11_t::connect_type p11
            ) {
                connect(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
                return base::call_impl();
        }
    };

    //Специализация для функции с переменным числом аргументов
    template<>
    class marh_t<std::vector<int>, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t, marh_null_t>: public marh_amx_t {
    public:
        marh_t(std::string const& name, marh_collection_t& marh_collection): marh_amx_t(name, marh_collection) {}
        marh_t(std::string const& name): marh_amx_t(name) {}
        int call(std::vector<int> const& v) {
            if (amx && fn) {
                int rezult;
                std::vector<cell> cells(v.size() + 1);

                //precall
                cells[0] = v.size() * sizeof(cell);
                for (std::size_t param_id = 0, len = v.size(); param_id < len; ++param_id) {
                    cell* phys_addr;
                    amx_Allot(amx, 1, &cells[param_id + 1], &phys_addr);
                    *phys_addr = v[param_id];
                }
                //call
                rezult = fn(amx, &cells[0]);

                //postcall
                for (std::size_t param_id = 0, len = v.size(); param_id < len; ++param_id) {
                    amx_Release(amx, cells[param_id + 1]);
                }

                return rezult;
            }
            else {
                assert(false && "error call null amx");
                return -1;
            }
        }
    };

} // namespace pawn {
#endif // SAMP_MARSHALING_HPP
