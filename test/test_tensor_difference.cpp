//
// Created by ww on 2020/12/21.
//

#include <gtest/gtest.h>
#include "warm_wind/difference/tensor_difference.h"

class TensorDifferenceTests : public testing::Test {

};

TEST_F(TensorDifferenceTests, DifferenceAbs) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_TRUE(warm_wind::DifferenceAbs(a, b)[0][0].item().toFloat() == 0);
    EXPECT_TRUE(warm_wind::DifferenceAbs(a, c)[0][0].item().toFloat() == 0.5);
}

TEST_F(TensorDifferenceTests, DifferenceSum) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_TRUE(warm_wind::DifferenceSum(a, b).item().toFloat() == 0);
    EXPECT_TRUE(warm_wind::DifferenceSum(a, c).item().toFloat() == 0.5);
}

TEST_F(TensorDifferenceTests, DifferenceSumEqual) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_TRUE(warm_wind::DifferenceSumEqual(a, b, 0.0));
    EXPECT_TRUE(warm_wind::DifferenceSumEqual(a, c, 0.5));
}

TEST_F(TensorDifferenceTests, DifferenceSumLess) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_FALSE(warm_wind::DifferenceSumLess(a, b, 0));
    EXPECT_TRUE(warm_wind::DifferenceSumLess(a, b, 0.1));
    EXPECT_FALSE(warm_wind::DifferenceSumLess(a, c, 0));
    EXPECT_FALSE(warm_wind::DifferenceSumLess(a, c, 0.5));
    EXPECT_TRUE(warm_wind::DifferenceSumLess(a, c, 0.51));
}

TEST_F(TensorDifferenceTests, DifferenceCount) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_EQ(warm_wind::DifferenceCount(a, b).item().toFloat(), 0);
    EXPECT_EQ(warm_wind::DifferenceCount(a, c).item().toFloat(), 1);
}

TEST_F(TensorDifferenceTests, DifferenceCountEqual) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_TRUE(warm_wind::DifferenceCountEqual(a, b, 0));
    EXPECT_FALSE(warm_wind::DifferenceCountEqual(a, b, 0.1));
    EXPECT_FALSE(warm_wind::DifferenceCountEqual(a, c, 0));
    EXPECT_TRUE(warm_wind::DifferenceCountEqual(a, c, 1));
    EXPECT_FALSE(warm_wind::DifferenceCountEqual(a, c, 2));
}

TEST_F(TensorDifferenceTests, DifferenceCountLess) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_FALSE(warm_wind::DifferenceCountLess(a, b, 0));
    EXPECT_TRUE(warm_wind::DifferenceCountLess(a, b, 0.1));
    EXPECT_FALSE(warm_wind::DifferenceCountLess(a, c, 0));
    EXPECT_FALSE(warm_wind::DifferenceCountLess(a, c, 1));
    EXPECT_TRUE(warm_wind::DifferenceCountLess(a, c, 2));
}

TEST_F(TensorDifferenceTests, RelativeDifferenceCount) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor d = at::tensor({1+1e-10, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_EQ(warm_wind::RelativeDifferenceCount(a, b).item().toFloat(), 0);
    EXPECT_EQ(warm_wind::RelativeDifferenceCount(a, c).item().toFloat(), 1);
    EXPECT_EQ(warm_wind::RelativeDifferenceCount(a, d).item().toFloat(), 0);
}

TEST_F(TensorDifferenceTests, RelativeDifferenceCountEqual) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor d = at::tensor({1+1e-10, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_TRUE(warm_wind::RelativeDifferenceCountEqual(a, b, 0));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, b, 0.1));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, c, 0));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountEqual(a, c, 1));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, c, 2));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountEqual(a, d, 0));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountEqual(a, d, 1));
}

TEST_F(TensorDifferenceTests, RelativeDifferenceCountLess) {
    at::Tensor a = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor b = at::tensor({1, 2, 3, 4, 5, 6, 7, 8, 9}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor c = at::tensor({1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});
    at::Tensor d = at::tensor({1+1e-10, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, at::TensorOptions(torch::kFloat32)).reshape({3, 3});

    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, b, 0));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountLess(a, b, 0.1));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, c, 0));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, c, 1));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountLess(a, c, 2));
    EXPECT_FALSE(warm_wind::RelativeDifferenceCountLess(a, d, 0));
    EXPECT_TRUE(warm_wind::RelativeDifferenceCountLess(a, d, 1));
}