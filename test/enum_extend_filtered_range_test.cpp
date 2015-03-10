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
#include "enum_extend/filtered_range.hpp"

#include <gtest/gtest.h>
#include <vector>

enum Flags
{
  F0x00 = 0,
  F0x01 = 1,
  F0x02 = 2,
  F0x03 = F0x01 | F0x02,
  F0x04 = 4,
  F0x07 = F0x03 | F0x04,
  F0x08 = 8
};

enum_extend::extender<Flags>::instances enum_extend::extender<Flags>::s_instances;
enum_extend::extender<Flags>  ColorExtender(Flags::F0x00, Flags::F0x01, Flags::F0x02, Flags::F0x03, Flags::F0x04, Flags::F0x07, Flags::F0x08);


class EnumExtenderFilterRangeTest : public ::testing::Test
{
public:
};


TEST_F(EnumExtenderFilterRangeTest, Size)
{
  EXPECT_EQ(7, (enum_extend::extender<Flags>::size()));
}

struct Matcher
{
  using reult_type = bool;
  bool operator()(Flags x, Flags y) const
  {
    EXPECT_EQ(x, y); 
    return x == y;
  };
};

TEST_F(EnumExtenderFilterRangeTest, FilteredRangeWithSingleResults)
{
  auto Only_F0x02 = [](Flags f)
  {
    return f == Flags::F0x02;
  };
  std::vector<Flags> expectedResult = { Flags::F0x02 };

  auto range = enum_extend::filtered_range<Flags>(Only_F0x02);

  EXPECT_TRUE(std::equal(range.begin(), range.end(), expectedResult.begin(), Matcher()));
}


TEST_F(EnumExtenderFilterRangeTest, FilteredRangeWithMultipleResults)
{
  auto With_F0x02 = [](Flags f)
  {
    return (f & Flags::F0x02) != 0;
  };
  std::vector<Flags> expectedResult = { Flags::F0x02, Flags::F0x03, Flags::F0x07 };

  auto range = enum_extend::filtered_range<Flags>(With_F0x02);
  EXPECT_TRUE(std::equal(range.begin(), range.end(), expectedResult.begin(), Matcher()));
}


TEST_F(EnumExtenderFilterRangeTest, FilteredRangeWithNoResults)
{
  auto EmptyFilter = [](Flags)
  {
    return false;;
  };

  auto range = enum_extend::filtered_range<Flags>(EmptyFilter);
  EXPECT_EQ(range.begin(), range.end());
}
