//
// Created by ww on 2020/12/22.
//

#include <gtest/gtest.h>
#include "warm_wind/cv/image_process.h"
#include "warm_wind/difference/mat_difference.h"

class ImageProcessTests : public testing::Test {

};

TEST_F(ImageProcessTests, ComputeChannelsMean) {
    cv::Mat r_channel = (cv::Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
    cv::Mat g_channel = (cv::Mat_<uchar>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cv::Mat b_channel = (cv::Mat_<uchar>(3, 3) << 255, 255, 255, 255, 255, 255, 255, 255, 255);
    cv::Mat image_cpu;
    std::vector<cv::Mat> channels = {r_channel, g_channel, b_channel};
    cv::merge(channels, image_cpu);
    cv::cuda::GpuMat image_gpu;
    image_gpu.upload(image_cpu);

    EXPECT_EQ(warm_wind::ComputeChannelsMean(image_gpu), cv::Scalar(1, 0, 255));
}

TEST_F(ImageProcessTests, ToThreeChannels) {
    cv::Mat r_channel = (cv::Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
    cv::Mat g_channel = (cv::Mat_<uchar>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cv::Mat b_channel = (cv::Mat_<uchar>(3, 3) << 255, 255, 255, 255, 255, 255, 255, 255, 255);
    cv::Mat a_channel = (cv::Mat_<uchar>(3, 3) << 2, 2, 2, 2, 2, 2, 2, 2, 2);
    cv::Mat image_cpu;
    cv::cuda::GpuMat image_gpu;
    std::vector<cv::Mat> rgb_channels = {r_channel, g_channel, b_channel};
    std::vector<cv::Mat> rgba_channels = {r_channel, g_channel, b_channel, a_channel};
    // gray image
    cv::merge(r_channel, image_cpu);
    image_gpu.upload(image_cpu);
    warm_wind::ToThreeChannels(image_gpu, image_gpu);
    EXPECT_EQ(warm_wind::ComputeChannelsMean(image_gpu), cv::Scalar(1, 1, 1));
    // rgb image
    cv::merge(rgb_channels, image_cpu);
    image_gpu.upload(image_cpu);
    warm_wind::ToThreeChannels(image_gpu, image_gpu);
    EXPECT_EQ(warm_wind::ComputeChannelsMean(image_gpu), cv::Scalar(1, 0, 255));
    // rgba image
    cv::merge(rgba_channels, image_cpu);
    image_gpu.upload(image_cpu);
    warm_wind::ToThreeChannels(image_gpu, image_gpu);
    EXPECT_EQ(warm_wind::ComputeChannelsMean(image_gpu), cv::Scalar(1, 0, 255));
}

TEST_F(ImageProcessTests, ComputePadSizes) {
    // aspect ratio < 1
    EXPECT_EQ(warm_wind::ComputePadSizes(100, 100, 3.0/4.0), cv::Scalar_<int>(0, 17));
    EXPECT_EQ(warm_wind::ComputePadSizes(1080, 1920, 3.0/4.0), cv::Scalar_<int>(180, 0));
    EXPECT_EQ(warm_wind::ComputePadSizes(3, 4, 3.0/4.0), cv::Scalar_<int>(0, 0));
    // aspect ratio = 1
    EXPECT_EQ(warm_wind::ComputePadSizes(100, 100, 1.0/1.0), cv::Scalar_<int>(0, 0));
    EXPECT_EQ(warm_wind::ComputePadSizes(1080, 1920, 1.0/1.0), cv::Scalar_<int>(420, 0));
    EXPECT_EQ(warm_wind::ComputePadSizes(4, 3, 1.0/1.0), cv::Scalar_<int>(0, 0));
    // aspect ratio > 1
    EXPECT_EQ(warm_wind::ComputePadSizes(100, 100, 3.0/2.0), cv::Scalar_<int>(25, 0));
    EXPECT_EQ(warm_wind::ComputePadSizes(1080, 640, 3.0/2.0), cv::Scalar_<int>(0, 40));
    EXPECT_EQ(warm_wind::ComputePadSizes(300, 200, 3.0/2.0), cv::Scalar_<int>(0, 0));
}

TEST_F(ImageProcessTests, AddPad) {
    cv::cuda::GpuMat image(3, 4, CV_8UC1, cv::Scalar(0));
    cv::cuda::GpuMat pad_image;
    cv::Mat pad_image_cpu;
    // add pad (1, 1)
    pad_image = warm_wind::AddPad(image, cv::Scalar_<int>(1, 1), cv::Scalar(255));
    pad_image.download(pad_image_cpu);
    EXPECT_EQ(pad_image_cpu.at<uchar>(0, 0), 255);
    EXPECT_EQ(pad_image_cpu.at<uchar>(3, 4), 0);
    EXPECT_EQ(pad_image_cpu.at<uchar>(4, 5), 255);
    EXPECT_EQ(pad_image_cpu.rows, 5);
    EXPECT_EQ(pad_image_cpu.cols, 6);
    // add pad (0, 0)
    pad_image = warm_wind::AddPad(image, cv::Scalar_<int>(0, 0), cv::Scalar(0));
    pad_image.download(pad_image_cpu);
    EXPECT_EQ(pad_image_cpu.rows, 3);
    EXPECT_EQ(pad_image_cpu.cols, 4);
    // add pad (3, 0)
    pad_image = warm_wind::AddPad(image, cv::Scalar_<int>(3, 0), cv::Scalar(125));
    pad_image.download(pad_image_cpu);
    EXPECT_EQ(pad_image_cpu.rows, 9);
    EXPECT_EQ(pad_image_cpu.cols, 4);
    // add pad (0, 100)
    pad_image = warm_wind::AddPad(image, cv::Scalar_<int>(0, 100), cv::Scalar(100));
    pad_image.download(pad_image_cpu);
    EXPECT_EQ(pad_image_cpu.rows, 3);
    EXPECT_EQ(pad_image_cpu.cols, 204);
}