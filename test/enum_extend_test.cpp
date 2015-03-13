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

enum Color
{
  Red, Green, Blue
};

template <>
enum_extend::extender<Color>::instances enum_extend::extender<Color>::s_instances = {};
enum_extend::extender<Color>  ColorExtender(Color::Red, Color::Green, Color::Blue);


Color& operator++(Color& e);                                                  
Color& operator--(Color& e);                                                  
Color operator++(Color& e, int);                                              
Color operator--(Color& e, int);                                              


  Color& operator++(Color& e) { return enum_extend::extender<Color>::increment(e); } 
  Color& operator--(Color& e) { return enum_extend::extender<Color>::decrement(e); }
  Color operator++(Color& e, int) {                                            
    auto tmp = e;                                                            
    enum_extend::extender<Color>::increment(e);
    return tmp;                                                              
  }                                                                          
  Color operator--(Color& e, int) {                                            
    auto tmp = e;                                                            
    enum_extend::extender<Color>::decrement(e);
    return tmp;                                                              
  }                                                                          





class EnumExtenderTest : public ::testing::Test
{
public:
  EnumExtenderTest()
    : reference({Color::Red, Color::Green, Color::Blue})
  {}

  std::vector<Color> reference;
};


TEST_F(EnumExtenderTest, Size)
{
  EXPECT_EQ(3, (enum_extend::extender<Color>::size()));
}

TEST_F(EnumExtenderTest, Range)
{
  size_t i = 0;
  for (auto c : enum_extend::range<Color>())
  {
    EXPECT_EQ(reference[i], c);
    ++i;
  }
}


TEST_F(EnumExtenderTest, ForwardIterators)
{
  EXPECT_TRUE(std::equal(reference.begin(), reference.end(), enum_extend::extender<Color>::begin()));
  EXPECT_TRUE(std::equal(reference.cbegin(), reference.cend(), enum_extend::extender<Color>::cbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<Color>::begin(), enum_extend::extender<Color>::end(), reference.begin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<Color>::cbegin(), enum_extend::extender<Color>::cend(), reference.cbegin()));
}

TEST_F(EnumExtenderTest, ReverseIterators)
{
  EXPECT_TRUE(std::equal(reference.rbegin(), reference.rend(), enum_extend::extender<Color>::rbegin()));
  EXPECT_TRUE(std::equal(reference.crbegin(), reference.crend(), enum_extend::extender<Color>::crbegin()));

  EXPECT_TRUE(std::equal(enum_extend::extender<Color>::rbegin(), enum_extend::extender<Color>::rend(), reference.rbegin()));
  EXPECT_TRUE(std::equal(enum_extend::extender<Color>::crbegin(), enum_extend::extender<Color>::crend(), reference.crbegin()));
}

TEST_F(EnumExtenderTest, PlusPlusOperator)
{
  Color c = Color::Red;
  EXPECT_EQ(Color::Green, ++c);
  EXPECT_EQ(Color::Blue, ++c);
  EXPECT_THROW(++c, std::exception);
}

TEST_F(EnumExtenderTest, OperatorPlusPlus)
{
  Color c = Color::Red;
  EXPECT_EQ(Color::Red, c++);
  EXPECT_EQ(Color::Green, c++);
  EXPECT_EQ(Color::Blue, c);
  EXPECT_THROW(c++, std::exception);
}


TEST_F(EnumExtenderTest, MinusMinusOperator)
{
  Color c = Color::Blue;
  EXPECT_EQ(Color::Green, --c);
  EXPECT_EQ(Color::Red, --c);
  
  EXPECT_THROW(--c, std::exception);
}

TEST_F(EnumExtenderTest, OperatorMinusMinus)
{
  Color c = Color::Blue;
  EXPECT_EQ(Color::Blue, c--);
  EXPECT_EQ(Color::Green, c--);
  EXPECT_EQ(Color::Red, c);
  
  EXPECT_THROW(c--, std::exception);
}

