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

#include "enum_extender.hpp"

#include "create_enum.hpp"
#include "create_operators.hpp"

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/tuple/elem.hpp>


#define ENUM_LIB_DECLARE_EXTENDED_ENUM_BASE(ENUM, ENUMERATIONS)               \
  struct ENUM {                                                               \
    ENUM_LIB_DECLARE_ENUM_BASE(InternalValues, ENUMERATIONS)                  \
    ENUM_LIB_DECLARE_ENUM_EXTENDER_BASE(BOOST_PP_CAT(Extended, ENUM),         \
                                        ENUM::InternalValues,                 \
                                        BOOST_PP_SEQ_SIZE(ENUMERATIONS))      \
  };                                                                          \


// \p (ENUM, ENUMERATIONS)
#define ENUM_LIB_DECLARE_EXTENDED_ENUM(DEF)                                   \
  ENUM_LIB_DECLARE_EXTENDED_ENUM_BASE(BOOST_PP_TUPLE_ELEM(2, 0, DEF),         \
                                      BOOST_PP_TUPLE_ELEM(2, 1, DEF))         \
  ENUM_LIB_DECLARE_EXTENDED_ENUM_OPERATORS(BOOST_PP_TUPLE_ELEM(2, 0, DEF))    \


// \p (ENUM, ENUMERATIONS)
#define ENUM_LIB_DECLARE_COMPLETE_ENUM(DEF)                                   \
  ENUM_LIB_DECLARE_EXTENDED_ENUM(BOOST_PP_TUPLE_ELEM(2, 0, DEF),              \
                                 BOOST_PP_TUPLE_ELEM(2, 1, DEF))              \


#define ENUM_LIB_DEFINE_EXTENDED_ENUM_BASE(ENUM, SIZE, ENUMERATIONS)          \
  template <>                                                                 \
  BOOST_PP_CAT(ENUM::, BOOST_PP_CAT(Extended, ENUM))::enum_extender<          \
      BOOST_PP_CAT(ENUM::, BOOST_PP_CAT(Extended, ENUM)),                     \
      ENUM::InternalValues, SIZE>::instances                                  \
  BOOST_PP_CAT(ENUM::, BOOST_PP_CAT(Extended, ENUM))::enum_extender<          \
      BOOST_PP_CAT(ENUM::, BOOST_PP_CAT(Extended, ENUM)),                     \
      ENUM::InternalValues, SIZE>::s_instances;                               \
                                                                              \
  const BOOST_PP_CAT(ENUM::, BOOST_PP_CAT(Extended, ENUM))                    \
    BOOST_PP_CAT(ENUM::, BOOST_PP_CAT(Extended, ENUM))::all({                 \
      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(ENUM_LIB_EXPANDER,             \
                                               ENUM::InternalValues::,        \
                                               ENUMERATIONS))                 \
    });                                                                       \


// \p (ENUM, ENUMERATIONS)
#define ENUM_LIB_DEFINE_EXTENDED_ENUM(DEF)                                    \
  ENUM_LIB_DEFINE_EXTENDED_ENUM_BASE(BOOST_PP_TUPLE_ELEM(2, 0, DEF),          \
                                     BOOST_PP_SEQ_SIZE(                       \
                                       BOOST_PP_TUPLE_ELEM(2, 1, DEF)),       \
                                     BOOST_PP_TUPLE_ELEM(2, 1, DEF))          \
  ENUM_LIB_DEFINE_EXTENDED_ENUM_OPERATORS(BOOST_PP_TUPLE_ELEM(2, 0, DEF))     \


