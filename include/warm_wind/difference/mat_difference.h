//
// Created by ww on 2020/12/20.
//

#ifndef COMMON_UTILS_MAT_DIFFERENCE_H
#define COMMON_UTILS_MAT_DIFFERENCE_H

#include "warm_wind/common_header.h"

namespace warm_wind {

/**
 * @brief Compute \f$c = |a - b|\f$
 * @param a
 * @param b
 * @return
 */
inline cv::Mat DifferenceAbs(const cv::Mat& a, const cv::Mat& b) {
    CV_Assert(a.rows == b.rows);
    CV_Assert(a.cols == b.cols);

//    cv::Mat difference;
//    cv::subtract(a, b, difference);
//    cv::Mat difference_abs = cv::abs(difference);
//    return difference_abs;
    cv::Mat difference_abs;
    cv::absdiff(a, b, difference_abs);
    return difference_abs;
}

/**
 * @brief Compute \f$c = \sum|a_i - b_i|\f$
 * @param a
 * @param b
 * @return
 */
inline cv::Scalar DifferenceSum(const cv::Mat& a, const cv::Mat& b) {
    CV_Assert((a.channels() == 1) && (b.channels() == 1));

    cv::Mat difference_abs = warm_wind::DifferenceAbs(a, b);
    cv::Scalar difference_abs_sum = cv::sum(difference_abs);
    return difference_abs_sum;
}

/**
 * @brief Compute \f$c==const_value\f$, and \f$c = \sum|a_i - b_i|\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool DifferenceSumEqual(const cv::Mat& a, const cv::Mat& b, const T const_value) {
    cv::Scalar difference_abs_sum = warm_wind::DifferenceSum(a, b);
    return difference_abs_sum[0] == const_value;
}

/**
 * @brief Compute \f$c<const_value\f$, and \f$c = \sum|a_i - b_i|\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool DifferenceSumLess(const cv::Mat& a, const cv::Mat& b, const T const_value) {
    cv::Scalar difference_abs_sum = warm_wind::DifferenceSum(a, b);
    return difference_abs_sum[0] < const_value;
}

/**
 * @brief Compute \f$c = \sum(|a_i - b_i|>1e-8)\f$
 * @param a
 * @param b
 * @return
 */
inline cv::Scalar DifferenceCount(const cv::Mat& a, const cv::Mat& b) {
    CV_Assert((a.channels() == 1) && (b.channels() == 1));

    cv::Mat difference_abs = warm_wind::DifferenceAbs(a, b);
    cv::Scalar difference_abs_count = cv::countNonZero(difference_abs > 1e-8);
    return difference_abs_count;
}

/**
 * @brief Compute \f$c==const_value\f$, and \f$c = \sum(|a_i - b_i|>1e-8)\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool DifferenceCountEqual(const cv::Mat& a, const cv::Mat& b, const T const_value) {
    cv::Scalar difference_abs_count = warm_wind::DifferenceCount(a, b);
    return difference_abs_count[0] == const_value;
}

/**
 * @brief Compute \f$c<const_value\f$, and \f$c = \sum(|a_i - b_i|>1e-8)\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool DifferenceCountLess(const cv::Mat& a, const cv::Mat& b, const T const_value) {
    cv::Scalar difference_abs_count = warm_wind::DifferenceCount(a, b);
    return difference_abs_count[0] < const_value;
}

/**
 * @brief Compute \f$c = \sum((|a_i - b_i|)/\min(a_i, b_i)>1e-8)\f$
 * @param a
 * @param b
 * @return
 */
inline cv::Scalar RelativeDifferenceCount(const cv::Mat& a, const cv::Mat& b) {
    CV_Assert((a.channels() == 1) && (b.channels() == 1));

    cv::Mat difference_abs = warm_wind::DifferenceAbs(a, b);
    cv::Mat min_mat = cv::min(a, b);
    cv::Scalar relative_difference_abs_count = cv::countNonZero((difference_abs / min_mat) > 1e-8);
    return relative_difference_abs_count;
}

/**
 * @brief Compute \f$c==const_value\f$, and \f$c = \sum((|a_i - b_i|)/\min(a_i, b_i)>1e-8)\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool RelativeDifferenceCountEqual(const cv::Mat& a, const cv::Mat& b, const T const_value) {
    cv::Scalar relative_difference_abs_count = warm_wind::RelativeDifferenceCount(a, b);
    return relative_difference_abs_count[0] == const_value;
}

/**
 * @brief Compute \f$c<const_value\f$, and \f$c = \sum((|a_i - b_i|)/\min(a_i, b_i)>1e-8)\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool RelativeDifferenceCountLess(const cv::Mat& a, const cv::Mat& b, const T const_value) {
    cv::Scalar relative_difference_abs_count = warm_wind::RelativeDifferenceCount(a, b);
    return relative_difference_abs_count[0] < const_value;
}
} // warm_wind

#endif //COMMON_UTILS_MAT_DIFFERENCE_H
