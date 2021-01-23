//
// Created by ww on 2020/12/25.
//

#ifndef COMMON_UTILS_VISUALIZATION_H
#define COMMON_UTILS_VISUALIZATION_H
#include "warm_wind/common_header.h"

namespace warm_wind {
/**
 * @brief Draw 2D points on image
 * @param image [in][out]:
 * @param ipoints [in]: 2D points, shape is (N, 2), N is the number of points
 * @param point_color [in]:
 * @param point_size [in]:
 */
void DrawPointsOnImage(cv::Mat& image, const cv::Mat& ipoints, const cv::Scalar& point_color=CV_RGB(255, 0, 0), const int point_size=3) {
    // draw 2D points
    for (int i = 0; i < ipoints.rows; i++) {
        cv::Point cur_point(ipoints.at<float>(i, 0), ipoints.at<float>(i, 1));
        cv::circle(image, cur_point, point_size, point_color, 3);
    }
}

/**
 * @brief Draw 3D bounding box on image
 * @param image [in][out]:
 * @param corner_points [in]: shape is (8, 2), order is
   @verbatim
           4----5
          /|   /|
         6-+--7 |
         | 0--+-1
         |/   |/
         2----3
   @endverbatim
 */
void DrawBoundingBox3DOnImage(cv::Mat& image, const cv::Mat& corner_points) {
    // draw bounding box
    int pts_idx_array[2][8] = {{0, 1, 3, 2, 0, 4, 6, 2}, {5, 4, 6, 7, 5, 1, 3, 7}};
    for (int i = 0; i < 7; i++) {
        int pt_idx1 = pts_idx_array[0][i];
        int pt_idx2 = pts_idx_array[0][i+1];
        cv::Point point1(corner_points.at<float>(pt_idx1, 0), corner_points.at<float>(pt_idx1, 1));
        cv::Point point2(corner_points.at<float>(pt_idx2, 0), corner_points.at<float>(pt_idx2, 1));
        cv::line(image, point1, point2, CV_RGB(255, 0, 0), 3);

        pt_idx1 = pts_idx_array[1][i];
        pt_idx2 = pts_idx_array[1][i+1];
        point1 = cv::Point(corner_points.at<float>(pt_idx1, 0), corner_points.at<float>(pt_idx1, 1));
        point2 = cv::Point(corner_points.at<float>(pt_idx2, 0), corner_points.at<float>(pt_idx2, 1));
        cv::line(image, point1, point2, CV_RGB(0, 0, 255), 3);
    }
}
} // warm_wind

#endif //COMMON_UTILS_VISUALIZATION_H
