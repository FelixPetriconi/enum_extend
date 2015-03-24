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

// These makros are needed to create from a sequence of (a,b)(c,d)... an 
// initializerlist of {a,b}, {c,d}, ...
#define ENUM_EXTEND_EXPAND_TUPLE_ELEMENT_INTO_STD_MAKE_TUPLE2(r,enum_type, index, tuple_elements) \
  BOOST_PP_COMMA_IF(index) std::make_tuple(                                   \
    ENUM_EXTEND_QUALIFY(enum_type, BOOST_PP_TUPLE_ELEM(2, 0, tuple_elements)),                                \
    BOOST_PP_TUPLE_ELEM(2, 1, tuple_elements)                                 \
  )

#define ENUM_EXTEND_CREATE_EXPAND_TUPLES2_INTO_LIST_OF_STD_MAKE_TUPLE(enum_type, tuples)  \
  BOOST_PP_SEQ_FOR_EACH_I(ENUM_EXTEND_EXPAND_TUPLE_ELEMENT_INTO_STD_MAKE_TUPLE2, enum_type, \
    BOOST_PP_CAT(ENUM_EXTEND_PLACEHOLDER_FILLER_0 tuples,_END))
