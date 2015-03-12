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

#include <boost/preprocessor/cat.hpp>

// Inspired by Andrej Alexandrescu's ScopeGuard.h
// Some compiler does not support __COUNTER__ so there is an alternative
// implementation with __LINE__

#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str)                                               \
  BOOST_PP_CAT(str,__COUNTER__)
#else
#define ANONYMOUS_VARIABLE(str)                                               \
  BOOST_PP_CAT(str,__LINE__)
#endif

#define ENUM_EXTEND_EXPANDER(r, data, elem) BOOST_PP_CAT(data, elem)
#define ENUM_EXTEND_EMBRACER(r, nil, elem) BOOST_PP_CAT( {, BOOST_PP_CAT(elem, } ) )
