#ifndef UTIL
#define UTIL

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cv.h>
#include <highgui.h>
#include "types.h"

namespace util {
    using namespace cv;

    template<typename T>
    void printVector(const std::vector<T>& vect, int fieldWidth = 8) {
        typename std::vector<T>::const_iterator elem;
        for (elem = vect.begin(); elem != vect.end(); ++elem) {
            std::cout << std::setw(fieldWidth) << static_cast<double>(*elem);
        }
        std::cout << std::endl;
    }

    void printImage(const Mat& image, const std::string& windowName);
    void printMatrix(Mat & mat, int fieldWidth = 4);
    void markPixel(Mat& mat, int x, int y);
    void printPointVector(const PointVector pVect, int fieldWidth = 0);
} /* util */

#endif /* end of include guard: UTIL */
