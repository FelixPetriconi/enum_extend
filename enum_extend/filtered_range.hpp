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
#include <functional>
#include <boost/iterator/filter_iterator.hpp>

namespace enum_extend
{
  namespace v_1_0_0
  {
    template <typename T, typename D = NoDecoration>
    struct filtered_range
    {
      using Filter = std::function<bool(typename extender<T, D>::value_type)>;
      Filter filter_;

      explicit filtered_range(Filter filter) : filter_(filter) {}

      using const_iterator = typename extender<T, D>::const_iterator;
      using const_reverse_iterator = typename extender<T, D>::const_reverse_iterator;

      using const_filtered_iterator = typename boost::filter_iterator<Filter, const_iterator>;
      using const_reverse_filtered_iterator = typename boost::filter_iterator<Filter, const_reverse_iterator>;

      const_filtered_iterator begin() { return const_filtered_iterator(filter_, extender<T, D>::begin(), extender<T, D>::end()); }
      const_filtered_iterator end() { return const_filtered_iterator(filter_, extender<T, D>::end(), extender<T, D>::end()); }

      const_reverse_filtered_iterator rbegin() { return const_filtered_iterator(filter_, extender<T, D>::rbegin(), extender<T, D>::rbegin()); }
      const_reverse_filtered_iterator rend() { return const_filtered_iterator(filter_, extender<T, D>::rend(), extender<T, D>::rend()); }
    };
  }
  using namespace v_1_0_0;
}