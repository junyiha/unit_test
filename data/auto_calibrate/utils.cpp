//
// Created by liangsy on 23-7-10.
//
#include "utils.h"

using namespace std;
using namespace cv;
using namespace boost::filesystem;
namespace po = boost::program_options;

bool readStringList(const string& filename, vector<string>& l)
{
    l.resize(0);
    FileStorage fs(filename, FileStorage::READ);
    if (!fs.isOpened())
        return false;
    size_t dir_pos = filename.rfind('/');
    if (dir_pos == string::npos)
        dir_pos = filename.rfind('\\');
    FileNode n = fs.getFirstTopLevelNode();
    if (n.type() != FileNode::SEQ)
        return false;
    FileNodeIterator it = n.begin(), it_end = n.end();
    for (; it != it_end; ++it)
    {
        string fname = (string)*it;
        if (dir_pos != string::npos)
        {
            string fpath = samples::findFile(filename.substr(0, dir_pos + 1) + fname, false);
            if (fpath.empty())
            {
                fpath = samples::findFile(fname);
            }
            fname = fpath;
        }
        else
        {
            fname = samples::findFile(fname);
        }
        l.push_back(fname);
    }
    return true;
}

bool compareFilesWithoutExt(string& a, string& b)
{
    vector<string> tmp_split_a, tmp_split_b, tmp_a, tmp_b;
    boost::split(tmp_split_a,a,boost::is_any_of("/"));
    boost::split(tmp_split_b,b,boost::is_any_of("/"));
    boost::split(tmp_a,tmp_split_a[tmp_split_a.size()-1],boost::is_any_of("."));
    boost::split(tmp_b,tmp_split_b[tmp_split_b.size()-1],boost::is_any_of("."));
    int i1 = stoi(tmp_a[0]);
    int i2 = stoi(tmp_b[0]);
    return (i1 < i2);
}

void retrieveFilesInDir(path& input_p, vector<string >& out, bool sort_output)
{
    directory_iterator end_itr;
    for (directory_iterator itr(input_p); itr != end_itr; ++itr)
    {
        if (is_regular_file(itr->path()))
        {
            string current_file = itr->path().string();
            out.push_back(current_file);
        }
    }
    if(sort_output)
        std::sort(out.begin(), out.end(), compareFilesWithoutExt);
}

// 读取机械臂位姿
void readPoseFromCSV(const string& input_path, Mat& out_mat, char delim)
{
    std::ifstream input_file(input_path);
    string current_line;
    vector<vector<float> > all_data;        //vector <float>是一个float向量存储一组元素，那么vector<vector<float> >就是向量的元素为向量
    while(getline(input_file, current_line))
    {
        vector<float> values; // 每一列的数据
        stringstream temp(current_line);
        string single_value;
        while(getline(temp,single_value,delim))
        {
            // 将字符串转成float类型
            float f = stof(single_value);
            values.push_back(f);
        }
        all_data.push_back(values); // 每一行的数据
    }

    out_mat = Mat::zeros((int)all_data.size(), (int)all_data[0].size(), CV_64FC1);
    for(int rows = 0; rows < (int)all_data.size(); rows++)
    {
        for(int cols= 0; cols< (int)all_data[0].size(); cols++)
        {
            out_mat.at<double>(rows,cols) = all_data[rows][cols];
        }
    }
}

bool isRotatedMatrix(Mat& R) // 旋转矩阵的转置矩阵是它的逆矩阵，逆矩阵 * 矩阵 = 单位矩阵
{
    Mat temp33 = R({ 0,0,3,3 }); // 无论输入是几阶矩阵，均提取其三阶矩阵
    Mat Rt;
    transpose(temp33, Rt);  // 转置矩阵
    Mat shouldBeIdentity = Rt * temp33; // 是旋转矩阵则乘积为单位矩阵
    Mat I = Mat::eye(3, 3, shouldBeIdentity.type());

    return cv::norm(I, shouldBeIdentity) < 1e-6;
}

/**************************************************
* @brief   欧拉角转换为旋转矩阵
* @note
* @param    const std::string& seq  指定欧拉角的排列顺序；（机械臂的位姿类型有xyz,zyx,zyz几种，需要区分）
* @param    const Mat& eulerAngle   欧拉角（1*3矩阵）, 角度值
* @param
* @return   返回3*3旋转矩阵
**************************************************/
Mat eulerAngleToRotateMatrix(const Mat& eulerAngle, const std::string& seq, bool is_rad)
{
    CV_Assert(eulerAngle.rows == 1 && eulerAngle.cols == 3); // 检查参数格式是否正确

    if (!is_rad)
    {
        eulerAngle /= (180 / CV_PI); // 角度转弧度
    }

    Matx13d m(eulerAngle);	// <double, 1, 3>

    auto rx = m(0, 0), ry = m(0, 1), rz = m(0, 2);
    auto rxs = sin(rx), rxc = cos(rx);
    auto rys = sin(ry), ryc = cos(ry);
    auto rzs = sin(rz), rzc = cos(rz);

    // XYZ方向的旋转矩阵，即：Rx，Ry，Rz
    Mat RotX = (Mat_<double>(3, 3) << 1, 0, 0,
            0, rxc, -rxs,
            0, rxs, rxc);
    Mat RotY = (Mat_<double>(3, 3) << ryc, 0, rys,
            0,	  1, 0,
            -rys, 0, ryc);
    Mat RotZ = (Mat_<double>(3, 3) << rzc, -rzs, 0,
            rzs, rzc, 0,
            0, 0, 1);
    // 按一定顺序合成旋转矩阵
    cv::Mat rotMat;

    if (seq == "zyx") rotMat = RotX * RotY * RotZ;
    else if (seq == "yzx") rotMat = RotX * RotZ * RotY;
    else if (seq == "zxy") rotMat = RotY * RotX * RotZ;
    else if (seq == "yxz") rotMat = RotZ * RotX * RotY;
    else if (seq == "xyz") rotMat = RotZ * RotY * RotX;
    else if (seq == "xzy") rotMat = RotY * RotZ * RotX;
    else
    {
        cout << "Euler Angle Sequence string is wrong...";
    }
    if (!isRotatedMatrix(rotMat)) // 进行判断，欧拉角在特殊情况下，会出现死锁
    {
        cout << "Euler Angle convert to RotatedMatrix failed..." << endl;
        exit(-1);
    }
    return rotMat;
}

void Transform2Rt(Mat& HomoMtr, Mat& R, Mat& T)
{
    Rect R_rect(0, 0, 3, 3);
    Rect T_rect(3, 0, 1, 3);
    R = HomoMtr(R_rect);
    T = HomoMtr(T_rect);
}

Mat R_t2Transform(const Mat& R,const Mat& T)
{
    Mat HomoMtr;
    Mat_<double> R1 = (Mat_<double>(4, 3) <<
            R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2),
            R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2),
            R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2),
            0, 0, 0);
    Mat_<double> T1 = (Mat_<double>(4, 1) <<
            T.at<double>(0,0),
            T.at<double>(1,0),
            T.at<double>(2,0),
            1);
    cv::hconcat(R1, T1, HomoMtr); // 矩阵拼接
    return HomoMtr;
}