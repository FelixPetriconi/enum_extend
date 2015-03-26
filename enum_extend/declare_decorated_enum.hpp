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
#include "internal/pp_create_seq_from_1st_tuple2.hpp"
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/tuple/elem.hpp>


// \p (NAME, DECO_TYPE1, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_1_DECORATED_ENUM(DEF)                             \
  ENUM_EXTEND_DECLARE_1_DECORATED_ENUM_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF),      \
                                         BOOST_PP_TUPLE_ELEM(3, 2, DEF))      \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_1_DECORATED_ENUM_I(NAME, ENUMERATIONS)            \
  enum NAME {                                                                 \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE2_ELEMENT(ENUMERATIONS)              \
  };                                                                          \

// \p (NAME, DECO_TYPE1, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_1_DECORATED_ENUM_CLASS(DEF)                       \
  ENUM_EXTEND_DECLARE_1_DECORATED_ENUM_CLASS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF),\
                                         BOOST_PP_TUPLE_ELEM(3, 2, DEF))      \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(3, 0, DEF))        \

#define ENUM_EXTEND_DECLARE_1_DECORATED_ENUM_CLASS_I(NAME, ENUMERATIONS)      \
  enum class NAME {                                                           \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE2_ELEMENT(ENUMERATIONS)              \
  };                                                                          \


// \p (NAME, ENUM_TYPE, DECO_TYPE1, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM(DEF)                       \
  ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),\
                                         BOOST_PP_TUPLE_ELEM(4, 1, DEF),      \
                                         BOOST_PP_TUPLE_ELEM(4, 3, DEF))      \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM_I(NAME,                    \
                                                     ENUM_TYPE,               \
                                                     ENUMERATIONS)            \
  enum NAME : ENUM_TYPE {                                                     \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE2_ELEMENT(ENUMERATIONS)              \
  };                                                                          \

// \p (NAME, ENUM_TYPE, DECO_TYPE1, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM_CLASS(DEF)                 \
  ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM_CLASS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),\
                                         BOOST_PP_TUPLE_ELEM(4, 1, DEF),      \
                                         BOOST_PP_TUPLE_ELEM(4, 3, DEF))      \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM_CLASS_I(NAME,              \
                                                           ENUM_TYPE,         \
                                                           ENUMERATIONS)      \
  enum class NAME : ENUM_TYPE {                                               \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE2_ELEMENT(ENUMERATIONS)              \
  };                                                                          \






// \p (NAME, DECO_TYPE1, DECO_TYPE2, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_2_DECORATED_ENUM(DEF)                             \
  ENUM_EXTEND_DECLARE_2_DECORATED_ENUM_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),      \
                                         BOOST_PP_TUPLE_ELEM(4, 3, DEF))      \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_2_DECORATED_ENUM_I(NAME, ENUMERATIONS)            \
  enum class NAME {                                                           \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE3_ELEMENT(ENUMERATIONS)              \
  };                                                                          \


// \p (NAME, DECO_TYPE1, DECO_TYPE2, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_2_DECORATED_ENUM_CLASS(DEF)                       \
  ENUM_EXTEND_DECLARE_2_DECORATED_ENUM_CLASS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF),\
                                               BOOST_PP_TUPLE_ELEM(4, 3, DEF))\
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(4, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_2_DECORATED_ENUM_CLASS_I(NAME, ENUMERATIONS)      \
  enum class NAME {                                                           \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE3_ELEMENT(ENUMERATIONS)              \
  };                                                                          \

// \p (NAME, ENUM_TYPE, DECO_TYPE1, DECO_TYPE2, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_2_DECORATED_TYPED_ENUM(DEF)                       \
  ENUM_EXTEND_DECLARE_2_DECORATED_TYPED_ENUM_I(BOOST_PP_TUPLE_ELEM(5, 0, DEF),\
                                               BOOST_PP_TUPLE_ELEM(5, 1, DEF),\
                                               BOOST_PP_TUPLE_ELEM(5, 4, DEF))\
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(5, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_2_DECORATED_TYPED_ENUM_I(NAME, ENUM_TYPE, ENUMERATIONS)\
  enum NAME : ENUM_TYPE {                                                     \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE3_ELEMENT(ENUMERATIONS)              \
  };                                                                          \

// \p (NAME, ENUM_TYPE, DECO_TYPE1, DECO_TYPE2, ENUMERATIONS) 
#define ENUM_EXTEND_DECLARE_2_DECORATED_TYPED_ENUM_CLASS(DEF)                 \
  ENUM_EXTEND_DECLARE_2_DECORATED_TYPED_ENUM_CLASS_I(BOOST_PP_TUPLE_ELEM(5, 0, DEF),\
                                         BOOST_PP_TUPLE_ELEM(5, 1, DEF),      \
                                         BOOST_PP_TUPLE_ELEM(5, 4, DEF))      \
  ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(BOOST_PP_TUPLE_ELEM(5, 0, DEF))        \


#define ENUM_EXTEND_DECLARE_2_DECORATED_TYPED_ENUM_CLASS_I(NAME,              \
                                                           ENUM_TYPE,         \
                                                           ENUMERATIONS)      \
  enum class NAME : ENUM_TYPE {                                               \
    ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE3_ELEMENT(ENUMERATIONS)              \
  };                                                                          \

