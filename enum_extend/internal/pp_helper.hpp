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

#define ENUM_EXTEND_PLACEHOLDER_FILLER_0(x, y)                                   \
    ((x, y)) ENUM_EXTEND_PLACEHOLDER_FILLER_1
#define ENUM_EXTEND_PLACEHOLDER_FILLER_1(x, y)                                   \
    ((x, y)) ENUM_EXTEND_PLACEHOLDER_FILLER_0
#define ENUM_EXTEND_PLACEHOLDER_FILLER_0_END
#define ENUM_EXTEND_PLACEHOLDER_FILLER_1_END


#define ENUM_EXTEND_QUALIFY(a,b) a::b



