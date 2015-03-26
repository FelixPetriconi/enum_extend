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

#define ENUM_EXTEND_DEFINE_ENUM_OPERATORS_I(ENUM)                             \
  ENUM& operator++(ENUM& e) {                                                 \
    return enum_extend::extender<ENUM>::increment(e);                         \
  }                                                                           \
  ENUM& operator--(ENUM& e) {                                                 \
    return enum_extend::extender<ENUM>::decrement(e);                         \
  }                                                                           \
  ENUM operator++(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM>::increment(e);                                \
    return tmp;                                                               \
  }                                                                           \
  ENUM operator--(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM>::decrement(e);                                \
    return tmp;                                                               \
  }                                                                           \


#define ENUM_EXTEND_DEFINE_1_DECO_ENUM_OPERATORS_I(ENUM, DECO_TYPE1)          \
  ENUM& operator++(ENUM& e) {                                                 \
    return enum_extend::extender<ENUM, DECO_TYPE1>::increment(e);             \
  }                                                                           \
  ENUM& operator--(ENUM& e) {                                                 \
    return enum_extend::extender<ENUM, DECO_TYPE1>::decrement(e);             \
  }                                                                           \
  ENUM operator++(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM, DECO_TYPE1>::increment(e);                    \
    return tmp;                                                               \
  }                                                                           \
  ENUM operator--(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM, DECO_TYPE1>::decrement(e);                    \
    return tmp;                                                               \
  }                                                                           \

#define ENUM_EXTEND_DEFINE_2_DECO_ENUM_OPERATORS_I(ENUM, DECO_TYPE1, DECO_TYPE2)\
  ENUM& operator++(ENUM& e) {                                                 \
    return enum_extend::extender<ENUM, DECO_TYPE1, DECO_TYPE2>::increment(e); \
  }                                                                           \
  ENUM& operator--(ENUM& e) {                                                 \
    return enum_extend::extender<ENUM, DECO_TYPE1, DECO_TYPE2>::decrement(e); \
  }                                                                           \
  ENUM operator++(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM, DECO_TYPE1, DECO_TYPE2>::increment(e);        \
    return tmp;                                                               \
  }                                                                           \
  ENUM operator--(ENUM& e, int) {                                             \
    auto tmp = e;                                                             \
    enum_extend::extender<ENUM, DECO_TYPE1, DECO_TYPE2>::decrement(e);        \
    return tmp;                                                               \
  }                                                                           \

