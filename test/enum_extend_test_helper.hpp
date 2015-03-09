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

#include <gtest/gtest.h>

struct EqualStr
{
  using result_type = bool;

  bool operator() (const char* x, const char* y) const {
    EXPECT_STREQ(y, x);
    return strcmp(x, y) == 0;
  }
};


