//
// Created by ww on 2020/12/7.
//

#include <gtest/gtest.h>
#include "warm_wind/time/time_recorder_macro.h"

class TimeRecorderTests : public testing::Test {

};

TEST_F(TimeRecorderTests, WITH_PRINT_RUN_TIME) {
    WITH_PRINT_RUN_TIME("test",
    for (int i = 0; i < 1000; ++i) {

    }
    )
}