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

#define ENUM_EXTEND_DEFINE_ENUM_OPERATORS_BASE(ENUM)                            \
  ENUM& operator++(ENUM& e) { return enum_extend::extender<ENUM>::increment(e); }\
  ENUM& operator--(ENUM& e) { return enum_extend::extender<ENUM>::decrement(e); }\
  ENUM operator++(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM>::increment(e);                                 \
    return tmp;                                                               \
  }                                                                           \
  ENUM operator--(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM>::decrement(e);                                 \
    return tmp;                                                               \
  }                                                                           \


