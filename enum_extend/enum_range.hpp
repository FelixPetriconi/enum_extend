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

#include "enum_extender.hpp"

namespace enum_extend
{
  namespace v_1_0_0
  {
    template <typename T, typename D = NoDecoration>
    struct enum_range
    {
      using const_iterator = typename extender<T, D>::const_iterator;
      using const_reverse_iterator = typename extender<T, D>::const_reverse_iterator;

      const_iterator begin() { return extender<T, D>::begin(); }
      const_iterator end() { return extender<T, D>::end(); }

      const_reverse_iterator rbegin() { return extender<T, D>::rbegin(); }
      const_reverse_iterator rend() { return extender<T, D>::rend(); }
    };
  }
  using namespace v_1_0_0;
}