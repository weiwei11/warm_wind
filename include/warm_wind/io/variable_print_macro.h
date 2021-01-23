//
// Created by ww on 2020/12/5.
//

#ifndef COMMON_UTILS_VARIABLE_PRINT_MACRO_H
#define COMMON_UTILS_VARIABLE_PRINT_MACRO_H

#include "terminal_color_macro.h"
#include <iostream>

#define PRINT_VARIABLE_FLAG
#ifdef PRINT_VARIABLE_FLAG

#define PRINT_VARIABLE_WITH_NAME(var) std::cout << (#var) << "(" << __FUNCTION__ << "-" << __LINE__ << ")" << ": " << (var) << std::endl;
#define PRINT_VARIABLE(var) PRINT_VARIABLE_WITH_NAME(var)
#define PRINT_VARIABLE_WITH_COLOR(var, color_name) \
            SET_TERMINAL_COLOR(color_name) \
            PRINT_VARIABLE(var) \
            RESET_TERMINAL_COLOR()

#else

#define PRINT_VARIABLE_WITH_NAME(var)
#define PRINT_VARIABLE(var) PRINT_VARIABLE_WITH_NAME(var)
#define PRINT_VARIABLE_WITH_COLOR(var, color_name)

#endif

#endif //COMMON_UTILS_VARIABLE_PRINT_MACRO_H
