#include "tset.h"
#include <gtest.h>

int l1 = 100000000;
TBitField X1(l1), Y1(l1);

int l2 = 200000000;
TBitField X2(l2), Y2(l2);

int l3 = 300000000;
TBitField X3(l3), Y3(l3);

int l4 = 400000000;
TBitField X4(l4), Y4(l4);


TEST(TBitFieldTime, with_100_million)
{
  ASSERT_NO_THROW(X1 | Y1);
}

TEST(TBitFieldTime, with_200_million)
{
  ASSERT_NO_THROW(X2 | Y2);
}

TEST(TBitFieldTime, with_300_million)
{
  ASSERT_NO_THROW(X3 | Y3);
}

TEST(TBitFieldTime, with_400_million)
{
  ASSERT_NO_THROW(X4 | Y4);
}