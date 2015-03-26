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

#define ENUM_EXTEND_DECLARE_ENUM_OPERATORS_I(ENUM)                            \
  ENUM& operator++(ENUM& e);                                                  \
  ENUM& operator--(ENUM& e);                                                  \
  ENUM operator++(ENUM& e, int);                                              \
  ENUM operator--(ENUM& e, int);                                              \


