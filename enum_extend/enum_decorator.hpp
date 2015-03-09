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

#include <algorithm>
#include <array>
#include <boost/iterator/transform_iterator.hpp>
#include "internal/defines.hpp"
#include "internal/helper.hpp"
#include "internal/error_handling.hpp"

namespace enum_extend
{
  namespace v_1_0_0
  {

    template <typename T>
    struct enum_value_range
    {
      typename T::const_value_iterator begin() { return T::all.vbegin(); }
      typename T::const_value_iterator end() { return T::all.vend(); }

      typename T::const_value_reverse_iterator rbegin() { return T::all.rvbegin(); }
      typename T::const_value_reverse_iterator rend() { return T::all.rvend(); }
    };

    template <typename T>
    struct enum_decoration_range
    {
      typename T::const_decoration_iterator begin() { return T::all.dbegin(); }
      typename T::const_decoration_iterator end() { return T::all.dend(); }

      typename T::const_decoration_reverse_iterator rbegin() { return T::all.rdbegin(); }
      typename T::const_decoration_reverse_iterator rend() { return T::all.rdend(); }
    };


    template<typename EnumType, typename T, typename D, size_t S>
    class enum_decorator
    {
    public:
      using value_type = std::pair<T, D>;
      using instances = std::array<value_type, S>;

      using const_iterator = typename instances::const_iterator;
      using const_reverse_iterator = typename instances::const_reverse_iterator;

      using const_value_iterator = boost::transform_iterator < First<value_type>,
        const_iterator > ;
      using const_decoration_iterator = boost::transform_iterator < Second<value_type>,
        const_iterator > ;
      using const_value_reverse_iterator = boost::transform_iterator < First<value_type>,
        const_reverse_iterator > ;
      using const_decoration_reverse_iterator = boost::transform_iterator < Second<value_type>,
        const_reverse_iterator > ;

      enum_decorator(std::initializer_list<value_type> init) {
        std::copy(init.begin(), init.end(), s_instances.begin());
      }

      //enum_decorator(const enum_decorator&) = delete;
      enum_decorator(enum_decorator&&) = delete;
      enum_decorator& operator=(const enum_decorator&) = delete;
      enum_decorator& operator=(enum_decorator&&) = delete;

      static const_iterator begin() { return s_instances.cbegin(); }
      static const_iterator cbegin() { return s_instances.cbegin(); }
      static const_iterator end() { return s_instances.cend(); }
      static const_iterator cend() { return s_instances.cend(); }
      static const_reverse_iterator crbegin() { return s_instances.crbegin(); }
      static const_reverse_iterator rbegin() { return s_instances.crbegin(); }
      static const_reverse_iterator crend() { return s_instances.crend(); }
      static const_reverse_iterator rend() { return s_instances.crend(); }

      static const_value_iterator vbegin() { return const_value_iterator(begin()); }
      static const_value_iterator vend() { return const_value_iterator(end()); }
      static const_value_reverse_iterator rvbegin() { return const_value_reverse_iterator(rbegin()); }
      static const_value_reverse_iterator rvend() { return const_value_reverse_iterator(rend()); }

      static const_decoration_iterator dbegin() { return const_decoration_iterator(begin()); }
      static const_decoration_iterator dend() { return const_decoration_iterator(end()); }
      static const_decoration_reverse_iterator rdbegin() { return const_decoration_reverse_iterator(rbegin()); }
      static const_decoration_reverse_iterator rdend() { return const_decoration_reverse_iterator(rend()); }

      static size_t size() { return S; }

      static T& increment(T& t) {
        auto findIt = std::find(vbegin(), vend(), t);
        if (findIt != vend()) {
          ++findIt;
          if (findIt != vend()) {
            t = *findIt;
            return t;
          }
        }
        handle_error("Try to increment beyond the last element!");
        return t;
      }

      static T& decrement(T& t) {
        auto findIt = std::find(vbegin(), vend(), t);
        if (findIt != vend()) {
          if (findIt != vbegin()) {
            --findIt;
            t = *findIt;
            return t;
          }
        }
        handle_error("Try to decrement before the first element!");
        return t;
      }

      static D to_decoration(const T& t) {
        auto findIt = std::find_if(cbegin(), cend(),
          [&t](const value_type& v) { return equal(v.first, t); });

        if (findIt != cend()) {
          return findIt->second;
        }
        handle_error("Enumerated value not found!");
        return D();
      }

      static T to_enum(const D& d) {
        auto findIt = std::find_if(cbegin(), cend(),
          [&d](const value_type& v) { return equal(v.second, d); });
        if (findIt != cend()) {
          return findIt->first;
        }
        handle_error("Decoration not found!");
        return T();
      }

    private:

      static instances s_instances;
    };


  }
  using namespace v_1_0_0;
}
