//
// Created by ww on 2020/12/15.
//


#include <gtest/gtest.h>
#include "warm_wind/io/variable_print_macro.h"

#include "warm_wind/types/type.h"

class TypeTests : public testing::Test {

};

#ifdef USE_TORCH
TEST_F(TypeTests, ScalarType2CodeChar) {
//    PRINT_VARIABLE(warm_wind::ScalarType2CodeChar(torch::kUInt8))
//    PRINT_VARIABLE(warm_wind::ScalarType2CodeChar(torch::kInt8))
//    PRINT_VARIABLE(warm_wind::ScalarType2CodeChar(torch::kInt16))
//    PRINT_VARIABLE(warm_wind::ScalarType2CodeChar(torch::kInt32))
//    PRINT_VARIABLE(warm_wind::ScalarType2CodeChar(torch::kFloat32))
//    PRINT_VARIABLE(warm_wind::ScalarType2CodeChar(torch::kFloat64))
    EXPECT_EQ(warm_wind::ScalarType2CodeChar(torch::kUInt8), 'u');
    EXPECT_EQ(warm_wind::ScalarType2CodeChar(torch::kInt8), 'c');
    EXPECT_EQ(warm_wind::ScalarType2CodeChar(torch::kInt16), 's');
    EXPECT_EQ(warm_wind::ScalarType2CodeChar(torch::kInt32), 'i');
    EXPECT_EQ(warm_wind::ScalarType2CodeChar(torch::kFloat32), 'f');
    EXPECT_EQ(warm_wind::ScalarType2CodeChar(torch::kFloat64), 'd');

}

TEST_F(TypeTests, CodeChar2ScalarType) {
//    PRINT_VARIABLE(warm_wind::CodeChar2ScalarType('u'))
//    PRINT_VARIABLE(warm_wind::CodeChar2ScalarType('c'))
//    PRINT_VARIABLE(warm_wind::CodeChar2ScalarType('s'))
//    PRINT_VARIABLE(warm_wind::CodeChar2ScalarType('i'))
//    PRINT_VARIABLE(warm_wind::CodeChar2ScalarType('f'))
//    PRINT_VARIABLE(warm_wind::CodeChar2ScalarType('d'))
    EXPECT_EQ(warm_wind::CodeChar2ScalarType('u'), torch::kUInt8);
    EXPECT_EQ(warm_wind::CodeChar2ScalarType('c'), torch::kInt8);
    EXPECT_EQ(warm_wind::CodeChar2ScalarType('s'), torch::kInt16);
    EXPECT_EQ(warm_wind::CodeChar2ScalarType('i'), torch::kInt32);
    EXPECT_EQ(warm_wind::CodeChar2ScalarType('f'), torch::kFloat32);
    EXPECT_EQ(warm_wind::CodeChar2ScalarType('d'), torch::kFloat64);
}
#endif // USE_TORCH