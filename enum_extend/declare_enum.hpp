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

#include "internal/declare_operators_helpers.hpp"
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/tuple/elem.hpp>


// \p (NAME, ENUMERATIONS)
#define ENUM_EXTEND_DECLARE_ENUM(DEF)                                         \
  ENUM_EXTEND_DECLARE_ENUM_I(BOOST_PP_TUPLE_ELEM(2, 0, DEF),                  \
                           BOOST_PP_TUPLE_ELEM(2, 1, DEF))                    \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(2, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_ENUM_I(NAME, ENUMERATIONS)                        \
  enum NAME {                                                                 \
    BOOST_PP_SEQ_ENUM(ENUMERATIONS)                                           \
  };                                                                          \


// \p (NAME, ENUMERATIONS)
#define ENUM_EXTEND_DECLARE_ENUM_CLASS(DEF)                                   \
  ENUM_EXTEND_DECLARE_ENUM_CLASS_I(BOOST_PP_TUPLE_ELEM(2, 0, DEF),            \
                                      BOOST_PP_TUPLE_ELEM(2, 1, DEF))         \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(2, 0, DEF))        \



#define ENUM_EXTEND_DECLARE_ENUM_CLASS_I(NAME, ENUMERATIONS)                  \
  enum class NAME {                                                           \
    BOOST_PP_SEQ_ENUM(ENUMERATIONS)                                           \
  };                                                                          \

// \p (NAME, TYPE, ENUMERATIONS)
#define ENUM_EXTEND_DECLARE_TYPED_ENUM(DEF)                                   \
  ENUM_EXTEND_DECLARE_TYPED_ENUM_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF),            \
                           BOOST_PP_TUPLE_ELEM(3, 1, DEF),                    \
                           BOOST_PP_TUPLE_ELEM(3, 2, DEF))                    \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_TYPED_ENUM_I(NAME, TYPE, ENUMERATIONS)            \
  enum NAME : TYPE {                                                          \
    BOOST_PP_SEQ_ENUM(ENUMERATIONS)                                           \
  };                                                                          \

// \p (NAME, TYPE, ENUMERATIONS)
#define ENUM_EXTEND_DECLARE_TYPED_ENUM_CLASS(DEF)                             \
  ENUM_EXTEND_DECLARE_TYPED_ENUM_CLASS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF),      \
                                            BOOST_PP_TUPLE_ELEM(3, 1, DEF),   \
                                            BOOST_PP_TUPLE_ELEM(3, 2, DEF))   \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF))        \



#define ENUM_EXTEND_DECLARE_TYPED_ENUM_CLASS_I(NAME, TYPE, ENUMERATIONS)      \
  enum class NAME : TYPE {                                                    \
    BOOST_PP_SEQ_ENUM(ENUMERATIONS)                                           \
  };                                                                          \


