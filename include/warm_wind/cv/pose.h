//
// Created by ww on 2020/12/24.
//

#ifndef COMMON_UTILS_POSE_H
#define COMMON_UTILS_POSE_H

#include "warm_wind/common_header.h"

namespace warm_wind {

/**
 * @brief Compute 3D points projection on image
 * @param opoints [in]: (N, 3), N is the number of 3D points
 * @param rt [in]: (4, 4), rotation matrix and translation vector of pose
 * @param camera_intrinsic [in]: (3, 3), camera intrinsic matrix
 * @return (N, 2), 2D points on image corresponding to 3D points
 */
cv::Mat ProjectPoints(const cv::Mat &opoints, const cv::Mat &rt, const cv::Mat &camera_intrinsic) {
    cv::Mat ipoints_2d_array;
    cv::Mat rvec, tvec, dist_coeffs(1, 4, CV_32FC1, cv::Scalar(0));
    cv::Rodrigues(rt.rowRange(0, 3).colRange(0, 3), rvec);
    tvec = rt.rowRange(0, 3).col(3);
    cv::projectPoints(opoints, rvec, tvec, camera_intrinsic, dist_coeffs, ipoints_2d_array);
    cv::Mat ipoints = ipoints_2d_array.reshape(1, ipoints_2d_array.rows);

    // convert 2 channel mat to mat
//    cv::Mat points_2d(points_3d.rows, 2, CV_32FC1, cv::Scalar(0));
//    for (int i = 0; i < ipoints_2d_array.rows; i++)
//    {
//        points_2d.at<float>(i, 0) = ipoints_2d_array.at<float>(i, 0);
//        points_2d.at<float>(i, 1) = ipoints_2d_array.at<float>(i, 1);
//    }

    return ipoints;
}

/**
 * @brief A warp function for cv::solvePnP
 * @param opoints [in]: (N, 3), N is the number of 3D points
 * @param ipoints [in]: (N, 2), N is the number of 2D points corresponding to 3D points
 * @param camera_intrinsic [in]: (3, 3), camera intrinsic matrix
 * @param method [in]: method used to solve PnP
 * @return the rotation matrix and translation vector of pose which shape is (4, 4)
 */
cv::Mat SolvePnP(const cv::Mat &opoints, const cv::Mat &ipoints, const cv::Mat &camera_intrinsic, const int method) {
    if (opoints.rows != ipoints.rows) {
        return cv::Mat::eye(cv::Size(4, 4), CV_32FC1);
    }

    // init
    cv::Mat new_points_3d, new_points_2d, new_camera_matrix;

    opoints.convertTo(new_points_3d, CV_64FC1);
    ipoints.convertTo(new_points_2d, CV_64FC1);
    camera_intrinsic.convertTo(new_camera_matrix, CV_64FC1);
    cv::Mat dist_coeffs(1, 4, CV_64FC1, cv::Scalar(0));
    cv::Mat rvec, tvec;
    cv::Mat rot_mat;

    // pnp
    cv::solvePnP(opoints, ipoints, camera_intrinsic, dist_coeffs, rvec, tvec, false, method);
    cv::Rodrigues(rvec, rot_mat);
    rot_mat.convertTo(rot_mat, CV_32FC1);
    tvec.convertTo(tvec, CV_32FC1);

    // get rt
    cv::Mat rt = cv::Mat::eye(cv::Size(4, 4), CV_32FC1);
    rot_mat.copyTo(rt.rowRange(0, 3).colRange(0, 3));
    tvec.copyTo(rt.rowRange(0, 3).col(3));

    return rt;
}

/**
 * @brief A warp function of cv::solvePnPRansac
 * @param opoints [in]: (N, 3), N is the number of 3D points
 * @param ipoints [in]: (N, 2), N is the number of 2D points corresponding to 3D points
 * @param camera_intrinsic [in]: (3, 3), camera intrinsic matrix
 * @param inliers [in]: inlier points indexes
 * @param iterations_count [in]: the iterations count of ransac
 * @param reprojection_error [in]:
 * @param confidence [in]:
 * @param method [in]: the method of solve PnP
 * @return rotation matrix and translation vector of pose which shape is (3, 3)
 */
    cv::Mat
    SolvePnPRansac(const cv::Mat &opoints, const cv::Mat &ipoints, const cv::Mat &camera_intrinsic, cv::Mat &inliers,
                   const int iterations_count, const float reprojection_error, const double confidence,
                   const int method) {
        if (opoints.rows != ipoints.rows) {
            return cv::Mat::eye(cv::Size(4, 4), CV_32FC1);
        }

        // init
        // cv::Mat new_points_3d, new_points_2d, new_camera_matrix;

        // opoints.convertTo(new_points_3d, CV_64FC1);
        // ipoints.convertTo(new_points_2d, CV_64FC1);
        // camera_intrinsic.convertTo(new_camera_matrix, CV_64FC1);
        cv::Mat dist_coeffs(1, 8, CV_64FC1, cv::Scalar(0));
        cv::Mat rvec, tvec;
        cv::Mat rot_mat;

        // pnp
        cv::solvePnPRansac(opoints, ipoints, camera_intrinsic, dist_coeffs, rvec, tvec, false,
                           iterations_count, reprojection_error, confidence, inliers, method);
        cv::Rodrigues(rvec, rot_mat);
        rot_mat.convertTo(rot_mat, CV_32FC1);
        tvec.convertTo(tvec, CV_32FC1);

        // get rt
        cv::Mat rt = cv::Mat::eye(cv::Size(4, 4), CV_32FC1);
        rot_mat.copyTo(rt.rowRange(0, 3).colRange(0, 3));
        tvec.copyTo(rt.rowRange(0, 3).col(3));

        return rt;
    }

} // warm_wind

#endif //COMMON_UTILS_POSE_H
