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

#include <exception>

namespace enum_extend
{
  namespace v_1_0_0
  {
    inline void handle_error(const char*) {
      throw std::exception();
    }
  }
  using namespace v_1_0_0;
}