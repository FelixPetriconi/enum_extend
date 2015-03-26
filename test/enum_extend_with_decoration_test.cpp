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
#include "enum_extend/decoration_range.hpp"

#include <gtest/gtest.h>
#include <vector>

enum Gray
{
  DarkGray, MidGray, LightGray
};

using ccharp = const char*;
ccharp DarkGrayC = "DarkGray";
ccharp MidGrayC = "MidGray";
ccharp LightGrayC = "LightGray";

template <>
enum_extend::extender<Gray, ccharp>::instances 
  enum_extend::extender<Gray, ccharp>::all_values = {
  
  std::make_tuple( Gray::DarkGray, DarkGrayC ), 
  std::make_tuple( Gray::MidGray, MidGrayC ), 
  std::make_tuple( Gray::LightGray, LightGrayC ) 
};


Gray& operator++(Gray& e) { return enum_extend::extender<Gray, ccharp>::increment(e); }
Gray& operator--(Gray& e) { return enum_extend::extender<Gray, ccharp>::decrement(e); }
Gray operator++(Gray& e, int) {
  auto tmp = e;                                                            
  enum_extend::extender<Gray, ccharp>::increment(e);
  return tmp;                                                              
}          

Gray operator--(Gray& e, int) {
  auto tmp = e;                                                            
  enum_extend::extender<Gray, ccharp>::decrement(e);
  return tmp;                                                              
}                                                                          


class EnumExtendWitDecorationTest : public ::testing::Test
{
public:
  EnumExtendWitDecorationTest()
    : reference({ std::make_tuple( Gray::DarkGray, DarkGrayC ), 
                  std::make_tuple( Gray::MidGray, MidGrayC ), 
                  std::make_tuple( Gray::LightGray, LightGrayC ) })
  {}

  std::vector<std::tuple<Gray, ccharp>> reference;
};


TEST_F(EnumExtendWitDecorationTest, Size)
{
  EXPECT_EQ(3, (enum_extend::extender<Gray, ccharp>::size()));
}

TEST_F(EnumExtendWitDecorationTest, Range)
{
  size_t i = 0;
  for (auto c : enum_extend::range<Gray, ccharp>())
  {
    EXPECT_EQ(reference[i], c);
    ++i;
  }
}

TEST_F(EnumExtendWitDecorationTest, ValueRange)
{
  size_t i = 0;
  for (auto c : enum_extend::enum_range<Gray, ccharp>())
  {
    EXPECT_EQ(std::get<0>(reference[i]), c);
    ++i;
  }
}


TEST_F(EnumExtendWitDecorationTest, DecorationRange)
{
  size_t i = 0;
  for (auto c : enum_extend::decoration_range<1, Gray, ccharp>())
  {
    EXPECT_EQ(std::get<1>(reference[i]), c);
    ++i;
  }
}


TEST_F(EnumExtendWitDecorationTest, ForwardIterators)
{
  EXPECT_TRUE(std::equal(reference.begin(), 
                         reference.end(), 
                         enum_extend::extender<Gray, ccharp>::begin()));
  EXPECT_TRUE(std::equal(reference.cbegin(), 
                         reference.cend(), 
                         enum_extend::extender<Gray, ccharp>::cbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<Gray, ccharp>::begin(), 
                         enum_extend::extender<Gray, ccharp>::end(), 
                         reference.begin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<Gray, ccharp>::cbegin(), 
                         enum_extend::extender<Gray, ccharp>::cend(), 
                         reference.cbegin()));
}

TEST_F(EnumExtendWitDecorationTest, ReverseIterators)
{
  EXPECT_TRUE(std::equal(reference.rbegin(), 
                         reference.rend(), 
                         enum_extend::extender<Gray, ccharp>::rbegin()));
  EXPECT_TRUE(std::equal(reference.crbegin(), 
                         reference.crend(), 
                         enum_extend::extender<Gray, ccharp>::crbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<Gray, ccharp>::rbegin(), 
                         enum_extend::extender<Gray, ccharp>::rend(), 
                         reference.rbegin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<Gray, ccharp>::crbegin(), 
                         enum_extend::extender<Gray, ccharp>::crend(), 
                         reference.crbegin()));
}

TEST_F(EnumExtendWitDecorationTest, PlusPlusOperator)
{
  auto c = Gray::DarkGray;
  EXPECT_EQ(Gray::MidGray, ++c);
  EXPECT_EQ(Gray::LightGray, ++c);
  EXPECT_THROW(++c, std::exception);
}

TEST_F(EnumExtendWitDecorationTest, OperatorPlusPlus)
{
  auto c = Gray::DarkGray;
  EXPECT_EQ(Gray::DarkGray, c++);
  EXPECT_EQ(Gray::MidGray, c++);
  EXPECT_EQ(Gray::LightGray, c);
  EXPECT_THROW(c++, std::exception);
}


TEST_F(EnumExtendWitDecorationTest, MinusMinusOperator)
{
  auto c = Gray::LightGray;
  EXPECT_EQ(Gray::MidGray, --c);
  EXPECT_EQ(Gray::DarkGray, --c);
  
  EXPECT_THROW(--c, std::exception);
}

TEST_F(EnumExtendWitDecorationTest, OperatorMinusMinus)
{
  auto c = Gray::LightGray;
  EXPECT_EQ(Gray::LightGray, c--);
  EXPECT_EQ(Gray::MidGray, c--);
  EXPECT_EQ(Gray::DarkGray, c);
  
  EXPECT_THROW(c--, std::exception);
}

