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

#include "compiler_support.hpp"
#include <exception>

namespace enum_extend
{
  INLINE_NAMESPACE_STANDIN
  namespace v_1_0_0
  {
    inline void handle_error(const char*) {
      throw std::exception();
    }
  }
  USING_VERSION_NAMESPACE
}