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

#include <tuple>

namespace enum_extend
{
  INLINE_NAMESPACE_STANDIN 
  namespace v_1_0_0
  {

    template <class T, class Tuple>
    struct TupleTypeIndex;

    template <class T, class... Types>
    struct TupleTypeIndex < T, std::tuple<T, Types...> > {
      static const std::size_t value = 0;
    };

    template <class T, class U, class... Types>
    struct TupleTypeIndex < T, std::tuple<U, Types...> > {
      static const std::size_t value = 1 + TupleTypeIndex<T, std::tuple<Types...>>::value;
    };
  }
  USING_VERSION_NAMESPACE
}