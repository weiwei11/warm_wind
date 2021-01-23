//
// Created by ww on 2020/12/22.
//

#ifndef COMMON_UTILS_IMAGE_PROCESS_H
#define COMMON_UTILS_IMAGE_PROCESS_H

#include "warm_wind/common_header.h"

namespace warm_wind {
/**
 * @brief Compute image means for every channel
 * @param image [in]:
 * @return channels mean
 */
inline cv::Scalar ComputeChannelsMean(const cv::cuda::GpuMat& image) {
    cv::Scalar means = cv::cuda::sum(image);
    int count = image.rows * image.cols;
    return means / count;
}

/**
 * @brief Make 1-channel and 4-channels image to 3-channels image
 * @param image
 * @param new_image : 3-channels image
 */
inline void ToThreeChannels(cv::cuda::GpuMat& image, cv::cuda::GpuMat& new_image) {
    CV_Assert((image.channels() == 1) || (image.channels() == 3) || (image.channels() == 4));

    if (image.channels() == 1) {
#if (CV_VERSION_MAJOR >= 4)
        cv::cuda::cvtColor(image, image, cv::COLOR_GRAY2BGR);
#else
        cv::cuda::cvtColor(image, image, CV_GRAY2BGR);
#endif
    } else if (image.channels() == 4) {
#if (CV_VERSION_MAJOR >= 4)
        cv::cuda::cvtColor(image, image, cv::COLOR_BGRA2BGR);
#else
        cv::cuda::cvtColor(image, image, CV_BGRA2BGR);
#endif
    }
}

/**
 * @brief Compute pad sizes from specific image to specified aspect ratio image
 * @param height [in]: old image height
 * @param width [in]: old image width
 * @param new_aspect_ratio [in]: new image aspect ratio which is height/width of new image
 * @return (h_pad, w_pad)
 */
inline cv::Scalar_<int> ComputePadSizes(const int height, const int width, const double new_aspect_ratio) {
    // expand image but keep scale
    cv::Scalar_<int> pad_sizes(0, 0); // (h_pad, w_pad)
    if (width * new_aspect_ratio > height) {
        int expend_height = std::ceil(width * new_aspect_ratio);
//        int expend_width = width;
//        expend_height = expend_height >= height ? expend_height : height;
//        expend_width = expend_width >= width ? expend_width : width;
        pad_sizes[0] = (expend_height - height) / 2;
        pad_sizes[1] = 0;
    } else {
//        int expend_height = height;
        int expend_width = std::ceil(height / new_aspect_ratio);
//        expend_height = expend_height >= height ? expend_height : height;
//        expend_width = expend_width >= width ? expend_width : width;
        pad_sizes[0] = 0;
        pad_sizes[1] = (expend_width - width) / 2;
    }
    return pad_sizes;
}

/**
 * @brief Add pad around the image
 * @param image [in]:
 * @param pad_sizes [in]: (h_pad, w_pad)
 * @param fill_value [in]: the specified value for pad
 * @return
 */
inline cv::cuda::GpuMat AddPad(const cv::cuda::GpuMat& image, const cv::Scalar_<int>& pad_sizes, const cv::Scalar& fill_value) {
    int height = image.rows, width = image.cols;
    cv::cuda::GpuMat expand_image(height + 2*pad_sizes[0], width + 2*pad_sizes[1], image.type(), fill_value);
    cv::Rect roi_rect = cv::Rect(pad_sizes[1], pad_sizes[0], image.cols, image.rows);
    image.copyTo(expand_image(roi_rect));
    return expand_image;
}

} // warm_wind

#endif //COMMON_UTILS_IMAGE_PROCESS_H
