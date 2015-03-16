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

enum Blue
{
  DarkBlue, MidBlue, LightBlue
};

using ccharp = const char*;
ccharp DarkBlueC = "DarkBlue";
ccharp MidBlueC = "MidBlue";
ccharp LightBlueC = "LightBlue";

struct StructuredDeco
{
  std::string text;
};

bool operator==(const StructuredDeco& x, const StructuredDeco& y)
{
  return x.text == y.text;
}

const StructuredDeco sdDarkBlue = { "Nice Dark Blue" };
const StructuredDeco sdMidBlue = { "Nice Mid Blue" };
const StructuredDeco sdLightBlue = { "Nice Light Blue" };

template <>
enum_extend::extender<Blue, StructuredDeco, ccharp>::instances 
  enum_extend::extender<Blue, StructuredDeco, ccharp>::s_instances = {};

enum_extend::extender<Blue, StructuredDeco, ccharp> BlueExtender({ 
  std::make_tuple( Blue::DarkBlue, sdDarkBlue, DarkBlueC ), 
  std::make_tuple( Blue::MidBlue, sdMidBlue, MidBlueC ), 
  std::make_tuple( Blue::LightBlue, sdLightBlue, LightBlueC ) });

using DecoratedBlue = std::tuple<Blue, StructuredDeco, ccharp>;
DecoratedBlue& operator++(DecoratedBlue& e);
DecoratedBlue& operator--(DecoratedBlue& e);
DecoratedBlue operator++(DecoratedBlue& e, int);
DecoratedBlue operator--(DecoratedBlue& e, int);


DecoratedBlue& operator++(DecoratedBlue& e) { return enum_extend::extender<Blue, StructuredDeco, ccharp>::increment(e); }
DecoratedBlue& operator--(DecoratedBlue& e) { return enum_extend::extender<Blue, StructuredDeco, ccharp>::decrement(e); }
DecoratedBlue operator++(DecoratedBlue& e, int) {
    auto tmp = e;                                                            
    enum_extend::extender<Blue, StructuredDeco, ccharp>::increment(e);
    return tmp;                                                              
  }          

DecoratedBlue operator--(DecoratedBlue& e, int) {
    auto tmp = e;                                                            
    enum_extend::extender<Blue, StructuredDeco, ccharp>::decrement(e);
    return tmp;                                                              
  }                                                                          





class EnumExtendWitMultipleDecorationTest : public ::testing::Test
{
public:
  EnumExtendWitMultipleDecorationTest()
    : reference({ std::make_tuple( Blue::DarkBlue, sdDarkBlue, DarkBlueC ), 
                  std::make_tuple( Blue::MidBlue, sdMidBlue, MidBlueC ), 
                  std::make_tuple( Blue::LightBlue, sdLightBlue, LightBlueC ) })
  {}

  std::vector<std::tuple<Blue, StructuredDeco, ccharp>> reference;
};


TEST_F(EnumExtendWitMultipleDecorationTest, Size)
{
  EXPECT_EQ(3, (enum_extend::extender<Blue, StructuredDeco, ccharp>::size()));
}

TEST_F(EnumExtendWitMultipleDecorationTest, Range)
{
  size_t i = 0;
  for (auto c : enum_extend::range<Blue, StructuredDeco, ccharp>())
  {
    EXPECT_EQ(reference[i], c);
    ++i;
  }
}

TEST_F(EnumExtendWitMultipleDecorationTest, ValueRange)
{
  size_t i = 0;
  for (auto c : enum_extend::enum_range<Blue, StructuredDeco, ccharp>())
  {
    EXPECT_EQ(std::get<0>(reference[i]), c);
    ++i;
  }
}


TEST_F(EnumExtendWitMultipleDecorationTest, FirstDecorationRange)
{
  size_t i = 0;
  for (auto c : enum_extend::decoration_range<1, Blue, StructuredDeco, ccharp>())
  {
    EXPECT_EQ(std::get<1>(reference[i]), c);
    ++i;
  }
}

TEST_F(EnumExtendWitMultipleDecorationTest, SecondDecorationRange)
{
  size_t i = 0;
  for (auto c : enum_extend::decoration_range<2, Blue, StructuredDeco, ccharp>())
  {
    EXPECT_EQ(std::get<2>(reference[i]), c);
    ++i;
  }
}

TEST_F(EnumExtendWitMultipleDecorationTest, GetDecorationRange)
{
  EXPECT_EQ(DarkBlueC, (enum_extend::extender<Blue, StructuredDeco, ccharp>::get_decoration<ccharp>(Blue::DarkBlue)) );
  EXPECT_EQ(LightBlueC, (enum_extend::extender<Blue, StructuredDeco, ccharp>::get_decoration<ccharp>(Blue::LightBlue)));

  EXPECT_EQ(sdDarkBlue, (enum_extend::extender<Blue, StructuredDeco, ccharp>::get_decoration<StructuredDeco>(Blue::DarkBlue)));
  EXPECT_EQ(sdLightBlue, (enum_extend::extender<Blue, StructuredDeco, ccharp>::get_decoration<StructuredDeco>(Blue::LightBlue)));
}

TEST_F(EnumExtendWitMultipleDecorationTest, ForwardIterators)
{
  EXPECT_TRUE(std::equal(reference.begin(), 
                         reference.end(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::begin()));
  EXPECT_TRUE(std::equal(reference.cbegin(), 
                         reference.cend(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::cbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<Blue, StructuredDeco, ccharp>::begin(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::end(), 
                         reference.begin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<Blue, StructuredDeco, ccharp>::cbegin(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::cend(), 
                         reference.cbegin()));
}

TEST_F(EnumExtendWitMultipleDecorationTest, ReverseIterators)
{
  EXPECT_TRUE(std::equal(reference.rbegin(), 
                         reference.rend(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::rbegin()));
  EXPECT_TRUE(std::equal(reference.crbegin(), 
                         reference.crend(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::crbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<Blue, StructuredDeco, ccharp>::rbegin(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::rend(), 
                         reference.rbegin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<Blue, StructuredDeco, ccharp>::crbegin(), 
                         enum_extend::extender<Blue, StructuredDeco, ccharp>::crend(), 
                         reference.crbegin()));
}

TEST_F(EnumExtendWitMultipleDecorationTest, PlusPlusOperator)
{
  auto c = std::make_tuple(Blue::DarkBlue, sdDarkBlue, DarkBlueC);
  EXPECT_EQ(std::make_tuple(Blue::MidBlue, sdMidBlue, MidBlueC), ++c);
  EXPECT_EQ(std::make_tuple(Blue::LightBlue, sdLightBlue, LightBlueC), ++c);
  EXPECT_THROW(++c, std::exception);
}

TEST_F(EnumExtendWitMultipleDecorationTest, OperatorPlusPlus)
{
  auto c = std::make_tuple(Blue::DarkBlue, sdDarkBlue, DarkBlueC);
  EXPECT_EQ(std::make_tuple(Blue::DarkBlue, sdDarkBlue, DarkBlueC), c++);
  EXPECT_EQ(std::make_tuple(Blue::MidBlue, sdMidBlue, MidBlueC), c++);
  EXPECT_EQ(std::make_tuple(Blue::LightBlue, sdLightBlue, LightBlueC), c);
  EXPECT_THROW(c++, std::exception);
}


TEST_F(EnumExtendWitMultipleDecorationTest, MinusMinusOperator)
{
  auto c = std::make_tuple(Blue::LightBlue, sdLightBlue, LightBlueC);
  EXPECT_EQ(std::make_tuple(Blue::MidBlue, sdMidBlue, MidBlueC), --c);
  EXPECT_EQ(std::make_tuple(Blue::DarkBlue, sdDarkBlue, DarkBlueC), --c);
  
  EXPECT_THROW(--c, std::exception);
}

TEST_F(EnumExtendWitMultipleDecorationTest, OperatorMinusMinus)
{
  auto c = std::make_tuple(Blue::LightBlue, sdLightBlue, LightBlueC);
  EXPECT_EQ(std::make_tuple(Blue::LightBlue, sdLightBlue, LightBlueC), c--);
  EXPECT_EQ(std::make_tuple(Blue::MidBlue, sdMidBlue, MidBlueC), c--);
  EXPECT_EQ(std::make_tuple(Blue::DarkBlue, sdDarkBlue, DarkBlueC), c);
  
  EXPECT_THROW(c--, std::exception);
}

