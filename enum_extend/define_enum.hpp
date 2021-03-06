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

#include "internal/define_enum_helper.hpp"
#include "internal/define_operators_helpers.hpp"

#include <boost/preprocessor/tuple/elem.hpp>


// \p (ENUM, ENUMERATIONS)
#define ENUM_EXTEND_DEFINE_ENUM(DEF)                                          \
  ENUM_EXTEND_DEFINE_ENUM_I(BOOST_PP_TUPLE_ELEM(2, 0, DEF),                   \
                               BOOST_PP_TUPLE_ELEM(2, 1, DEF))                \
  ENUM_EXTEND_DEFINE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(2, 0, DEF))         \

// \p (ENUM, ENUMERATIONS)
#define ENUM_EXTEND_DEFINE_ENUM_CLASS(DEF)                                    \
  ENUM_EXTEND_DEFINE_ENUM(DEF)                                                \


// \p (ENUM, TYPE, ENUMERATIONS)
#define ENUM_EXTEND_DEFINE_TYPED_ENUM(DEF)                                    \
  ENUM_EXTEND_DEFINE_ENUM_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF),                   \
                               BOOST_PP_TUPLE_ELEM(3, 2, DEF))                \
  ENUM_EXTEND_DEFINE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF))         \

// \p (ENUM, TYPE, ENUMERATIONS)
#define ENUM_EXTEND_DEFINE_TYPED_ENUM_CLASS(DEF)                              \
  ENUM_EXTEND_DEFINE_TYPED_ENUM(DEF)                                          \

