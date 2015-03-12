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

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>


#define ENUM_LIB_CREATE_EXPLICIT_INITIALIZERS_ELEMENTS(r,_,index,enum_and_values)      \
  BOOST_PP_COMMA_IF(index) BOOST_PP_TUPLE_ELEM(2,0,enum_and_values) =         \
                             BOOST_PP_TUPLE_ELEM(2,1,enum_and_values)         \

#define ENUM_LIB_CREATE_EXPLICIT_ENUM_INITIALIZERS(enum_and_values)           \
  BOOST_PP_SEQ_FOR_EACH_I(ENUM_LIB_CREATE_EXPLICIT_INITIALIZERS_ELEMENTS, _,           \
    BOOST_PP_CAT(ENUM_LIB_PLACEHOLDER_FILLER_0 enum_and_values,_END))


