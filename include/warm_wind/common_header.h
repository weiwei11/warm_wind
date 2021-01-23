//
// Created by ww on 2020/12/15.
//

#ifndef COMMON_UTILS_COMMON_HEADER_H
#define COMMON_UTILS_COMMON_HEADER_H

#ifdef USE_OPENCV
// headers for opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
#include <opencv2/core.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#endif // USE_OPENCV

#ifdef USE_TORCH
#include <torch/script.h>
//#include <torch/types.h>
#endif // USE_TORCH

#endif //COMMON_UTILS_COMMON_HEADER_H
