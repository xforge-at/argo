#import "util.hpp"
#import <gmock/gmock.h>
#import <gtest/gtest.h>

TEST(UtilTest, MakeNotNullShouldAddNotNullAnnotation) {
    auto x = 5;
    auto xPtr = make_not_null(&x);

    ASSERT_EQ(x, *xPtr) << "X and the not null pointer should be equal";
}
