//========================================
// main.cpp
//
//  Created on: 2013/12/31
//      Author: you
//========================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <ctime>
#include <cmath>
#include <sstream>
#include <iostream>

void sample_0();
void sample_1();

#define __DEBUG__

int main(int argc, char* argv[]) {

#ifdef __DEBUG__
    sample_0();
#else
    sample_1();
#endif

    return 0;
}

void sample_0() {

    cv::VideoCapture cap0(0);
    cv::VideoCapture cap1(1);

    cv::Size img_size(100, 100);
    cv::Mat cap_img0 = cv::Mat::zeros(img_size, CV_8UC3);
    cv::Mat cap_img1 = cv::Mat::zeros(img_size, CV_8UC3);
    cv::Mat img_buffer0 = cv::Mat::zeros(
                                         cv::Size(img_size.width, 2 * img_size.height),
                                         CV_8UC3);
    cv::Mat img_buffer1 = cv::Mat::zeros(img_buffer0.size(), CV_8UC3);

    cv::Mat* img_ptr[2];
    img_ptr[0] = &img_buffer0;
    img_ptr[1] = &img_buffer1;

    cv::Mat img_toShow = cv::Mat::zeros(
                                        cv::Size(2 * img_size.width, 2 * img_size.height),
                                        CV_8UC3);
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);

    std::string prefix("D:\\images\\");
    {
//        struct tm* now;
//        auto t = time(0);
//        now = localtime(&t);
//        std::string str(asctime(now));
//        std::replace(str.begin(), str.end(), ':', '-');
//        std::replace(str.begin(), str.end(), ' ', '_');
//        str[str.length() - 1] = '_';
//
//        prefix = "D:\\images\\" + str + "\\";
    }

    const char THRESHOLD = 12;

    int elappsed = 0;
    std::stringstream ss;
    int index = 0;
    int prev = 1;
    while (true) {
        if (cv::waitKey(400) == 'q') {
            break;
        } else {
            cap0 >> cap_img1;
            cap1 >> cap_img0;

            cv::hconcat(cap_img0, cap_img1, *img_ptr[index]);

            bool isChanged = false;
            if (img_ptr[index]->rows == img_ptr[prev]->rows
                && img_ptr[index]->cols == img_ptr[prev]->cols) {

                cv::Mat img_diff;
                cv::subtract(*img_ptr[index], *img_ptr[prev], img_diff);
                cv::vconcat(*img_ptr[index], img_diff, img_toShow);

                int count = 0;
                for (int i = 0; i < img_ptr[index]->rows; ++i) {
                    for (int j = 0; j < img_ptr[index]->cols; ++j) {
                        char* color0 = (char*) &img_ptr[index]->at<int>(i, j);
                        char* color1 = (char*) &img_ptr[prev]->at<int>(i, j);
                        if (std::abs(color0[0] - color1[0]) > THRESHOLD
                            || std::abs(color0[1] - color1[1]) > THRESHOLD
                            || std::abs(color0[2] - color1[2]) > THRESHOLD) {

//                            std::cout << i << ", " << j << ": "
//                                << std::abs(color0[0] - color1[0]) << "_"
//                                << std::abs(color0[1] - color1[1]) << "_"
//                                << std::abs(color0[2] - color1[2]) << "_"
//                                << std::endl;
                            ++count;
                            if (count > img_ptr[index]->rows * img_ptr[index]->cols / 8) {
                                isChanged = true;
                                break;
                            }
                        }
                    }
                }
            }

            if (isChanged) {
                struct tm* now;
                auto t = time(0);
                now = localtime(&t);
                std::string str(asctime(now));
                std::replace(str.begin(), str.end(), ':', '-');
                std::replace(str.begin(), str.end(), ' ', '_');

                str[str.length() - 1] = '.';
                ss.str("");
                ss << elappsed++ << "_";
                std::string filename =
                    prefix
                        + ss.str()
                        + str
                        + std::string("jpg");
                std::cout << ss.str() << str << std::endl;
                bool canWrite = cv::imwrite(
                                            filename,
//                                            *img_ptr[index],
                        img_toShow,
                        { 50 });
                if (!canWrite) {
                    std::cout << "failed to save file: " << filename << std::endl;
                }
            }

            cv::imshow("image", img_toShow);
//            cv::imshow("image", *img_ptr[index]);

            prev = index;
            index = (index + 1) % 2;
        }
    }
}

void sample_1() {

    cv::VideoCapture cap0(0);
    cv::VideoCapture cap1(1);

    cv::Size img_size(100, 100);
    cv::Mat cap_img0 = cv::Mat::zeros(img_size, CV_8UC3);
    cv::Mat cap_img1 = cv::Mat::zeros(img_size, CV_8UC3);
    cv::Mat img_buffer0 = cv::Mat::zeros(
                                         cv::Size(img_size.width, 2 * img_size.height),
                                         CV_8UC3);
    cv::Mat img_buffer1 = cv::Mat::zeros(img_buffer0.size(), CV_8UC3);

    cv::Mat* img_ptr[2];
    img_ptr[0] = &img_buffer0;
    img_ptr[1] = &img_buffer1;

    cv::Mat img_toShow = cv::Mat::zeros(
                                        cv::Size(2 * img_size.width, 2 * img_size.height),
                                        CV_8UC3);

    cv::namedWindow("image", cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);

    std::string prefix("D:\\images\\");
    {
//        struct tm* now;
//        auto t = time(0);
//        now = localtime(&t);
//        std::string str(asctime(now));
//        std::replace(str.begin(), str.end(), ':', '-');
//        std::replace(str.begin(), str.end(), ' ', '_');
//        str[str.length() - 1] = '_';
//
//        prefix = "D:\\images\\" + str + "\\";
    }

    const char THRESHOLD = 12;

    int elappsed = 0;
    std::stringstream ss;
    int index = 0;
    int prev = 1;
    while (true) {
        if (cv::waitKey(400) == 'q') {
            break;
        } else {
            cap0 >> cap_img1;
            cap1 >> cap_img0;

            cv::hconcat(cap_img0, cap_img1, *img_ptr[index]);

            bool isChanged = false;
            if (img_ptr[index]->rows == img_ptr[prev]->rows
                && img_ptr[index]->cols == img_ptr[prev]->cols) {

                cv::Mat img_diff;
                cv::subtract(*img_ptr[index], *img_ptr[prev], img_diff);
                cv::vconcat(*img_ptr[index], img_diff, img_toShow);

                int count = 0;
                for (int i = 0; i < img_ptr[index]->rows
                        ; ++i) {
                    for (int j = 0; j < img_ptr[index]->cols; ++j) {
                        char* color0 = (char*) &img_ptr[index]->at<int>(i, j);
                        char* color1 = (char*) &img_ptr[prev]->at<int>(i, j);
                        if (std::abs(color0[0] - color1[0]) > THRESHOLD
                            || std::abs(color0[1] - color1[1]) > THRESHOLD
                            || std::abs(color0[2] - color1[2]) > THRESHOLD) {

//                            std::cout << i << ", " << j << ": "
//                                << std::abs(color0[0] - color1[0]) << "_"
//                                << std::abs(color0[1] - color1[1]) << "_"
//                                << std::abs(color0[2] - color1[2]) << "_"
//                                << std::endl;
                            ++count;
                            if (count > img_ptr[index]->rows * img_ptr[index]->cols / 8) {
                                isChanged = true;
                                break;
                            }
                        }
                    }
                }
            }

            if (isChanged) {
                struct tm* now;
                auto t = time(0);
                now = localtime(&t);
                std::string str(asctime(now));
                std::replace(str.begin(), str.end(), ':', '-');
                std::replace(str.begin(), str.end(), ' ', '_');

                str[str.length() - 1] = '.';
                ss.str("");
                ss << elappsed++ << "_";
                std::string filename =
                    prefix
                        + ss.str()
                        + str
                        + std::string("jpg");

                std::cout << ss.str() << str << std::endl;
                bool canWrite = cv::imwrite(
                                            filename,
                                            *img_ptr[index],
                                            //                        img_toShow,
                                            { 50 });
                if (!canWrite) {
                    std::cout << "failed to save file: " << filename << std::endl;
                }
            }

//            cv::imshow("image", img_toShow);
//            cv::imshow("image", *img_ptr[index]);

            prev = index;
            index = (index + 1) % 2;
        }
    }

}

