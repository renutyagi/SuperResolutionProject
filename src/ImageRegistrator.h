#ifndef IMAGE_REGISTRATOR
#define IMAGE_REGISTRATOR

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include "Scaller.h"
#include "types.h"
#include "util.h"

class ImageRegistrator 
{
public:
    ImageRegistrator();
    virtual ~ImageRegistrator();

    std::pair<Mat, Mat> 
        registerImages(ImageList inputImages, int resizeFactor = 2, int cornersAmount = 10);

private:
    inline PointVector  removeBadPoints(PointVector points, std::vector<uchar> status);
    double pixelCovreage(Mat image);
    void roundMatrixCoefficients(Mat& matrix, int resizeFactor);

    inline uchar produceMedian(std::list<uchar> pixelValues)
    {
        int n = pixelValues.size();
        pixelValues.sort();
        std::vector<uchar> values(pixelValues.begin(), pixelValues.end());

        return  (n % 2 == 0) ? 
            (values[n / 2 - 1] + values[n / 2]) / 2 : values[(n - 1) / 2];
    }
    
    struct ImageRemPred 
    {
        bool operator()(Mat& img) {
            return img.empty();
        }
    };
};

#endif /* end of include guard: IMAGE_REGISTRATER */
