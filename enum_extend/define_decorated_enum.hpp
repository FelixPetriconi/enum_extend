///////////////////////////////////////////////////////////////////
//
// Copyright 2015 Felix Petriconi
//
// License: http://boost.org/LICENSE_1_0.txt, Boost License 1.0
//
// Authors: http://petriconi.net, Felix Petriconi
//
//////////////////////////////////////////////////////////////////

#pragma once

#include "extender.hpp"
#include "internal/define_operators_helpers.hpp"
#include "internal/pp_create_seq_from_tuple2_seq.hpp"
#include "internal/pp_create_seq_from_tuple3_seq.hpp"

#include <boost/preprocessor/tuple/elem.hpp>


// \p (ENUM, DECO_TYPE1, DECORATED_ENUMERATIONS_PAIR)
#define ENUM_EXTEND_DEFINE_1_DECORATED_ENUM(DEF)                              \
  ENUM_EXTEND_DEFINE_1_DECORATED_ENUM_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(3, 1, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(3, 2, DEF))       \
  ENUM_EXTEND_DEFINE_1_DECO_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF), BOOST_PP_TUPLE_ELEM(3, 1, DEF))         \


#define ENUM_EXTEND_DEFINE_1_DECORATED_ENUM_I(ENUM, DECO_TYPE1, ENUMERATIONS) \
  template <>                                                                 \
  enum_extend::v_1_0_0::extender<ENUM, DECO_TYPE1>::instances                          \
    enum_extend::v_1_0_0::extender<ENUM, DECO_TYPE1>::all_values = {                   \
      ENUM_EXTEND_CREATE_EXPAND_TUPLES2_INTO_LIST_OF_STD_MAKE_TUPLE(ENUM, ENUMERATIONS)\
    };                                                                        \

// \p (ENUM, DECO_TYPE1, DECORATED_ENUMERATIONS_PAIR)
#define ENUM_EXTEND_DEFINE_1_DECORATED_ENUM_CLASS(DEF)                        \
  ENUM_EXTEND_DEFINE_1_DECORATED_ENUM(DEF)                                    \


// \p (ENUM, ENUM_TYPE, DECO_TYPE1, DECORATED_ENUMERATIONS_PAIR)
#define ENUM_EXTEND_DEFINE_1_DECORATED_TYPED_ENUM(DEF)                        \
  ENUM_EXTEND_DEFINE_1_DECORATED_ENUM_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(4, 2, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(4, 3, DEF))       \
  ENUM_EXTEND_DEFINE_1_DECO_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF), BOOST_PP_TUPLE_ELEM(4, 2, DEF))         \

// \p (ENUM, ENUM_TYPE, DECO_TYPE1, DECORATED_ENUMERATIONS_PAIR)
#define ENUM_EXTEND_DEFINE_1_DECORATED_TYPED_ENUM_CLASS(DEF)                  \
  ENUM_EXTEND_DEFINE_1_DECORATED_TYPED_ENUM(DEF)                              \




// \p (ENUM, DECO_TYPE1, DECO_TYPE2, DECORATED_ENUMERATIONS_TRIPPLE)
#define ENUM_EXTEND_DEFINE_2_DECORATED_ENUM(DEF)                              \
  ENUM_EXTEND_DEFINE_2_DECORATED_ENUM_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(4, 1, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(4, 2, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(4, 3, DEF))       \
  ENUM_EXTEND_DEFINE_2_DECO_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),BOOST_PP_TUPLE_ELEM(4, 1, DEF), BOOST_PP_TUPLE_ELEM(4, 2, DEF))         \



#define ENUM_EXTEND_DEFINE_2_DECORATED_ENUM_I(ENUM, DECO_TYPE1, DECO_TYPE2, ENUMERATIONS) \
  template <>                                                                 \
  enum_extend::v_1_0_0::extender<ENUM, DECO_TYPE1, DECO_TYPE2>::instances              \
    enum_extend::v_1_0_0::extender<ENUM, DECO_TYPE1, DECO_TYPE2>::all_values = {       \
   ENUM_EXTEND_CREATE_EXPAND_TUPLES3_INTO_LIST_OF_STD_MAKE_TUPLE(ENUM, ENUMERATIONS)\
                };                                                            \

// \p (ENUM, DECO_TYPE1, DECO_TYPE2, DECORATED_ENUMERATIONS_TRIPPLE)
#define ENUM_EXTEND_DEFINE_2_DECORATED_ENUM_CLASS(DEF)                        \
  ENUM_EXTEND_DEFINE_2_DECORATED_ENUM(DEF)                                    \


// \p (ENUM, ENUM_TYPE, DECO_TYPE1, DECO_TYPE2, DECORATED_ENUMERATIONS_TRIPPLE)
#define ENUM_EXTEND_DEFINE_2_DECORATED_TYPED_ENUM(DEF)                        \
  ENUM_EXTEND_DEFINE_2_DECORATED_ENUM_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(4, 2, DEF),       \
                                        BOOST_PP_TUPLE_ELEM(4, 3, DEF))       \
  ENUM_EXTEND_DEFINE_2_DECO_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),BOOST_PP_TUPLE_ELEM(4, 1, DEF), BOOST_PP_TUPLE_ELEM(4, 2, DEF))         \


// \p (ENUM, ENUM_TYPE, DECO_TYPE1, DECO_TYPE2, DECORATED_ENUMERATIONS_PAIR)
#define ENUM_EXTEND_DEFINE_2_DECORATED_TYPED_ENUM_CLASS(DEF)                  \
  ENUM_EXTEND_DEFINE_2_DECORATED_TYPED_ENUM(DEF)                              \

