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

#include "../extender.hpp"
#include "define_operators_helpers.hpp"
#include "pp_helper.hpp"

#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>

#define ENUM_EXTEND_DEFINE_ENUM_I(ENUM, ENUMERATIONS)                         \
  template <>                                                                 \
  enum_extend::v_1_0_0::extender<ENUM>::instances                             \
    enum_extend::v_1_0_0::extender<ENUM>::all_values = {                      \
      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(ENUM_EXTEND_COLON_GLUE,        \
                                               ENUM,                          \
                                               ENUMERATIONS))                 \
    };                                                                        \



