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

namespace enum_extend
{
  namespace v_1_0_0
  {
    struct NoDecoration {};

    /**
    * Functor that returns a pairs first element
    * \tparam T a pair type
    */
    template<typename T>
    struct First
    {
      using type = T;
      using result_type = typename T::first_type;

      result_type operator()(const T& pair) const {
        return pair.first;
      }
    };

    /**
    * Functor that returns a pairs second element
    * \tparam T a pair type
    */
    template<typename T>
    struct Second
    {
      using type = T;
      using result_type = typename T::second_type;;

      result_type operator() (const T& pair) const {
        return pair.second;
      }
    };

  }


}