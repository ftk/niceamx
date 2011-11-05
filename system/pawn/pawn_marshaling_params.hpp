#ifndef PAWN_MARSHALING_PARAMS_HPP
#define PAWN_MARSHALING_PARAMS_HPP
#include "SDK/amx/amx.h"
#include "pawn_marshaling_param.hpp"

namespace pawn {
    //////////////////////////////////////////////////////////////////////////
    struct marh_params_0_t {
        enum {params_count = 0};

        void connect() {}
        void precall(AMX* amx, cell* params) {}
        void postcall(AMX* amx, cell* params) {}

        /*static std::string get_pawn_call_args() { return ""; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0>
    struct marh_params_1_t {
        typedef marh_param_t<0, t0> param0_t;
        param0_t param0;
        enum {params_count = 1};

        void connect(
              typename param0_t::connect_type p0
            ) {
                param0.connect(p0);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
            param0_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1>
    struct marh_params_2_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        param0_t param0;
        param1_t param1;
        enum {params_count = 2};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            ) {
                param0.connect(p0);
                param1.connect(p1);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2>
    struct marh_params_3_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        enum {params_count = 3};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3>
    struct marh_params_4_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        enum {params_count = 4};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4>
    struct marh_params_5_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        enum {params_count = 5};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5>
    struct marh_params_6_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        enum {params_count = 6};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6>
    struct marh_params_7_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        typedef marh_param_t<6, t6> param6_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        param6_t param6;
        enum {params_count = 7};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            , typename param6_t::connect_type p6
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
                param6.connect(p6);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
            param6.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
            param6.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            + ", " + param6_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7>
    struct marh_params_8_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        typedef marh_param_t<6, t6> param6_t;
        typedef marh_param_t<7, t7> param7_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        param6_t param6;
        param7_t param7;
        enum {params_count = 8};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            , typename param6_t::connect_type p6
            , typename param7_t::connect_type p7
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
                param6.connect(p6);
                param7.connect(p7);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
            param6.precall(amx, params);
            param7.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
            param6.postcall(amx, params);
            param7.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            + ", " + param6_t::get_pawn_call_arg()
            + ", " + param7_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8>
    struct marh_params_9_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        typedef marh_param_t<6, t6> param6_t;
        typedef marh_param_t<7, t7> param7_t;
        typedef marh_param_t<8, t8> param8_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        param6_t param6;
        param7_t param7;
        param8_t param8;
        enum {params_count = 9};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            , typename param6_t::connect_type p6
            , typename param7_t::connect_type p7
            , typename param8_t::connect_type p8
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
                param6.connect(p6);
                param7.connect(p7);
                param8.connect(p8);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
            param6.precall(amx, params);
            param7.precall(amx, params);
            param8.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
            param6.postcall(amx, params);
            param7.postcall(amx, params);
            param8.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            + ", " + param6_t::get_pawn_call_arg()
            + ", " + param7_t::get_pawn_call_arg()
            + ", " + param8_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9>
    struct marh_params_10_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        typedef marh_param_t<6, t6> param6_t;
        typedef marh_param_t<7, t7> param7_t;
        typedef marh_param_t<8, t8> param8_t;
        typedef marh_param_t<9, t9> param9_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        param6_t param6;
        param7_t param7;
        param8_t param8;
        param9_t param9;
        enum {params_count = 10};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            , typename param6_t::connect_type p6
            , typename param7_t::connect_type p7
            , typename param8_t::connect_type p8
            , typename param9_t::connect_type p9
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
                param6.connect(p6);
                param7.connect(p7);
                param8.connect(p8);
                param9.connect(p9);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
            param6.precall(amx, params);
            param7.precall(amx, params);
            param8.precall(amx, params);
            param9.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
            param6.postcall(amx, params);
            param7.postcall(amx, params);
            param8.postcall(amx, params);
            param9.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            + ", " + param6_t::get_pawn_call_arg()
            + ", " + param7_t::get_pawn_call_arg()
            + ", " + param8_t::get_pawn_call_arg()
            + ", " + param9_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10>
    struct marh_params_11_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        typedef marh_param_t<6, t6> param6_t;
        typedef marh_param_t<7, t7> param7_t;
        typedef marh_param_t<8, t8> param8_t;
        typedef marh_param_t<9, t9> param9_t;
        typedef marh_param_t<10, t10> param10_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        param6_t param6;
        param7_t param7;
        param8_t param8;
        param9_t param9;
        param10_t param10;
        enum {params_count = 11};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            , typename param6_t::connect_type p6
            , typename param7_t::connect_type p7
            , typename param8_t::connect_type p8
            , typename param9_t::connect_type p9
            , typename param10_t::connect_type p10
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
                param6.connect(p6);
                param7.connect(p7);
                param8.connect(p8);
                param9.connect(p9);
                param10.connect(p10);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
            param6.precall(amx, params);
            param7.precall(amx, params);
            param8.precall(amx, params);
            param9.precall(amx, params);
            param10.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
            param6.postcall(amx, params);
            param7.postcall(amx, params);
            param8.postcall(amx, params);
            param9.postcall(amx, params);
            param10.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            + ", " + param6_t::get_pawn_call_arg()
            + ", " + param7_t::get_pawn_call_arg()
            + ", " + param8_t::get_pawn_call_arg()
            + ", " + param9_t::get_pawn_call_arg()
            + ", " + param10_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10, typename t11>
    struct marh_params_12_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        typedef marh_param_t<6, t6> param6_t;
        typedef marh_param_t<7, t7> param7_t;
        typedef marh_param_t<8, t8> param8_t;
        typedef marh_param_t<9, t9> param9_t;
        typedef marh_param_t<10, t10> param10_t;
        typedef marh_param_t<11, t11> param11_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        param6_t param6;
        param7_t param7;
        param8_t param8;
        param9_t param9;
        param10_t param10;
        param11_t param11;
        enum {params_count = 12};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            , typename param6_t::connect_type p6
            , typename param7_t::connect_type p7
            , typename param8_t::connect_type p8
            , typename param9_t::connect_type p9
            , typename param10_t::connect_type p10
            , typename param11_t::connect_type p11
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
                param6.connect(p6);
                param7.connect(p7);
                param8.connect(p8);
                param9.connect(p9);
                param10.connect(p10);
                param11.connect(p11);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
            param6.precall(amx, params);
            param7.precall(amx, params);
            param8.precall(amx, params);
            param9.precall(amx, params);
            param10.precall(amx, params);
            param11.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
            param6.postcall(amx, params);
            param7.postcall(amx, params);
            param8.postcall(amx, params);
            param9.postcall(amx, params);
            param10.postcall(amx, params);
            param11.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            + ", " + param6_t::get_pawn_call_arg()
            + ", " + param7_t::get_pawn_call_arg()
            + ", " + param8_t::get_pawn_call_arg()
            + ", " + param9_t::get_pawn_call_arg()
            + ", " + param10_t::get_pawn_call_arg()
            + ", " + param11_t::get_pawn_call_arg()
            ; }*/
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename t0, typename t1, typename t2, typename t3, typename t4, typename t5, typename t6, typename t7, typename t8, typename t9, typename t10, typename t11, typename t12>
    struct marh_params_13_t {
        typedef marh_param_t<0, t0> param0_t;
        typedef marh_param_t<1, t1> param1_t;
        typedef marh_param_t<2, t2> param2_t;
        typedef marh_param_t<3, t3> param3_t;
        typedef marh_param_t<4, t4> param4_t;
        typedef marh_param_t<5, t5> param5_t;
        typedef marh_param_t<6, t6> param6_t;
        typedef marh_param_t<7, t7> param7_t;
        typedef marh_param_t<8, t8> param8_t;
        typedef marh_param_t<9, t9> param9_t;
        typedef marh_param_t<10, t10> param10_t;
        typedef marh_param_t<11, t11> param11_t;
        typedef marh_param_t<12, t12> param12_t;
        param0_t param0;
        param1_t param1;
        param2_t param2;
        param3_t param3;
        param4_t param4;
        param5_t param5;
        param6_t param6;
        param7_t param7;
        param8_t param8;
        param9_t param9;
        param10_t param10;
        param11_t param11;
        param12_t param12;
        enum {params_count = 13};

        void connect(
              typename param0_t::connect_type p0
            , typename param1_t::connect_type p1
            , typename param2_t::connect_type p2
            , typename param3_t::connect_type p3
            , typename param4_t::connect_type p4
            , typename param5_t::connect_type p5
            , typename param6_t::connect_type p6
            , typename param7_t::connect_type p7
            , typename param8_t::connect_type p8
            , typename param9_t::connect_type p9
            , typename param10_t::connect_type p10
            , typename param11_t::connect_type p11
            , typename param12_t::connect_type p12
            ) {
                param0.connect(p0);
                param1.connect(p1);
                param2.connect(p2);
                param3.connect(p3);
                param4.connect(p4);
                param5.connect(p5);
                param6.connect(p6);
                param7.connect(p7);
                param8.connect(p8);
                param9.connect(p9);
                param10.connect(p10);
                param11.connect(p11);
                param12.connect(p12);
        }
        void precall(AMX* amx, cell* params) {
            param0.precall(amx, params);
            param1.precall(amx, params);
            param2.precall(amx, params);
            param3.precall(amx, params);
            param4.precall(amx, params);
            param5.precall(amx, params);
            param6.precall(amx, params);
            param7.precall(amx, params);
            param8.precall(amx, params);
            param9.precall(amx, params);
            param10.precall(amx, params);
            param11.precall(amx, params);
            param12.precall(amx, params);
        }
        void postcall(AMX* amx, cell* params) {
            param0.postcall(amx, params);
            param1.postcall(amx, params);
            param2.postcall(amx, params);
            param3.postcall(amx, params);
            param4.postcall(amx, params);
            param5.postcall(amx, params);
            param6.postcall(amx, params);
            param7.postcall(amx, params);
            param8.postcall(amx, params);
            param9.postcall(amx, params);
            param10.postcall(amx, params);
            param11.postcall(amx, params);
            param12.postcall(amx, params);
        }

        /*static std::string get_pawn_call_args() { return 
                     param0_t::get_pawn_call_arg()
            + ", " + param1_t::get_pawn_call_arg()
            + ", " + param2_t::get_pawn_call_arg()
            + ", " + param3_t::get_pawn_call_arg()
            + ", " + param4_t::get_pawn_call_arg()
            + ", " + param5_t::get_pawn_call_arg()
            + ", " + param6_t::get_pawn_call_arg()
            + ", " + param7_t::get_pawn_call_arg()
            + ", " + param8_t::get_pawn_call_arg()
            + ", " + param9_t::get_pawn_call_arg()
            + ", " + param10_t::get_pawn_call_arg()
            + ", " + param11_t::get_pawn_call_arg()
            + ", " + param12_t::get_pawn_call_arg()
            ; }*/
    };
    
} // namespace pawn {
#endif // PAWN_MARSHALING_PARAMS_HPP
