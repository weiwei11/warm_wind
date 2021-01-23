//
// Created by ww on 2020/12/21.
//

#ifndef COMMON_UTILS_TENSOR_DIFFERENCE_H
#define COMMON_UTILS_TENSOR_DIFFERENCE_H
#include "warm_wind/common_header.h"

namespace warm_wind {

/**
 * @brief Compute \f$c = |a - b|\f$
 * @param a
 * @param b
 * @return
 */
inline at::Tensor DifferenceAbs(const at::Tensor& a, const at::Tensor& b) {
    at::Tensor difference_abs = torch::abs(a - b);
    return difference_abs;
}

/**
 * @brief Compute \f$c = \sum|a_i - b_i|\f$
 * @param a
 * @param b
 * @return
 */
inline at::Tensor DifferenceSum(const at::Tensor& a, const at::Tensor& b) {
    AT_ASSERTM(a.sizes() == b.sizes());
    at::Tensor difference_abs = warm_wind::DifferenceAbs(a, b);
    at::Tensor difference_abs_sum = torch::sum(difference_abs);
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
inline bool DifferenceSumEqual(const at::Tensor& a, const at::Tensor& b, const T const_value) {
    at::Tensor difference_abs_sum = warm_wind::DifferenceSum(a, b);
    return (difference_abs_sum == const_value).item().toBool();
}

/**
 * @brief Compute \f$c<const_value\f$, and \f$c = \sum|a_i - b_i|\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool DifferenceSumLess(const at::Tensor& a, const at::Tensor& b, const T const_value) {
    at::Tensor difference_abs_sum = warm_wind::DifferenceSum(a, b);
    return (difference_abs_sum < const_value).item().toBool();
}

/**
 * @brief Compute \f$c = \sum(|a_i - b_i|>1e-8)\f$
 * @param a
 * @param b
 * @return
 */
inline at::Tensor DifferenceCount(const at::Tensor& a, const at::Tensor& b) {
    AT_ASSERTM(a.sizes() == b.sizes());
    at::Tensor difference_abs = warm_wind::DifferenceAbs(a, b);
    at::Tensor difference_abs_count = torch::sum(difference_abs > 1e-8);
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
inline bool DifferenceCountEqual(const at::Tensor& a, const at::Tensor& b, const T const_value) {
    at::Tensor difference_abs_count = warm_wind::DifferenceCount(a, b);
    return (difference_abs_count == const_value).item().toBool();
}

/**
 * @brief Compute \f$c<const_value\f$, and \f$c = \sum(|a_i - b_i|>1e-8)\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool DifferenceCountLess(const at::Tensor& a, const at::Tensor& b, const T const_value) {
    at::Tensor difference_abs_count = warm_wind::DifferenceCount(a, b);
    return (difference_abs_count < const_value).item().toBool();
}

/**
 * @brief Compute \f$c = \sum((|a_i - b_i|)/\min(a_i, b_i)>1e-8)\f$
 * @param a
 * @param b
 * @return
 */
inline at::Tensor RelativeDifferenceCount(const at::Tensor& a, const at::Tensor& b) {
    AT_ASSERTM(a.sizes() == b.sizes());
    at::Tensor difference_abs = warm_wind::DifferenceAbs(a, b);
    at::Tensor min_mat = torch::min(a, b);
    at::Tensor relative_difference_abs_count = torch::sum((difference_abs / min_mat) > 1e-8);
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
inline bool RelativeDifferenceCountEqual(const at::Tensor& a, const at::Tensor& b, const T const_value) {
    at::Tensor relative_difference_abs_count = warm_wind::RelativeDifferenceCount(a, b);
    return (relative_difference_abs_count == const_value).item().toBool();
}

/**
 * @brief Compute \f$c<const_value\f$, and \f$c = \sum((|a_i - b_i|)/\min(a_i, b_i)>1e-8)\f$
 * @param a
 * @param b
 * @param const_value
 * @return
 */
template <typename T>
inline bool RelativeDifferenceCountLess(const at::Tensor& a, const at::Tensor& b, const T const_value) {
    at::Tensor relative_difference_abs_count = warm_wind::RelativeDifferenceCount(a, b);
    return (relative_difference_abs_count < const_value).item().toBool();
}
} // warm_wind

#endif //COMMON_UTILS_TENSOR_DIFFERENCE_H
