// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "header.hpp"
TEST(Example, EmptyTest) {
    ++mythreads::currentCount;
    mythreads ths(4);
    ths.startLogging();
    EXPECT_TRUE(true);
}
