//
// Created by ww on 2020/12/7.
//

#include <gtest/gtest.h>
#include "warm_wind/io/terminal_color_macro.h"
#include "warm_wind/io/variable_print_macro.h"

class TerminalPrintTests : public testing::Test {

};

TEST_F(TerminalPrintTests, PrintVariable) {
    std::string black = "black", red = "red", green = "green", yellow = "yellow", blue = "blue", magenta = "magenta",
        cyan = "cyan", white = "white";
    PRINT_VARIABLE_WITH_COLOR(black, WW_TC_BLACK)
    PRINT_VARIABLE_WITH_COLOR(red, WW_TC_RED)
    PRINT_VARIABLE_WITH_COLOR(green, WW_TC_GREEN)
    PRINT_VARIABLE_WITH_COLOR(yellow, WW_TC_YELLOW)
    PRINT_VARIABLE_WITH_COLOR(blue, WW_TC_BLUE)
    PRINT_VARIABLE_WITH_COLOR(magenta, WW_TC_MAGENTA)
    PRINT_VARIABLE_WITH_COLOR(cyan, WW_TC_CYAN)
    PRINT_VARIABLE_WITH_COLOR(white, WW_TC_WHITE)
    PRINT_VARIABLE_WITH_COLOR(black, WW_TC_BOLD_BLACK)
    PRINT_VARIABLE_WITH_COLOR(red, WW_TC_BOLD_RED)
    PRINT_VARIABLE_WITH_COLOR(green, WW_TC_BOLD_GREEN)
    PRINT_VARIABLE_WITH_COLOR(yellow, WW_TC_BOLD_YELLOW)
    PRINT_VARIABLE_WITH_COLOR(blue, WW_TC_BOLD_BLUE)
    PRINT_VARIABLE_WITH_COLOR(magenta, WW_TC_BOLD_MAGENTA)
    PRINT_VARIABLE_WITH_COLOR(cyan, WW_TC_BOLD_CYAN)
    PRINT_VARIABLE_WITH_COLOR(white, WW_TC_BOLD_WHITE)
}