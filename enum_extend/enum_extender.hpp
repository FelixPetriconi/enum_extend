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

#include "internal/error_handling.hpp"
#include "internal/helper_structs.hpp"

#include <algorithm>
#include <vector>
#include <iterator>


namespace enum_extend
{
  namespace v_1_0_0
  {
    template<typename T, typename D = NoDecoration>
    class extender
    {
      static const bool is_decorated_ = !std::is_same<D, NoDecoration>::value;
      using value_type_ = std::conditional_t<is_decorated_, std::pair<T, D>, T>;
    public:

      using value_type = value_type_;
      using instances = std::vector<value_type>;
      using const_iterator = typename instances::const_iterator;
      using const_reverse_iterator = typename instances::const_reverse_iterator;

      extender(const extender&) = default;
      extender(extender&&) = delete;
      extender& operator=(const extender&) = delete;
      extender& operator=(extender&&) = delete;

      template <typename...TT>
      extender(TT&&... t) {
        s_instances = { std::forward<TT>(t)... };
      }

      extender(std::initializer_list<value_type> init)
      {
        std::copy(init.begin(), init.end(), std::back_inserter(s_instances));
      }

      static const_iterator begin() { return s_instances.cbegin(); }
      static const_iterator cbegin() { return s_instances.cbegin(); }
      static const_iterator end() { return s_instances.cend(); }
      static const_iterator cend() { return s_instances.cend(); }
      static const_reverse_iterator crbegin() { return s_instances.crbegin(); }
      static const_reverse_iterator rbegin() { return s_instances.crbegin(); }
      static const_reverse_iterator crend() { return s_instances.crend(); }
      static const_reverse_iterator rend() { return s_instances.crend(); }

      static size_t size() { return s_instances.size(); }

      static value_type& increment(value_type& t) {
        auto findIt = std::find(begin(), end(), t);
        if (findIt != end()) {
          ++findIt;
          if (findIt != end()) {
            t = *findIt;
            return t;
          }
        }
        handle_error("Try to increment beyond the last element!");
        return t;
      }

      static value_type& decrement(value_type& t) {
        auto findIt = std::find(begin(), end(), t);
        if (findIt != end()) {
          if (findIt != begin()) {
            --findIt;
            t = *findIt;
            return t;
          }
        }
        handle_error("Try to decrement before the first element!");
        return t;
      }

    private:

      static instances s_instances;
    };
  }
  using namespace v_1_0_0;
}
