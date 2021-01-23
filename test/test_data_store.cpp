//
// Created by ww on 2020/12/15.
//

#include <gtest/gtest.h>
#include "warm_wind/common_header.h"
#include "warm_wind/io/data_store.h"

class DataStoreTests : public testing::Test {

};

#if (defined(USE_OPENCV) && defined(USE_TORCH))
TEST_F(DataStoreTests, WriteAndReadTensor) {
    std::string test_filename = "/home/ww/Desktop/test.yaml";

    // test write
//    cv::FileStorage fs_write(test_filename, cv::FileStorage::WRITE);
    cv::FileStorage fs_write(test_filename, cv::FileStorage::WRITE | cv::FileStorage::MEMORY);
    if (!fs_write.isOpened())
        exit(-1);
    // test type
    at::Tensor byte_tensor = at::arange(0, 10, at::TensorOptions(torch::kUInt8));
    warm_wind::Write(fs_write, "byte_tensor", byte_tensor);
    at::Tensor char_tensor = at::arange(0, 10, at::TensorOptions(torch::kInt8));
    warm_wind::Write(fs_write, "char_tensor", char_tensor);
    at::Tensor s_tensor = at::arange(0, 10, at::TensorOptions(torch::kInt16));
    warm_wind::Write(fs_write, "s_tensor", s_tensor);
    at::Tensor int_tensor = at::arange(0, 10, at::TensorOptions(torch::kInt32));
    warm_wind::Write(fs_write, "int_tensor", int_tensor);
    at::Tensor float_tensor = at::arange(0, 10, at::TensorOptions(torch::kFloat32));
    warm_wind::Write(fs_write, "float_tensor", float_tensor);
    at::Tensor double_tensor = at::arange(0, 10, at::TensorOptions(torch::kFloat64));
    warm_wind::Write(fs_write, "double_tensor", double_tensor);
    // test dim
    at::Tensor multi_dim_tensor = at::rand({2, 2, 3, 4});
    warm_wind::Write(fs_write, "multi_dim_tensor", multi_dim_tensor);
//    fs_write.release();
    cv::String test_input = fs_write.releaseAndGetString();

    // test read
//    cv::FileStorage fs_read(test_filename, cv::FileStorage::READ);
    cv::FileStorage fs_read(test_input, cv::FileStorage::READ | cv::FileStorage::MEMORY);
    if (!fs_read.isOpened())
        exit(-1);
    at::Tensor new_byte_tensor, new_char_tensor, new_s_tensor, new_int_tensor, new_float_tensor, new_double_tensor;
    at::Tensor new_multi_dim_tensor;
    warm_wind::Read(fs_read, "byte_tensor", new_byte_tensor);
    warm_wind::Read(fs_read, "char_tensor", new_char_tensor);
    warm_wind::Read(fs_read, "s_tensor", new_s_tensor);
    warm_wind::Read(fs_read, "int_tensor", new_int_tensor);
    warm_wind::Read(fs_read, "float_tensor", new_float_tensor);
    warm_wind::Read(fs_read, "double_tensor", new_double_tensor);
    warm_wind::Read(fs_read, "multi_dim_tensor", new_multi_dim_tensor);
    fs_read.release();

    // compare difference
    EXPECT_EQ(torch::sum(torch::abs(byte_tensor - new_byte_tensor)).item().toByte(), 0);
    EXPECT_EQ(torch::sum(torch::abs(char_tensor - new_char_tensor)).item().toChar(), 0);
    EXPECT_EQ(torch::sum(torch::abs(s_tensor - new_s_tensor)).item().toInt(), 0);
    EXPECT_EQ(torch::sum(torch::abs(int_tensor - new_int_tensor)).item().toInt(), 0);
    EXPECT_EQ(torch::sum(torch::abs(float_tensor - new_float_tensor)).item().toFloat(), 0);
    EXPECT_EQ(torch::sum(torch::abs(double_tensor - new_double_tensor)).item().toDouble(), 0);
    EXPECT_EQ(torch::sum(torch::abs(multi_dim_tensor - new_multi_dim_tensor)).item().toFloat(), 0);
}

#endif // USE_OPENCV and USE_TORCH
