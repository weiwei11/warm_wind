//
// Created by ww on 2020/12/5.
//

#ifndef COMMON_UTILS_TERMINAL_COLOR_MACRO_H
#define COMMON_UTILS_TERMINAL_COLOR_MACRO_H

namespace warm_wind {

#define USE_TERMINAL_COLOR_FLAG
#ifdef USE_TERMINAL_COLOR_FLAG

#define WW_TC_RESET   "\033[0m"
#define WW_TC_BLACK   "\033[30m"      /* Black */
#define WW_TC_RED     "\033[31m"      /* Red */
#define WW_TC_GREEN   "\033[32m"      /* Green */
#define WW_TC_YELLOW  "\033[33m"      /* Yellow */
#define WW_TC_BLUE    "\033[34m"      /* Blue */
#define WW_TC_MAGENTA "\033[35m"      /* Magenta */
#define WW_TC_CYAN    "\033[36m"      /* Cyan */
#define WW_TC_WHITE   "\033[37m"      /* White */
#define WW_TC_BOLD_BLACK   "\033[1m\033[30m"      /* Bold Black */
#define WW_TC_BOLD_RED     "\033[1m\033[31m"      /* Bold Red */
#define WW_TC_BOLD_GREEN   "\033[1m\033[32m"      /* Bold Green */
#define WW_TC_BOLD_YELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define WW_TC_BOLD_BLUE    "\033[1m\033[34m"      /* Bold Blue */
#define WW_TC_BOLD_MAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define WW_TC_BOLD_CYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define WW_TC_BOLD_WHITE   "\033[1m\033[37m"      /* Bold White */

#else

#define WW_TC_RESET ""
#define WW_TC_BLACK ""
#define WW_TC_RED ""
#define WW_TC_GREEN ""
#define WW_TC_YELLOW ""
#define WW_TC_BLUE ""
#define WW_TC_MAGENTA ""
#define WW_TC_CYAN ""
#define WW_TC_WHITE ""
#define WW_TC_BOLD_BLACK ""
#define WW_TC_BOLD_RED ""
#define WW_TC_BOLD_GREEN ""
#define WW_TC_BOLD_YELLOW ""
#define WW_TC_BOLD_BLUE ""
#define WW_TC_BOLD_MAGENTA ""
#define WW_TC_BOLD_CYAN ""
#define WW_TC_BOLD_WHITE ""

#endif

#define SET_TERMINAL_COLOR(color) std::cout << color;
#define RESET_TERMINAL_COLOR() std::cout << WW_TC_RESET;

//enum class tc : uint8_t {
//    reset = 0,
//};

} // warm_wind

#endif //COMMON_UTILS_TERMINAL_COLOR_MACRO_H
