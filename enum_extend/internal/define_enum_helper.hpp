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
#include "macro_helper.hpp"

#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>

// enum_extend::extender<Color>::instances enum_extend::extender<Color>::s_instances;
// enum_extend::extender<Color>  ColorExtender(Color::Red, Color::Green, Color::Blue);

#define ENUM_EXTEND_DEFINE_ENUM_BASE(ENUM, ENUMERATIONS)                      \
  template <>                                                                 \
  enum_extend::extender<ENUM>::instances                                      \
    enum_extend::extender<ENUM>::s_instances = {};                            \
  enum_extend::extender<ENUM> ANONYMOUS_VARIABLE(GLOBAL_ENUM_VARIABLE)({      \
      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(ENUM_EXTEND_COLON_GLUE,        \
                                               ENUM,                          \
                                               ENUMERATIONS))                 \
    });                                                                       \



