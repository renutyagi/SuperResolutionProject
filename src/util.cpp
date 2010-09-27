#include "util.h"

void util::printImage(const Mat& image, const std::string& windowName) 
{
    imshow(windowName, image);
    waitKey(); 
}

void util::printMatrix(Mat & mat, int fieldWidth)
{
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            std::cout << std::setw(fieldWidth) << mat.at<double>(i,j);
        }
        std::cout << std::endl;	
    }
    std::cout << std::endl;	
}

void util::printPointVector(const PointVector pVect, int fieldWidth)
{
    PointVector::const_iterator point;
    for (point = pVect.begin(); point != pVect.end(); ++point) {
        std::cout << "["
            << std::setw(fieldWidth) << (*point).x << " , "
            << std::setw(fieldWidth) << (*point).y << "]  ";
    }
    std::cout << std::endl;
}

void util::markPixel(Mat& mat, int x, int y)
{
    mat.at<uchar>(x, y) = 0;   
}
