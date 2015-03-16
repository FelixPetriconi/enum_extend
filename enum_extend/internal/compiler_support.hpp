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

#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_INLINE_NAMESPACES 
#define INLINE_NAMESPACE_STANDIN
#define USING_VERSION_NAMESPACE using namespace v_1_0_0;
#else
#define INLINE_NAMESPACE_STANDIN inline
#define USING_VERSION_NAMESPACE
#endif