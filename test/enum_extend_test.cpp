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

#include <gtest/gtest.h>
#include <vector>


template <typename T>
std::vector<T> createReference();


enum OneValue
{
  OV_1
};

template <>
std::vector<OneValue> createReference()
{
  return{ OneValue::OV_1 };
}

template <>
enum_extend::extender<OneValue>::instances enum_extend::extender<OneValue>::all_values = {
  OneValue::OV_1
};


OneValue& operator++(OneValue& e) { return enum_extend::extender<OneValue>::increment(e); }
OneValue& operator--(OneValue& e) { return enum_extend::extender<OneValue>::decrement(e); }
OneValue operator++(OneValue& e, int) {
  auto tmp = e;
  enum_extend::extender<OneValue>::increment(e);
  return tmp;
}
OneValue operator--(OneValue& e, int) {
  auto tmp = e;
  enum_extend::extender<OneValue>::decrement(e);
  return tmp;
}


enum TwoValues
{
  TV_1,
  TV_2
};

template <>
std::vector<TwoValues> createReference()
{
  return{ TwoValues::TV_1, TwoValues::TV_2 };
}

template <>
enum_extend::extender<TwoValues>::instances enum_extend::extender<TwoValues>::all_values = {
  TwoValues::TV_1, TV_2
};


TwoValues& operator++(TwoValues& e) { return enum_extend::extender<TwoValues>::increment(e); }
TwoValues& operator--(TwoValues& e) { return enum_extend::extender<TwoValues>::decrement(e); }
TwoValues operator++(TwoValues& e, int) {
  auto tmp = e;
  enum_extend::extender<TwoValues>::increment(e);
  return tmp;
}
TwoValues operator--(TwoValues& e, int) {
  auto tmp = e;
  enum_extend::extender<TwoValues>::decrement(e);
  return tmp;
}


enum ManyValues
{
  MV_01, MV_02, MV_03, MV_04, MV_05, MV_06, MV_07, MV_08, MV_09, MV_10,
  MV_11, MV_12, MV_13, MV_14, MV_15, MV_16, MV_17, MV_18, MV_19, MV_20,
  MV_21, MV_22, MV_23, MV_24, MV_25, MV_26, MV_27, MV_28, MV_29, MV_30,
  MV_31, MV_32, MV_33, MV_34, MV_35, MV_36, MV_37, MV_38, MV_39, MV_40
};

template <>
std::vector<ManyValues> createReference()
{
  return { 
    ManyValues::MV_01, ManyValues::MV_02, ManyValues::MV_03, ManyValues::MV_04, 
    ManyValues::MV_05, ManyValues::MV_06, ManyValues::MV_07, ManyValues::MV_08, 
    ManyValues::MV_09, ManyValues::MV_10,
    ManyValues::MV_11, ManyValues::MV_12, ManyValues::MV_13, ManyValues::MV_14, 
    ManyValues::MV_15, ManyValues::MV_16, ManyValues::MV_17, ManyValues::MV_18, 
    ManyValues::MV_19, ManyValues::MV_20,
    ManyValues::MV_21, ManyValues::MV_22, ManyValues::MV_23, ManyValues::MV_24, 
    ManyValues::MV_25, ManyValues::MV_26, ManyValues::MV_27, ManyValues::MV_28, 
    ManyValues::MV_29, ManyValues::MV_30,
    ManyValues::MV_31, ManyValues::MV_32, ManyValues::MV_33, ManyValues::MV_34, 
    ManyValues::MV_35, ManyValues::MV_36, ManyValues::MV_37, ManyValues::MV_38, 
    ManyValues::MV_39, ManyValues::MV_40
  };
}

template <>
enum_extend::extender<ManyValues>::instances 
  enum_extend::extender<ManyValues>::all_values = {
  ManyValues::MV_01, ManyValues::MV_02, ManyValues::MV_03, ManyValues::MV_04, 
  ManyValues::MV_05, ManyValues::MV_06, ManyValues::MV_07, ManyValues::MV_08, 
  ManyValues::MV_09, ManyValues::MV_10,
  ManyValues::MV_11, ManyValues::MV_12, ManyValues::MV_13, ManyValues::MV_14, 
  ManyValues::MV_15, ManyValues::MV_16, ManyValues::MV_17, ManyValues::MV_18, 
  ManyValues::MV_19, ManyValues::MV_20,
  ManyValues::MV_21, ManyValues::MV_22, ManyValues::MV_23, ManyValues::MV_24, 
  ManyValues::MV_25, ManyValues::MV_26, ManyValues::MV_27, ManyValues::MV_28, 
  ManyValues::MV_29, ManyValues::MV_30,
  ManyValues::MV_31, ManyValues::MV_32, ManyValues::MV_33, ManyValues::MV_34, 
  ManyValues::MV_35, ManyValues::MV_36, ManyValues::MV_37, ManyValues::MV_38, 
  ManyValues::MV_39, ManyValues::MV_40
};


ManyValues& operator++(ManyValues& e) { return enum_extend::extender<ManyValues>::increment(e); }
ManyValues& operator--(ManyValues& e) { return enum_extend::extender<ManyValues>::decrement(e); }
ManyValues operator++(ManyValues& e, int) {
  auto tmp = e;                                                            
  enum_extend::extender<ManyValues>::increment(e);
  return tmp;                                                              
}                                                                          
ManyValues operator--(ManyValues& e, int) {
  auto tmp = e;                                                            
  enum_extend::extender<ManyValues>::decrement(e);
  return tmp;                                                              
}                                                                          


template <typename T>
class EnumExtenderTest : public ::testing::Test
{
public:
  EnumExtenderTest()
    : reference(createReference<T>())
  {}

  std::vector<T> reference;
};

typedef ::testing::Types<OneValue, TwoValues, ManyValues> ValueTestTypes;

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, Size)
{
  EXPECT_EQ(this->reference.size(), (enum_extend::extender<TypeParam>::size()));
}

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, Range)
{
  size_t i = 0;
  for (auto x : enum_extend::range<TypeParam>())
  {
    EXPECT_EQ(this->reference[i], x);
    ++i;
  }
}

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, ForwardIterators)
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

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, ReverseIterators)
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

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, PlusPlusOperator)
{
  auto x = this->reference[0];
  for (auto i = 1; i < this->reference.size(); ++i)
  {
    EXPECT_EQ(this->reference[i], ++x);
  }
  
  EXPECT_THROW(++x, std::exception);
}

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, OperatorPlusPlus)
{
  auto x = this->reference.front();
  for (auto i = 0; i < this->reference.size(); ++i)
  {
    if (i != this->reference.size() - 1)
    {
      EXPECT_EQ(this->reference[i], x++);
    }
    else
    {
      EXPECT_EQ(this->reference[i], x);
    }
  }
  EXPECT_THROW(x++, std::exception);
}

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, MinusMinusOperator)
{
  auto x = this->reference.back();
  if (this->reference.size() > 1) {
    for (auto i = this->reference.size() - 1; i > 0; --i)
    {
      EXPECT_EQ(this->reference[i-1], --x);
    }
  }
  EXPECT_THROW(--x, std::exception);
}

TYPED_TEST_CASE(EnumExtenderTest, ValueTestTypes);
TYPED_TEST(EnumExtenderTest, OperatorMinusMinus)
{
  auto x = this->reference.back();
  
  for (auto i = this->reference.size() - 1; i > 0; --i)
  {
    if (i != 0)
    {
      EXPECT_EQ(this->reference[i], x--);
    }
    else
    {
      EXPECT_EQ(this->reference[i], x);
    }
  }
    
  EXPECT_THROW(x--, std::exception);
}

