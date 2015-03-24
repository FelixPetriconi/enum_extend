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

#include "pp_helper.hpp"


#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>

// These makros are needed to create from a sequence of (a,b,c)(d,e,f)... an 
// std::make_tyupe(a,b,c), std::make_tuple(d,e,f)...
#define ENUM_EXTEND_EXPAND_TUPLE_ELEMENT_INTO_STD_MAKE_TUPLE3(r,enum_type, index, tuple_elements) \
  BOOST_PP_COMMA_IF(index) std::make_tuple(                                   \
    ENUM_EXTEND_CAT(ENUM_EXTEND_CAT(enum_type,::),BOOST_PP_TUPLE_ELEM(3, 0, tuple_elements)),                                \
    BOOST_PP_TUPLE_ELEM(3, 1, tuple_elements),                                \
    BOOST_PP_TUPLE_ELEM(3, 2, tuple_elements)                                 \
  )

#define ENUM_EXTEND_CREATE_EXPAND_TUPLES3_INTO_LIST_OF_STD_MAKE_TUPLE(enum_type, tuples)  \
  BOOST_PP_SEQ_FOR_EACH_I(ENUM_EXTEND_EXPAND_TUPLE_ELEMENT_INTO_STD_MAKE_TUPLE3, enum_type, \
    BOOST_PP_CAT(ENUM_EXTEND_PLACEHOLDER_FILLER_0 tuples,_END))
