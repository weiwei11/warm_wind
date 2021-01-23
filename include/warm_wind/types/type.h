//
// Created by ww on 2020/12/15.
//

#ifndef COMMON_UTILS_TYPE_H
#define COMMON_UTILS_TYPE_H

#include "warm_wind/common_header.h"

#ifdef USE_TORCH
namespace warm_wind {
#define WW_FORALL_SCALAR_TYPES(_) \
    _('u', torch::kUInt8) /* 0 */       \
    _('c', torch::kInt8) /* 1 */            \
    _('s', torch::kInt16) /* 2 */            \
    _('i', torch::kInt32) /* 4 */               \
    _('f', torch::kFloat32) /* 5 */                \
    _('d', torch::kFloat64) /* 6 */

static inline char ScalarType2CodeChar(torch::ScalarType t) {
#define DEFINE_CASE(code_char, scalar_type) \
    case scalar_type:   \
        return code_char;

    switch (t) {
        WW_FORALL_SCALAR_TYPES(DEFINE_CASE)
        default:
            return '\0';
    }
#undef DEFINE_CASE
}

static inline torch::ScalarType CodeChar2ScalarType(char code_char) {
#define DEFINE_CASE(code_char, scalar_type) \
    case code_char:   \
        return scalar_type;

    switch (code_char) {
        WW_FORALL_SCALAR_TYPES(DEFINE_CASE)
        default:
            std::cerr << "Unknown code char" << std::endl;
            return torch::ScalarType::Undefined;
    }
#undef DEFINE_CASE
}

} // warm_wind
#endif // USE_TORCH
#endif //COMMON_UTILS_TYPE_H
