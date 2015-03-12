///////////////////////////////////////////////////////////////////
//
// Copyright 2015 Felix Petriconi
//
// License: http://boost.org/LICENSE_1_0.txt, Boost License 1.0
//
// Authors: http://petriconi.net, Felix Petriconi
//
//////////////////////////////////////////////////////////////////

#include "enum_extend/declare_enum.hpp"
#include "enum_extend/declare_enum_class.hpp"
#include "enum_extend/declare_typed_enum.hpp"
#include "enum_extend/declare_typed_enum_class.hpp"

#include "enum_extend/define_enum.hpp"
#include "enum_extend/define_enum_class.hpp"
#include "enum_extend/define_typed_enum.hpp"
#include "enum_extend/define_typed_enum_class.hpp"

#include "enum_extend/range.hpp"

#include <gtest/gtest.h>
#include <vector>

template <typename T>
std::vector<T> createReference();

#define MACROCOLOR_ENUM_SPEC (MacroColorEnum, (Red1)(Green1)(Blue1))
ENUM_EXTEND_DECLARE_ENUM(MACROCOLOR_ENUM_SPEC)
ENUM_EXTEND_DEFINE_ENUM(MACROCOLOR_ENUM_SPEC)

template<>
std::vector<MacroColorEnum> createReference()
{
  return { MacroColorEnum::Red1, MacroColorEnum::Green1, MacroColorEnum::Blue1 };
}

#define MACROCOLOR_ENUM_CLASS_SPEC (MacroColorEnumClass, (Red2)(Green2)(Blue2))
ENUM_EXTEND_DECLARE_ENUM_CLASS(MACROCOLOR_ENUM_CLASS_SPEC)
ENUM_EXTEND_DEFINE_ENUM_CLASS(MACROCOLOR_ENUM_CLASS_SPEC)

template<>
std::vector<MacroColorEnumClass> createReference()
{
  return{ MacroColorEnumClass::Red2, MacroColorEnumClass::Green2, MacroColorEnumClass::Blue2 };
}


#define MACROCOLOR_TYPED_ENUM_SPEC (MacroColorTypedEnum, short, (Red3)(Green3)(Blue3))
ENUM_EXTEND_DECLARE_TYPED_ENUM(MACROCOLOR_TYPED_ENUM_SPEC)
ENUM_EXTEND_DEFINE_TYPED_ENUM(MACROCOLOR_TYPED_ENUM_SPEC)

template<>
std::vector<MacroColorTypedEnum> createReference()
{
  return{ MacroColorTypedEnum::Red3, MacroColorTypedEnum::Green3, MacroColorTypedEnum::Blue3 };
}

#define MACROCOLOR_TYPED_ENUM_CLASS_SPEC (MacroColorTypedEnumClass, char, (Red4)(Green4)(Blue4))
ENUM_EXTEND_DECLARE_TYPED_ENUM_CLASS(MACROCOLOR_TYPED_ENUM_CLASS_SPEC)
ENUM_EXTEND_DEFINE_TYPED_ENUM_CLASS(MACROCOLOR_TYPED_ENUM_CLASS_SPEC)

template<>
std::vector<MacroColorTypedEnumClass> createReference()
{
  return{ MacroColorTypedEnumClass::Red4, MacroColorTypedEnumClass::Green4, MacroColorTypedEnumClass::Blue4 };
}

template <typename T>
class DeclareEnumTest : public ::testing::Test
{
public:
  DeclareEnumTest() : reference(createReference<T>()) {}
  std::vector<T> reference;
};

typedef ::testing::Types<MacroColorEnum, MacroColorEnumClass, MacroColorTypedEnum, MacroColorTypedEnumClass> ValueTestTypes;


TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, Size)
{
  EXPECT_EQ(3, (enum_extend::extender<TypeParam >::size()));
}

TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, Range)
{
  size_t i = 0;
  for (auto c : enum_extend::range<TypeParam>())
  {
    EXPECT_EQ(this->reference[i], c);
    ++i;
  }
}

TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, ForwardIterators)
{
  EXPECT_TRUE(std::equal(this->reference.begin(), 
                         this->reference.end(), 
                         enum_extend::extender<TypeParam>::begin()));
  EXPECT_TRUE(std::equal(this->reference.cbegin(), 
                         this->reference.cend(), 
                         enum_extend::extender<TypeParam>::cbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam>::begin(), 
                         enum_extend::extender<TypeParam>::end(), 
                         this->reference.begin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam>::cbegin(), 
                         enum_extend::extender<TypeParam>::cend(), 
                         this->reference.cbegin()));
}

TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, ReverseIterators)
{
  EXPECT_TRUE(std::equal(this->reference.rbegin(), 
                         this->reference.rend(), 
                         enum_extend::extender<TypeParam>::rbegin()));
  EXPECT_TRUE(std::equal(this->reference.crbegin(), 
                         this->reference.crend(), 
                         enum_extend::extender<TypeParam>::crbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam>::rbegin(), 
                         enum_extend::extender<TypeParam>::rend(), 
                         this->reference.rbegin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<TypeParam>::crbegin(), 
                         enum_extend::extender<TypeParam>::crend(), 
                         this->reference.crbegin()));
}


TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, PlusPlusOperator)
{
  auto c = this->reference[0];
  EXPECT_EQ(this->reference[1], ++c);
  EXPECT_EQ(this->reference[2], ++c);
  EXPECT_THROW(++c, std::exception);
}

TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, OperatorPlusPlus)
{
  auto c = this->reference[0];
  EXPECT_EQ(this->reference[0], c++);
  EXPECT_EQ(this->reference[1], c++);
  EXPECT_EQ(this->reference[2], c);
  EXPECT_THROW(c++, std::exception);
}


TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, MinusMinusOperator)
{
  auto c = this->reference[2];
  EXPECT_EQ(this->reference[1], --c);
  EXPECT_EQ(this->reference[0], --c);
  
  EXPECT_THROW(--c, std::exception);
}

TYPED_TEST_CASE(DeclareEnumTest, ValueTestTypes);
TYPED_TEST(DeclareEnumTest, OperatorMinusMinus)
{
  auto c = this->reference[2];
  EXPECT_EQ(this->reference[2], c--);
  EXPECT_EQ(this->reference[1], c--);
  EXPECT_EQ(this->reference[0], c);
  
  EXPECT_THROW(c--, std::exception);
}

