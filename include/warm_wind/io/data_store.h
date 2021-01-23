//
// Created by ww on 2020/12/14.
//

#ifndef COMMON_UTILS_DATA_STORE_H
#define COMMON_UTILS_DATA_STORE_H

#include "warm_wind/types/type.h"

#if (defined(USE_OPENCV) && defined(USE_TORCH))

//These write and read functions must exist as per the inline functions in operations.hpp
/**
 * @brief Write at::Tensor to cv::FileStorage
 * @param fs [in]: cv::FileStorage
 * @param name [in]: variable name
 * @param m [in]: at::Tensor
 */
static void write(cv::FileStorage& fs, const std::string& name, const at::Tensor& m) {

    CV_Assert(m.is_contiguous());
//        fs.startWriteStruct(name, cv::FileNode::MAP, cv::String("torch-tensor"));
    fs << "{";
    // write sizes
    auto m_sizes = m.sizes();
    fs << "sizes" << "[:";
    for(long m_size : m_sizes) {
        fs << (int)m_size;
    }
    fs << "]";
    // write element type
    char dt = warm_wind::ScalarType2CodeChar(m.scalar_type());
    CV_Assert(dt != '\0');
    fs << "dt" << std::string(1, dt);
    // write data
    fs << "data" << "[:";
    fs.writeRaw(cv::String(1, dt), static_cast<const uchar *>(m.data_ptr()), m.numel() * at::elementSize(m.scalar_type()));
    fs << "]";
    fs << "}";
//        fs.endWriteStruct();
}

/**
 * @brief Read a at::Tensor from cv::FileNode
 * @param node [in]: cv::FileNode
 * @param m [out]: at::Tensor
 * @param default_value [in]: default value when specific name of data is not exist
 */
static void read(const cv::FileNode& node, at::Tensor& m, const at::Tensor& default_value = at::zeros({1})) {
    if (node.empty())
        m = default_value;
    else {
        // read sizes
        std::vector<int64_t> sizes;
        cv::FileNode sizes_node = node["sizes"];
        for (auto it = sizes_node.begin(); it < sizes_node.end(); ++it) {
            int64_t tmp = (int)(*it);
            sizes.push_back(tmp);
        }
        // read element type
        std::string dt;
        node["dt"] >> dt;
        // read data
        m = at::zeros(c10::ArrayRef<int64_t>(sizes), at::TensorOptions(warm_wind::CodeChar2ScalarType(dt[0])));
        cv::FileNode data_node = node["data"];
        data_node.readRaw(dt, (uchar*)m.data_ptr(), m.numel()*at::elementSize(m.scalar_type()));
    }
}

//    static std::ostream &operator<<(std::ostream &out, const at::Tensor &x) {
//        out << "{ id = " << m.id << ", ";
//        out << "X = " << m.X << ", ";
//        out << "A = " << m.A << "}";
//        return out;
//    }
namespace warm_wind {
/**
 * @brief Write a at::Tensor to cv::FileStorage
 * @param fs [in]: cv::FileStorage
 * @param name [in]: variable name
 * @param m [in]: at::Tensor
 */
static void Write(cv::FileStorage& fs, const std::string& name, const at::Tensor& m) {
    fs << name;
    write(fs, name, m);
}

/**
 * @brief Read a at::Tensor from cv::FileStorage
 * @param fs [in]: cv::FileStorage
 * @param name [in]: variable name
 * @param m [out]: at::Tensor
 */
static void Read(cv::FileStorage& fs, const std::string& name, at::Tensor& m) {
    read(fs[name], m);
}

} // warm_wind
#endif // USE_OPENCV and USE_TORCH

#endif //COMMON_UTILS_DATA_STORE_H
