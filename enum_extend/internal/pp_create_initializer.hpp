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


// These makros are needed to create from a sequence of (a,b)(c,d)... an 
// initializerlist of {a,b}, {c,d}, ...
#define ENUM_LIB_CREATE_INITIALIZERS_ELEMENTS(r,ENUM,index,enum_and_decoration)  \
  BOOST_PP_COMMA_IF(index) { BOOST_PP_CAT(ENUM::,BOOST_PP_TUPLE_ELEM(2,0,enum_and_decoration)),    \
                             BOOST_PP_TUPLE_ELEM(2,1,enum_and_decoration) }

#define ENUM_LIB_CREATE_INITIALIZERS(TYPE, enum_and_decoration)                     \
  BOOST_PP_SEQ_FOR_EACH_I(ENUM_LIB_CREATE_INITIALIZERS_ELEMENTS, TYPE,           \
    BOOST_PP_CAT(ENUM_LIB_PLACEHOLDER_FILLER_0 enum_and_decoration,_END))

//
#define ENUM_LIB_EXPANDER(r, data, elem) BOOST_PP_CAT(data, elem)
#define ENUM_LIB_EMBRACER(r, nil, elem) BOOST_PP_CAT( {, BOOST_PP_CAT(elem, } ) )

