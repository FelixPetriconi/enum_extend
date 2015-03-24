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
#define ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE2_ELEMENT_IMP(r,_, index, tuple_elements) \
  BOOST_PP_COMMA_IF(index) BOOST_PP_TUPLE_ELEM(2, 0, tuple_elements)          \

#define ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE2_ELEMENT(tuples)                \
  BOOST_PP_SEQ_FOR_EACH_I(ENUM_EXTEND_CREATE_SEQ_FROM_1st_TUPLE2_ELEMENT_IMP, _, \
    BOOST_PP_CAT(ENUM_EXTEND_PLACEHOLDER_FILLER_0 tuples,_END))               \

