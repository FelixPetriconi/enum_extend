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

enum_extend::extender<Color>::instances enum_extend::extender<Color>::s_instances;
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


// 
// 
// #define COLOR_DECORATOR_SPECIIFIERS (DecoratedColor, Color2, const char*, \
//                                     (Black, "Black")\
//                                     (Red, "Red")\
//                                     (Green, "Green")\
//                                     (Blue, "Blue")\
//                                     (White, "White")) \
// 
// 
// ENUM_LIB_DECLARE_ENUM_DECORATOR(COLOR_DECORATOR_SPECIIFIERS)
// 
// ENUM_LIB_DEFINE_ENUM_DECORATOR(COLOR_DECORATOR_SPECIIFIERS)
// 
// 
// class EnumDecoratorTest : public ::testing::Test
// {
// public:
//   EnumDecoratorTest()
//     : enumReference({ Color2::Black, Color2::Red, Color2::Green, Color2::Blue, Color2::White })
//     , decoReference({"Black", "Red", "Green", "Blue", "White"})
//   {
// 
//   }
//   std::vector<Color2> enumReference;
//   std::vector<const char*> decoReference;
// 
// };
// 
// TEST_F(EnumDecoratorTest, Size)
// {
//   EXPECT_EQ(5, DecoratedColor::size());
// }
// 
// struct EqualStr
// {
//   using result_type = bool;
//   
//   bool operator() (const char* x, const char* y) const {
//     EXPECT_STREQ(y, x);
//     return strcmp(x, y) == 0;
//   }
// };
// 
// TEST_F(EnumDecoratorTest, ForwardIterator)
// {
//   EXPECT_TRUE(std::equal(enumReference.begin(), 
//                          enumReference.end(), 
//                          DecoratedColor::vbegin()));
//   
//   EXPECT_TRUE(std::equal(DecoratedColor::vbegin(), 
//                          DecoratedColor::vend(), 
//                          enumReference.begin()));
// 
//   EXPECT_TRUE(std::equal(enumReference.begin(), 
//                          enumReference.end(), 
//                          std::begin(enum_extend::enum_value_range<DecoratedColor>())));
// 
//   EXPECT_TRUE(std::equal(std::begin(enum_extend::enum_value_range<DecoratedColor>()), 
//                          std::end(enum_extend::enum_value_range<DecoratedColor>()), 
//                          enumReference.begin()));
// 
// 
//   EXPECT_TRUE(std::equal(decoReference.begin(), 
//                          decoReference.end(), 
//                          DecoratedColor::dbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(DecoratedColor::dbegin(), 
//                          DecoratedColor::dend(), 
//                          decoReference.begin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(decoReference.begin(), 
//                          decoReference.end(), 
//                          std::begin(enum_extend::enum_decoration_range<DecoratedColor>()), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(std::begin(enum_extend::enum_decoration_range<DecoratedColor>()),
//                          std::end(enum_extend::enum_decoration_range<DecoratedColor>()), 
//                          decoReference.begin(), 
//                          EqualStr()));
// }
// 
// TEST_F(EnumDecoratorTest, ReverseIterator)
// {
//   EXPECT_TRUE(std::equal(enumReference.rbegin(), 
//                          enumReference.rend(), 
//                          DecoratedColor::rvbegin()));
// 
//   EXPECT_TRUE(std::equal(DecoratedColor::rvbegin(), 
//                          DecoratedColor::rvend(), 
//                          enumReference.rbegin()));
// 
//   EXPECT_TRUE(std::equal(enumReference.rbegin(),
//                          enumReference.rend(),
//                          enum_extend::enum_value_range<DecoratedColor>().rbegin()));
// 
//   EXPECT_TRUE(std::equal(enum_extend::enum_value_range<DecoratedColor>().rbegin(),
//                          enum_extend::enum_value_range<DecoratedColor>().rend(),
//                          enumReference.rbegin()));
// 
//   EXPECT_TRUE(std::equal(decoReference.rbegin(), 
//                          decoReference.rend(), 
//                          DecoratedColor::rdbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(DecoratedColor::rdbegin(), 
//                          DecoratedColor::rdend(), 
//                          decoReference.rbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(decoReference.rbegin(),
//                          decoReference.rend(),
//                          enum_extend::enum_decoration_range<DecoratedColor>().rbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(enum_extend::enum_decoration_range<DecoratedColor>().rbegin(),
//                          enum_extend::enum_decoration_range<DecoratedColor>().rend(),
//                          decoReference.rbegin(), 
//                          EqualStr()));
// }
// 
// 
// TEST_F(EnumDecoratorTest, PlusPlusOperator)
// {
//   Color2 c = Color2::Black;
//   EXPECT_EQ(Color2::Red, ++c);
//   EXPECT_EQ(Color2::Green, ++c);
//   EXPECT_EQ(Color2::Blue, ++c);
//   EXPECT_EQ(Color2::White, ++c);
//   EXPECT_THROW(++c, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, OperatorPlusPlus)
// {
//   Color2 c = Color2::Black;
//   EXPECT_EQ(Color2::Black, c++);
//   EXPECT_EQ(Color2::Red, c++);
//   EXPECT_EQ(Color2::Green, c++);
//   EXPECT_EQ(Color2::Blue, c++);
//   EXPECT_EQ(Color2::White, c);
//   EXPECT_THROW(c++, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, MinusMinusOperator)
// {
//   Color2 c = Color2::White;
//   EXPECT_EQ(Color2::Blue, --c);
//   EXPECT_EQ(Color2::Green, --c);
//   EXPECT_EQ(Color2::Red, --c);
//   EXPECT_EQ(Color2::Black, --c);
// 
//   EXPECT_THROW(--c, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, OperatorMinusMinus)
// {
//   Color2 c = Color2::White;
//   EXPECT_EQ(Color2::White, c--);
//   EXPECT_EQ(Color2::Blue, c--);
//   EXPECT_EQ(Color2::Green, c--);
//   EXPECT_EQ(Color2::Red, c--);
//   EXPECT_EQ(Color2::Black, c);
// 
//   EXPECT_THROW(c--, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, ToDecoration)
// {
//   EXPECT_STREQ("Black", DecoratedColor::to_decoration(Color2::Black));
//   EXPECT_STREQ("Red", DecoratedColor::to_decoration(Color2::Red));
//   EXPECT_STREQ("Green", DecoratedColor::to_decoration(Color2::Green));
//   EXPECT_STREQ("Blue", DecoratedColor::to_decoration(Color2::Blue));
//   EXPECT_STREQ("White", DecoratedColor::to_decoration(Color2::White));
// 
//   EXPECT_THROW(DecoratedColor::to_decoration((Color2)-1), std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, To num)
// {
//   EXPECT_EQ(Color2::Black, DecoratedColor::to_enum("Black"));
//   EXPECT_EQ(Color2::Red, DecoratedColor::to_enum("Red"));
//   EXPECT_EQ(Color2::Green, DecoratedColor::to_enum("Green"));
//   EXPECT_EQ(Color2::Blue, DecoratedColor::to_enum("Blue"));
//   EXPECT_EQ(Color2::White, DecoratedColor::to_enum("White"));
// 
//   EXPECT_THROW(DecoratedColor::to_enum("42"), std::exception);
// }
// 
// 
// #define GRAY_VALUES_SPECS (GrayValues, (Black, 0x1)(DarkGray, 0x2)(MidGray, 0x4)(LightGray, 0x8))
// 
// ENUM_LIB_DECLARE_EXPLICIT_ENUM(GRAY_VALUES_SPECS)
// 
// #define DECORATED_GRAY_VALUES_SPECS (GrayValuesDeco,                          \
//   (Black, 0x1, "Black")(DarkGray, 0x2, "DarkGray")(MidGray, 0x4, "MidGray")\
//   (LightGray, 0x8, "LightGray")) \
// 
// 
// ENUM_LIB_DECLARE_EXPLICIT_DECORATED_ENUM(DECORATED_GRAY_VALUES_SPECS)
