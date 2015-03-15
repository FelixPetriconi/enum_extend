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

#include <tuple>

namespace enum_extend
{
  namespace v_1_0_0
  {
    struct NoDecoration {};

    /**
    * Functor that returns a pair's first element
    * \tparam T a pair type
    */
    template<typename T>
    struct First
    {
      using type = T;
      using result_type = typename std::tuple_element<0, T>::type;

      result_type operator()(const T& t) const {
        return std::get<0>(t);
      }
    };

    /**
    * Functor that returns a pair's second element
    * \tparam T a pair type
    */
    template<typename T>
    struct Second
    {
      using type = T;
      using result_type = typename std::tuple_element<1, T>::type;

      result_type operator() (const T& t) const {
        return std::get<1>(t);
      }
    };

    template<size_t I, typename T>
    struct TupleIndex
    {
      using type = T;
      using result_type = typename std::tuple_element<I, T>::type;

      result_type operator() (const T& t) const {
        return std::get<I>(t);
      }
    };
  }


}