//
// Created by ww on 2020/12/24.
//

#include <gtest/gtest.h>
#include "warm_wind/cv/pose.h"
#include "warm_wind/difference/mat_difference.h"

class PoseTests : public testing::Test {

};

TEST_F(PoseTests, ProjectPoints) {
    cv::Mat opoints = (cv::Mat_<float>(2, 3) << 0, 0, 0, 1, 1, 1);
    cv::Mat rt = (cv::Mat_<float>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    cv::Mat camera_intrinsic = (cv::Mat_<float>(3, 3) << 640, 0, 320, 0, 640, 240, 0, 0, 1);
    cv::Mat ipoints = (cv::Mat_<float>(2, 2) << 320, 240, 960, 880);
    EXPECT_TRUE(warm_wind::DifferenceSumEqual(warm_wind::ProjectPoints(opoints, rt, camera_intrinsic), ipoints, 0));
}

TEST_F(PoseTests, SolvePnP) {
    // TODO Test SolvePnP
}

TEST_F(PoseTests, SolvePnPRansac) {
    // TODO Test SolvePnPRansac
}