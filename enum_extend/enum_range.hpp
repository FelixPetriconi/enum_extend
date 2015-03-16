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

#include "extender.hpp"
#include <boost/iterator/transform_iterator.hpp>

namespace enum_extend 
{
  INLINE_NAMESPACE_STANDIN
  namespace v_1_0_0
  {

    template <typename T, typename... D> 
    struct enum_range {
      using extender_const_iterator = typename extender<T, D...>::const_iterator;
      using extender_const_reverse_iterator =
          typename extender<T, D...>::const_reverse_iterator;

      using const_value_iterator = boost::transform_iterator<
          First<typename extender<T, D...>::value_type>, extender_const_iterator>;
      using const_value_reverse_iterator =
          boost::transform_iterator<First<typename extender<T, D...>::value_type>,
                                    extender_const_reverse_iterator>;

      const_value_iterator begin() {
        return const_value_iterator(extender<T, D...>::begin());
      }
      const_value_iterator end() {
        return const_value_iterator(extender<T, D...>::end());
      }

      const_value_reverse_iterator rbegin() {
        return const_value_reverse_iterator(extender<T, D...>::rbegin());
      }
      const_value_reverse_iterator rend() {
        return const_value_reverse_iterator(extender<T, D...>::rend());
      }
    };
  }

  USING_VERSION_NAMESPACE
}