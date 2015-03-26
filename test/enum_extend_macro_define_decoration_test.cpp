///////////////////////////////////////////////////////////////////
//
// Copyright 2015 Felix Petriconi
//
// License: http://boost.org/LICENSE_1_0.txt, Boost License 1.0
//
// Authors: http://petriconi.net, Felix Petriconi
//
//////////////////////////////////////////////////////////////////

#include "enum_extend/extender.hpp"
#include "enum_extend/range.hpp"
#include "enum_extend/enum_range.hpp"
#include "enum_extend/declare_decorated_enum.hpp"
#include "enum_extend/define_decorated_enum.hpp"

#include <gtest/gtest.h>
#include <vector>

using ccharp = const char*;
ccharp DarkGray1C = "DarkGray1";
ccharp MidGray1C = "MidGray1";
ccharp LightGray1C = "LightGray1";


template <typename T>
std::vector<T> createReference();


#define MACROCOLOR_DECO_ENUM_SPEC (MacroColorDecoEnum, ccharp, \
  (DarkGray1, DarkGray1C)(MidGray1, MidGray1C)(LightGray1, LightGray1C))

ENUM_EXTEND_DECLARE_1_DECORATED_ENUM(MACROCOLOR_DECO_ENUM_SPEC)
ENUM_EXTEND_DEFINE_1_DECORATED_ENUM(MACROCOLOR_DECO_ENUM_SPEC)

template<>
std::vector<std::tuple<MacroColorDecoEnum, ccharp>> createReference()
{
  return { std::make_tuple(MacroColorDecoEnum::DarkGray1, DarkGray1C),
           std::make_tuple(MacroColorDecoEnum::MidGray1, MidGray1C), 
           std::make_tuple(MacroColorDecoEnum::LightGray1, LightGray1C) };
}


ccharp DarkGray2C = "DarkGray2";
ccharp MidGray2C = "MidGray2";
ccharp LightGray2C = "LightGray2";

#define MACROCOLOR_DECO_ENUM_CLASS_SPEC (MacroColorDecoEnumClass, ccharp, \
  (DarkGray2, DarkGray2C)(MidGray2, MidGray2C)(LightGray2, LightGray2C))

ENUM_EXTEND_DECLARE_1_DECORATED_ENUM_CLASS(MACROCOLOR_DECO_ENUM_CLASS_SPEC)
ENUM_EXTEND_DEFINE_1_DECORATED_ENUM_CLASS(MACROCOLOR_DECO_ENUM_CLASS_SPEC)

template<>
std::vector<std::tuple<MacroColorDecoEnumClass, ccharp>> createReference()
{
  return{ std::make_tuple(MacroColorDecoEnumClass::DarkGray2, DarkGray2C),
          std::make_tuple(MacroColorDecoEnumClass::MidGray2, MidGray2C),
          std::make_tuple(MacroColorDecoEnumClass::LightGray2, LightGray2C) };
}

ccharp DarkGray3C = "DarkGray3";
ccharp MidGray3C = "MidGray3";
ccharp LightGray3C = "LightGray3";

#define MACROCOLOR_DECO_TYPED_ENUM_SPEC (MacroColorDecoTypedEnum, short, ccharp, \
  (DarkGray3, DarkGray3C)(MidGray3, MidGray3C)(LightGray3, LightGray3C))
ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM(MACROCOLOR_DECO_TYPED_ENUM_SPEC)
ENUM_EXTEND_DEFINE_1_DECORATED_TYPED_ENUM(MACROCOLOR_DECO_TYPED_ENUM_SPEC)

template<>
std::vector<std::tuple<MacroColorDecoTypedEnum, ccharp>> createReference()
{
  return{ std::make_tuple(MacroColorDecoTypedEnum::DarkGray3, DarkGray3C),
          std::make_tuple(MacroColorDecoTypedEnum::MidGray3, MidGray3C),
          std::make_tuple(MacroColorDecoTypedEnum::LightGray3, LightGray3C) };
}


ccharp DarkGray4C = "DarkGray4";
ccharp MidGray4C = "MidGray4";
ccharp LightGray4C = "LightGray4";

#define MACROCOLOR_DECO_TYPED_ENUM_CLASS_SPEC (MacroColorDecoTypedEnumClass, short, ccharp, \
  (DarkGray4, DarkGray4C)(MidGray4, MidGray4C)(LightGray4, LightGray4C))
ENUM_EXTEND_DECLARE_1_DECORATED_TYPED_ENUM_CLASS(MACROCOLOR_DECO_TYPED_ENUM_CLASS_SPEC)
ENUM_EXTEND_DEFINE_1_DECORATED_TYPED_ENUM_CLASS(MACROCOLOR_DECO_TYPED_ENUM_CLASS_SPEC)

template<>
std::vector<std::tuple<MacroColorDecoTypedEnumClass, ccharp>> createReference()
{
  return{ std::make_tuple(MacroColorDecoTypedEnumClass::DarkGray4, DarkGray4C),
          std::make_tuple(MacroColorDecoTypedEnumClass::MidGray4, MidGray4C),
          std::make_tuple(MacroColorDecoTypedEnumClass::LightGray4, LightGray4C) };
}




template <typename T>
class DeclareDecoratedEnumTest : public ::testing::Test
{
public:
  using DecoPair = std::tuple<T, ccharp>;
  DeclareDecoratedEnumTest() : reference(createReference<DecoPair>()) {}
  std::vector<DecoPair> reference;
};

typedef ::testing::Types<MacroColorDecoEnum, 
                         MacroColorDecoEnumClass, 
                         MacroColorDecoTypedEnum, 
                         MacroColorDecoTypedEnumClass> ValueTestTypes;


TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, Size)
{
  EXPECT_EQ(3, (enum_extend::extender<TypeParam, ccharp>::size()));
}

TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, Range)
{
  size_t i = 0;
  for (auto c : enum_extend::range<TypeParam, ccharp>())
  {
    EXPECT_EQ(this->reference[i], c);
    ++i;
  }
}

TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, ForwardIterators)
{
  EXPECT_TRUE(std::equal(this->reference.begin(),
    this->reference.end(),
    enum_extend::extender<TypeParam, ccharp>::begin()));
  EXPECT_TRUE(std::equal(this->reference.cbegin(),
    this->reference.cend(),
    enum_extend::extender<TypeParam, ccharp>::cbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam, ccharp>::begin(),
    enum_extend::extender<TypeParam, ccharp>::end(),
    this->reference.begin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam, ccharp>::cbegin(),
    enum_extend::extender<TypeParam, ccharp>::cend(),
    this->reference.cbegin()));
}

TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, ReverseIterators)
{
  EXPECT_TRUE(std::equal(this->reference.rbegin(),
    this->reference.rend(),
    enum_extend::extender<TypeParam, ccharp>::rbegin()));
  EXPECT_TRUE(std::equal(this->reference.crbegin(),
    this->reference.crend(),
    enum_extend::extender<TypeParam, ccharp>::crbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam, ccharp>::rbegin(),
    enum_extend::extender<TypeParam, ccharp>::rend(),
    this->reference.rbegin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam, ccharp>::crbegin(),
    enum_extend::extender<TypeParam, ccharp>::crend(),
    this->reference.crbegin()));
}


TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, PlusPlusOperator)
{
  auto c = std::get<0>(this->reference[0]);
  EXPECT_EQ(std::get<0>(this->reference[1]), ++c);
  EXPECT_EQ(std::get<0>(this->reference[2]), ++c);
  EXPECT_THROW(++c, std::exception);
}

TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, OperatorPlusPlus)
{
  auto c = std::get<0>(this->reference[0]);
  EXPECT_EQ(std::get<0>(this->reference[0]), c++);
  EXPECT_EQ(std::get<0>(this->reference[1]), c++);
  EXPECT_EQ(std::get<0>(this->reference[2]), c);
  EXPECT_THROW(c++, std::exception);
}


TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, MinusMinusOperator)
{
  auto c = std::get<0>(this->reference[2]);
  EXPECT_EQ(std::get<0>(this->reference[1]), --c);
  EXPECT_EQ(std::get<0>(this->reference[0]), --c);

  EXPECT_THROW(--c, std::exception);
}

TYPED_TEST_CASE(DeclareDecoratedEnumTest, ValueTestTypes);
TYPED_TEST(DeclareDecoratedEnumTest, OperatorMinusMinus)
{
  auto c = std::get<0>(this->reference[2]);
  EXPECT_EQ(std::get<0>(this->reference[2]), c--);
  EXPECT_EQ(std::get<0>(this->reference[1]), c--);
  EXPECT_EQ(std::get<0>(this->reference[0]), c);

  EXPECT_THROW(c--, std::exception);
}

