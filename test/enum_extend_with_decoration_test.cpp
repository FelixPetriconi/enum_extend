///////////////////////////////////////////////////////////////////
//
// Copyright 2015 Felix Petriconi
//
// License: http://boost.org/LICENSE_1_0.txt, Boost License 1.0
//
// Authors: http://petriconi.net, Felix Petriconi
//
//////////////////////////////////////////////////////////////////

#include "enum_extend/enum_extender.hpp"
#include "enum_extend/enum_range.hpp"
#include "enum_extend/enum_value_range.hpp"
#include "enum_extend/enum_decoration_range.hpp"

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

enum_extend::extender<Gray, ccharp>::instances enum_extend::extender<Gray, ccharp>::s_instances;
enum_extend::extender<Gray, ccharp> GrayExtender({ { Gray::DarkGray, DarkGrayC }, 
                                                    { Gray::MidGray, MidGrayC }, 
                                                    { Gray::LightGray, LightGrayC } });

using DecoratedGray = std::pair<Gray, ccharp>;
DecoratedGray& operator++(DecoratedGray& e);
DecoratedGray& operator--(DecoratedGray& e);
DecoratedGray operator++(DecoratedGray& e, int);
DecoratedGray operator--(DecoratedGray& e, int);


DecoratedGray& operator++(DecoratedGray& e) { return enum_extend::extender<Gray, ccharp>::increment(e); }
DecoratedGray& operator--(DecoratedGray& e) { return enum_extend::extender<Gray, ccharp>::decrement(e); }
DecoratedGray operator++(DecoratedGray& e, int) {
    auto tmp = e;                                                            
    enum_extend::extender<Gray, ccharp>::increment(e);
    return tmp;                                                              
  }          

DecoratedGray operator--(DecoratedGray& e, int) {
    auto tmp = e;                                                            
    enum_extend::extender<Gray, ccharp>::decrement(e);
    return tmp;                                                              
  }                                                                          





class EnumExtendWitDecorationTest : public ::testing::Test
{
public:
  EnumExtendWitDecorationTest()
    : reference({ { Gray::DarkGray, DarkGrayC }, { Gray::MidGray, MidGrayC }, { Gray::LightGray, LightGrayC } })
  {}

  std::vector<std::pair<Gray, ccharp>> reference;
};


TEST_F(EnumExtendWitDecorationTest, Size)
{
  EXPECT_EQ(3, (enum_extend::extender<Gray, ccharp>::size()));
}

TEST_F(EnumExtendWitDecorationTest, Range)
{
  size_t i = 0;
  for (auto c : enum_extend::enum_range<Gray, ccharp>())
  {
    EXPECT_EQ(reference[i], c);
    ++i;
  }
}

TEST_F(EnumExtendWitDecorationTest, ValueRange)
{
  size_t i = 0;
  for (auto c : enum_extend::enum_value_range<Gray, ccharp>())
  {
    EXPECT_EQ(reference[i].first, c);
    ++i;
  }
}


TEST_F(EnumExtendWitDecorationTest, DecorationRange)
{
  size_t i = 0;
  for (auto c : enum_extend::enum_decoration_range<Gray, ccharp>())
  {
    EXPECT_EQ(reference[i].second, c);
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
  auto c = std::make_pair(Gray::DarkGray, DarkGrayC);
  EXPECT_EQ(std::make_pair(Gray::MidGray, MidGrayC), ++c);
  EXPECT_EQ(std::make_pair(Gray::LightGray, LightGrayC), ++c);
  EXPECT_THROW(++c, std::exception);
}

TEST_F(EnumExtendWitDecorationTest, OperatorPlusPlus)
{
  auto c = std::make_pair(Gray::DarkGray, DarkGrayC);
  EXPECT_EQ(std::make_pair(Gray::DarkGray, DarkGrayC), c++);
  EXPECT_EQ(std::make_pair(Gray::MidGray, MidGrayC), c++);
  EXPECT_EQ(std::make_pair(Gray::LightGray, LightGrayC), c);
  EXPECT_THROW(c++, std::exception);
}


TEST_F(EnumExtendWitDecorationTest, MinusMinusOperator)
{
  auto c = std::make_pair(Gray::LightGray, LightGrayC);
  EXPECT_EQ(std::make_pair(Gray::MidGray, MidGrayC), --c);
  EXPECT_EQ(std::make_pair(Gray::DarkGray, DarkGrayC), --c);
  
  EXPECT_THROW(--c, std::exception);
}

TEST_F(EnumExtendWitDecorationTest, OperatorMinusMinus)
{
  auto c = std::make_pair(Gray::LightGray, LightGrayC);
  EXPECT_EQ(std::make_pair(Gray::LightGray, LightGrayC), c--);
  EXPECT_EQ(std::make_pair(Gray::MidGray, MidGrayC), c--);
  EXPECT_EQ(std::make_pair(Gray::DarkGray, DarkGrayC), c);
  
  EXPECT_THROW(c--, std::exception);
}


// 
// 
// #define Gray_DECORATOR_SPECIIFIERS (DecoratedGray, Gray2, const char*, \
//                                     (Black, "Black")\
//                                     (DarkGray, "DarkGray")\
//                                     (MidGray, "MidGray")\
//                                     (LightGray, "LightGray")\
//                                     (White, "White")) \
// 
// 
// ENUM_LIB_DECLARE_ENUM_DECORATOR(Gray_DECORATOR_SPECIIFIERS)
// 
// ENUM_LIB_DEFINE_ENUM_DECORATOR(Gray_DECORATOR_SPECIIFIERS)
// 
// 
// class EnumDecoratorTest : public ::testing::Test
// {
// public:
//   EnumDecoratorTest()
//     : enumReference({ Gray2::Black, Gray2::DarkGray, Gray2::MidGray, Gray2::LightGray, Gray2::White })
//     , decoReference({"Black", "DarkGray", "MidGray", "LightGray", "White"})
//   {
// 
//   }
//   std::vector<Gray2> enumReference;
//   std::vector<const char*> decoReference;
// 
// };
// 
// TEST_F(EnumDecoratorTest, Size)
// {
//   EXPECT_EQ(5, DecoratedGray::size());
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
//                          DecoratedGray::vbegin()));
//   
//   EXPECT_TRUE(std::equal(DecoratedGray::vbegin(), 
//                          DecoratedGray::vend(), 
//                          enumReference.begin()));
// 
//   EXPECT_TRUE(std::equal(enumReference.begin(), 
//                          enumReference.end(), 
//                          std::begin(enum_extend::enum_value_range<DecoratedGray>())));
// 
//   EXPECT_TRUE(std::equal(std::begin(enum_extend::enum_value_range<DecoratedGray>()), 
//                          std::end(enum_extend::enum_value_range<DecoratedGray>()), 
//                          enumReference.begin()));
// 
// 
//   EXPECT_TRUE(std::equal(decoReference.begin(), 
//                          decoReference.end(), 
//                          DecoratedGray::dbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(DecoratedGray::dbegin(), 
//                          DecoratedGray::dend(), 
//                          decoReference.begin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(decoReference.begin(), 
//                          decoReference.end(), 
//                          std::begin(enum_extend::enum_decoration_range<DecoratedGray>()), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(std::begin(enum_extend::enum_decoration_range<DecoratedGray>()),
//                          std::end(enum_extend::enum_decoration_range<DecoratedGray>()), 
//                          decoReference.begin(), 
//                          EqualStr()));
// }
// 
// TEST_F(EnumDecoratorTest, ReverseIterator)
// {
//   EXPECT_TRUE(std::equal(enumReference.rbegin(), 
//                          enumReference.rend(), 
//                          DecoratedGray::rvbegin()));
// 
//   EXPECT_TRUE(std::equal(DecoratedGray::rvbegin(), 
//                          DecoratedGray::rvend(), 
//                          enumReference.rbegin()));
// 
//   EXPECT_TRUE(std::equal(enumReference.rbegin(),
//                          enumReference.rend(),
//                          enum_extend::enum_value_range<DecoratedGray>().rbegin()));
// 
//   EXPECT_TRUE(std::equal(enum_extend::enum_value_range<DecoratedGray>().rbegin(),
//                          enum_extend::enum_value_range<DecoratedGray>().rend(),
//                          enumReference.rbegin()));
// 
//   EXPECT_TRUE(std::equal(decoReference.rbegin(), 
//                          decoReference.rend(), 
//                          DecoratedGray::rdbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(DecoratedGray::rdbegin(), 
//                          DecoratedGray::rdend(), 
//                          decoReference.rbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(decoReference.rbegin(),
//                          decoReference.rend(),
//                          enum_extend::enum_decoration_range<DecoratedGray>().rbegin(), 
//                          EqualStr()));
// 
//   EXPECT_TRUE(std::equal(enum_extend::enum_decoration_range<DecoratedGray>().rbegin(),
//                          enum_extend::enum_decoration_range<DecoratedGray>().rend(),
//                          decoReference.rbegin(), 
//                          EqualStr()));
// }
// 
// 
// TEST_F(EnumDecoratorTest, PlusPlusOperator)
// {
//   Gray2 c = Gray2::Black;
//   EXPECT_EQ(Gray2::DarkGray, ++c);
//   EXPECT_EQ(Gray2::MidGray, ++c);
//   EXPECT_EQ(Gray2::LightGray, ++c);
//   EXPECT_EQ(Gray2::White, ++c);
//   EXPECT_THROW(++c, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, OperatorPlusPlus)
// {
//   Gray2 c = Gray2::Black;
//   EXPECT_EQ(Gray2::Black, c++);
//   EXPECT_EQ(Gray2::DarkGray, c++);
//   EXPECT_EQ(Gray2::MidGray, c++);
//   EXPECT_EQ(Gray2::LightGray, c++);
//   EXPECT_EQ(Gray2::White, c);
//   EXPECT_THROW(c++, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, MinusMinusOperator)
// {
//   Gray2 c = Gray2::White;
//   EXPECT_EQ(Gray2::LightGray, --c);
//   EXPECT_EQ(Gray2::MidGray, --c);
//   EXPECT_EQ(Gray2::DarkGray, --c);
//   EXPECT_EQ(Gray2::Black, --c);
// 
//   EXPECT_THROW(--c, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, OperatorMinusMinus)
// {
//   Gray2 c = Gray2::White;
//   EXPECT_EQ(Gray2::White, c--);
//   EXPECT_EQ(Gray2::LightGray, c--);
//   EXPECT_EQ(Gray2::MidGray, c--);
//   EXPECT_EQ(Gray2::DarkGray, c--);
//   EXPECT_EQ(Gray2::Black, c);
// 
//   EXPECT_THROW(c--, std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, ToDecoration)
// {
//   EXPECT_STREQ("Black", DecoratedGray::to_decoration(Gray2::Black));
//   EXPECT_STREQ("DarkGray", DecoratedGray::to_decoration(Gray2::DarkGray));
//   EXPECT_STREQ("MidGray", DecoratedGray::to_decoration(Gray2::MidGray));
//   EXPECT_STREQ("LightGray", DecoratedGray::to_decoration(Gray2::LightGray));
//   EXPECT_STREQ("White", DecoratedGray::to_decoration(Gray2::White));
// 
//   EXPECT_THROW(DecoratedGray::to_decoration((Gray2)-1), std::exception);
// }
// 
// TEST_F(EnumDecoratorTest, To num)
// {
//   EXPECT_EQ(Gray2::Black, DecoratedGray::to_enum("Black"));
//   EXPECT_EQ(Gray2::DarkGray, DecoratedGray::to_enum("DarkGray"));
//   EXPECT_EQ(Gray2::MidGray, DecoratedGray::to_enum("MidGray"));
//   EXPECT_EQ(Gray2::LightGray, DecoratedGray::to_enum("LightGray"));
//   EXPECT_EQ(Gray2::White, DecoratedGray::to_enum("White"));
// 
//   EXPECT_THROW(DecoratedGray::to_enum("42"), std::exception);
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
