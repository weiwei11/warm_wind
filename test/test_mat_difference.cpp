//
// Created by ww on 2020/12/21.
//

#include <gtest/gtest.h>
#include "warm_wind/difference/mat_difference.h"

class MatDifferenceTests : public testing::Test {

};

TEST_F(MatDifferenceTests, DifferenceAbs) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_TRUE(warm_wind::DifferenceAbs(a, b).at<float>(0, 0) == 0);
    EXPECT_TRUE(warm_wind::DifferenceAbs(a, c).at<float>(0, 0) == 0.5);
}

TEST_F(MatDifferenceTests, DifferenceSum) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_TRUE(warm_wind::DifferenceSum(a, b)[0] == 0);
    EXPECT_TRUE(warm_wind::DifferenceSum(a, c)[0] == 0.5);
}

TEST_F(MatDifferenceTests, DifferenceSumEqual) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_TRUE(warm_wind::DifferenceSumEqual(a, b, 0.0));
    EXPECT_TRUE(warm_wind::DifferenceSumEqual(a, c, 0.5));
}

TEST_F(MatDifferenceTests, DifferenceSumLess) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_FALSE(warm_wind::DifferenceSumLess(a, b, 0));
    EXPECT_TRUE(warm_wind::DifferenceSumLess(a, b, 0.1));
    EXPECT_FALSE(warm_wind::DifferenceSumLess(a, c, 0));
    EXPECT_FALSE(warm_wind::DifferenceSumLess(a, c, 0.5));
    EXPECT_TRUE(warm_wind::DifferenceSumLess(a, c, 0.51));
}

TEST_F(MatDifferenceTests, DifferenceCount) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(warm_wind::DifferenceCount(a, b)[0], 0);
    EXPECT_EQ(warm_wind::DifferenceCount(a, c)[0], 1);
}

TEST_F(MatDifferenceTests, DifferenceCountEqual) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_TRUE(warm_wind::DifferenceCountEqual(a, b, 0));
    EXPECT_FALSE(warm_wind::DifferenceCountEqual(a, b, 0.1));
    EXPECT_FALSE(warm_wind::DifferenceCountEqual(a, c, 0));
    EXPECT_TRUE(warm_wind::DifferenceCountEqual(a, c, 1));
    EXPECT_FALSE(warm_wind::DifferenceCountEqual(a, c, 2));
}

TEST_F(MatDifferenceTests, DifferenceCountLess) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_FALSE(warm_wind::DifferenceCountLess(a, b, 0));
    EXPECT_TRUE(warm_wind::DifferenceCountLess(a, b, 0.1));
    EXPECT_FALSE(warm_wind::DifferenceCountLess(a, c, 0));
    EXPECT_FALSE(warm_wind::DifferenceCountLess(a, c, 1));
    EXPECT_TRUE(warm_wind::DifferenceCountLess(a, c, 2));
}

TEST_F(MatDifferenceTests, RelativeDifferenceCount) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat d = (cv::Mat_<float>(3, 3) << 1+1e-10, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_EQ(warm_wind::RelativeDifferenceCount(a, b)[0], 0);
    EXPECT_EQ(warm_wind::RelativeDifferenceCount(a, c)[0], 1);
    EXPECT_EQ(warm_wind::RelativeDifferenceCount(a, d)[0], 0);
}

TEST_F(MatDifferenceTests, RelativeDifferenceCountEqual) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat d = (cv::Mat_<float>(3, 3) << 1+1e-10, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_TRUE(warm_wind::RelativeDifferenceCountEqual(a, b, 0));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, b, 0.1));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, c, 0));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountEqual(a, c, 1));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, c, 2));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountEqual(a, d, 0));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, d, 1));
}

TEST_F(MatDifferenceTests, RelativeDifferenceCountLess) {
    cv::Mat a = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat c = (cv::Mat_<float>(3, 3) << 1.5, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat d = (cv::Mat_<float>(3, 3) << 1+1e-10, 2, 3, 4, 5, 6, 7, 8, 9);

    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, b, 0));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountLess(a, b, 0.1));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, c, 0));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, c, 1));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountLess(a, c, 2));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, d, 0));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountLess(a, d, 1));
}