//
// Created by ww on 2020/11/29.
//

#ifndef COMMON_UTILS_TIME_RECORDER_MACRO_H
#define COMMON_UTILS_TIME_RECORDER_MACRO_H

#include <chrono>
#include <utility>
//#include <vector>
#include <string>
#include <stack>

struct RunTimeRecord {
    std::string name_;
    std::chrono::steady_clock::time_point start_time_;
    std::chrono::steady_clock::time_point end_time_;
    int begin_line_ = 0;
    int end_line_ = 0;

    RunTimeRecord(std::string name, std::chrono::steady_clock::time_point start_time,
                  std::chrono::steady_clock::time_point end_time, int begin_line, int end_line)
            : name_(std::move(name)), start_time_(start_time), end_time_(end_time), begin_line_(begin_line), end_line_(end_line)
    {}

    RunTimeRecord(std::chrono::steady_clock::time_point start_time, int begin_line) : start_time_(start_time), begin_line_(begin_line)
    {}
};

struct RunTimeRecordStack {
//    std::stack<std::string> name_stack;
    std::stack<std::chrono::steady_clock::time_point> start_time_stack;
    std::stack<std::chrono::steady_clock::time_point> end_time_stack;
    std::stack<int> begin_line_stack;
    std::stack<int> end_line_stack;
};

#define SHOW_RUN_TIME_FLAG
#ifdef SHOW_RUN_TIME_FLAG
//std::chrono::steady_clock::time_point time_record_start, time_record_end;
static RunTimeRecordStack global_run_time_record_stack;
#define START_TIME_RECORD() \
            global_run_time_record_stack.start_time_stack.push(std::chrono::steady_clock::now()); \
            global_run_time_record_stack.begin_line_stack.push(__LINE__);

#define END_TIME_RECORD(name) \
            for (size_t global_run_time_record_i = global_run_time_record_stack.start_time_stack.size() - 1; global_run_time_record_i > 0; --global_run_time_record_i) std::cout << "  "; \
            std::cout << (name) << "(" << global_run_time_record_stack.begin_line_stack.top() << "-" << (__LINE__) << "): " << \
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - global_run_time_record_stack.start_time_stack.top()).count() / 1000.0 \
            << " ms" << std::endl; \
            global_run_time_record_stack.start_time_stack.pop(); \
            global_run_time_record_stack.begin_line_stack.pop();

#define WITH_PRINT_RUN_TIME(name, code_block...) \
            START_TIME_RECORD() \
            code_block; \
            END_TIME_RECORD(name)
#else
#define START_TIME_RECORD()
#define END_TIME_RECORD()
#define WITH_PRINT_RUN_TIME(name, code_block) code_block;
#endif

#endif //COMMON_UTILS_TIME_RECORDER_MACRO_H
