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
#include "internal/tupple_helper.hpp"
#include "internal/compiler_support.hpp"

#include <type_traits>
#include <algorithm>
#include <vector>
#include <iterator>

namespace enum_extend
{
  INLINE_NAMESPACE_STANDIN 
  namespace v_1_0_0
  {
    template<bool Decorated, typename T, typename... D>
    struct IncDecWorker;


    template<typename T, typename... D>
    class extender
    {
      static const bool is_decorated_ = sizeof...(D) != 0;
      using value_type_ = typename std::conditional<is_decorated_, 
                                                    std::tuple<T, D...>, 
                                                    T>::type;
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
        all_values = { std::forward<TT>(t)... };
      }

      extender(std::initializer_list<value_type> init)
      {
        std::copy(init.begin(), init.end(), std::back_inserter(all_values));
      }

      static const_iterator begin() { return all_values.cbegin(); }
      static const_iterator cbegin() { return all_values.cbegin(); }
      static const_iterator end() { return all_values.cend(); }
      static const_iterator cend() { return all_values.cend(); }
      static const_reverse_iterator crbegin() { return all_values.crbegin(); }
      static const_reverse_iterator rbegin() { return all_values.crbegin(); }
      static const_reverse_iterator crend() { return all_values.crend(); }
      static const_reverse_iterator rend() { return all_values.crend(); }

      static size_t size() { return all_values.size(); }

      static T& increment(T& t) {
        return IncDecWorker<is_decorated_, T, D...>::inc(t);
      }

      static T& decrement(T& t) {
        return IncDecWorker<is_decorated_, T, D...>::dec(t);
      }

      template <typename TT>
      static typename std::enable_if<is_decorated_, TT>::type 
        get_decoration(const T& t) {
        
        auto findIt = std::find_if(begin(), end(), 
                                   [&t](const value_type& v) {
                                     return std::get<0>(v) == t;
                                   });
        if (findIt != end()) {
          return std::get<TupleTypeIndex<TT, value_type>::value>(*findIt);
        }
        handle_error("Access to not defined enumerated value!");
        return TT();
      }
    private:

      static instances all_values;
    };


    template<typename T, typename... D>
    struct IncDecWorker < true, T, D... >
    {
      static T&  inc(T& t) {
        auto endIt = extender<T, D...>::end();
        auto findIt = std::find_if(extender<T, D...>::begin(), endIt,
                                   [&t](const typename extender<T, D...>::value_type& x) {
                                     return std::get<0>(x) == t;
                                  });

        if (findIt != endIt) {
          ++findIt;
          if (findIt != endIt) {
            t = std::get<0>(*findIt);
            return t;
          }
        }
        handle_error("Try to increment beyond the last element!");
        return t;
      }

      static T& dec(T& t) {
        auto findIt = std::find_if(extender<T, D...>::begin(), extender<T, D...>::end(),
                [&t](const typename extender<T, D...>::value_type& x) {
                  return std::get<0>(x) == t;
                });

        if (findIt != extender<T, D...>::end()) {
          if (findIt != extender<T, D...>::begin()) {
            --findIt;
            t = std::get<0>(*findIt);
            return t;
          }
        }
        handle_error("Try to decrement before the first element!");
        return t;
      }

    };

    template<typename T, typename... D>
    struct IncDecWorker < false, T, D... >
    {
      static T& inc(T& t) {
        auto endIt = extender<T, D...>::end();
        auto findIt = std::find(extender<T, D...>::begin(), endIt, t);
        if (findIt != endIt) {
          ++findIt;
          if (findIt != endIt) {
            t = *findIt;
            return t;
          }
        }
        handle_error("Try to increment beyond the last element!");
        return t;
      }

      static T& dec(T& t) {
        auto findIt = std::find(extender<T, D...>::begin(), extender<T, D...>::end(), t);
        if (findIt != extender<T, D...>::end()) {
          if (findIt != extender<T, D...>::begin()) {
            --findIt;
            t = *findIt;
            return t;
          }
        }
        handle_error("Try to decrement before the first element!");
        return t;
      }
    };

  }
  USING_VERSION_NAMESPACE
}
