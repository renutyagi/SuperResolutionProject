#include "ImageRegistrator.h"

ImageRegistrator::ImageRegistrator()
{

}

ImageRegistrator::~ImageRegistrator()
{

}

PointVector ImageRegistrator::removeBadPoints(PointVector points, std::vector<uchar> status)
{
    std::vector<uchar>::iterator statusIter = status.begin();
    PointVector::iterator pointIter = points.begin();
    PointVector goodPoints(points.size() - std::count(status.begin(), status.end(), 0));

    for (int i = 0; statusIter != status.end(); ++statusIter, ++pointIter) {
        if (*statusIter == 1) {
            goodPoints[i] = *pointIter;
            ++i;
        }
    }

    return goodPoints;
}

std::pair<Mat, Mat> 
ImageRegistrator::registerImages(ImageList inputImages, int resizeFactor, int cornersAmount)
{
    Scaller                     scaller;
    MatrixList                  homographies;
    ImageList::const_iterator   selectedImage = inputImages.begin();
    ImageList::iterator         nthImage = inputImages.begin();
    PointVector                 selectedImageCorners(cornersAmount);
    PointVector                 nthImageCorners(cornersAmount);
    std::vector<uchar>          status(cornersAmount);
    std::vector<float>          error(cornersAmount);

    goodFeaturesToTrack(
            *selectedImage,
            selectedImageCorners,
            cornersAmount,
            0.01,
            1);

    cv::cornerSubPix(
            *selectedImage,
            selectedImageCorners,
            Size(5, 5),
            Size(-1, -1),
            TermCriteria(
                TermCriteria::COUNT + TermCriteria::EPS,
                6000,
                0.001)
            );


    for (; nthImage != inputImages.end(); ++nthImage) {
        if (nthImage != selectedImage) {
            calcOpticalFlowPyrLK(
                    *selectedImage,
                    *nthImage,
                    selectedImageCorners,
                    nthImageCorners,
                    status,
                    error);

            PointVector selImgCor = removeBadPoints(selectedImageCorners, status);
            PointVector nthImgCor = removeBadPoints(nthImageCorners, status);

            Mat H = findHomography(
                    selImgCor,
                    nthImgCor,
                    CV_RANSAC,
                    0.1);

            if (cv::norm(Point2f(H.at<double>(0,2), H.at<double>(1,2))) > 2) {
                nthImage->release();
                continue;
            }

            roundMatrixCoefficients(H, resizeFactor);
            homographies.push_back(H);
        }
    }  
    
    inputImages.erase(std::remove_if(inputImages.begin(),
                inputImages.end(),
                ImageRegistrator::ImageRemPred()),
            inputImages.end());
        
    inputImages = scaller.upscaleImages(inputImages, resizeFactor); 
    MatrixList::iterator h = homographies.begin();

    for (nthImage = inputImages.begin(); nthImage != inputImages.end(); ++nthImage) {
        if (nthImage != selectedImage) {
            util::printMatrix(*h, 12);
            warpPerspective(
                    nthImage->clone(),
                    *nthImage,
                    *h,
                    nthImage->size(),
                    cv::INTER_NEAREST | cv::WARP_INVERSE_MAP);
            ++h;
        }
    }

    Mat                 output(selectedImage->size(), selectedImage->type());
    std::list<uchar>    pixelValues;
    Mat                 medianWeights(output.size(), output.type());
    
    for (int i = 0; i < selectedImage->rows ; ++i) {
        for (int j = 0; j < selectedImage->cols; ++j) {

            for (nthImage = inputImages.begin(); nthImage != inputImages.end(); ++nthImage) {
                uchar value = (*nthImage).at<uchar>(i,j);

                if (value != 0)  {
                    pixelValues.push_back(value);
                }
            }

            if ( !pixelValues.empty() ) {
                output.at<uchar>(i,j) = produceMedian(pixelValues);
                medianWeights.at<uchar>(i,j) = 
                    static_cast<uchar>(std::sqrt(pixelValues.size()));
            }

            pixelValues.clear();
        }
    }

    std::cout << "pixel covreage : " << pixelCovreage(output) << std::endl;

    Mat fullMedian(output.size(), output.type());
    cv::medianBlur(output, fullMedian, 1);

    for (int i = 0; i < output.rows ; ++i) {
        for (int j = 0; j < output.cols; ++j) {
            if (output.at<uchar>(i,j) == 0) {
                output.at<uchar>(i,j) = fullMedian.at<uchar>(i,j);
            }
        }
    }
    util::printImage(output, std::string("tada"));

    return std::pair<Mat, Mat>(output, medianWeights);
}

double ImageRegistrator::pixelCovreage(Mat image)
{
    double emptyPixels = std::count(image.begin<uchar>(), image.end<uchar>(), 0);
    double totalAmountOfPixels = image.size().width * image.size().height;

    return ( totalAmountOfPixels - emptyPixels ) / totalAmountOfPixels;
}

void ImageRegistrator::roundMatrixCoefficients(Mat& matrix, int resizeFactor)
{
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            if ((i != 0 && j != 2) || (i != 1 && j != 2)) {
                double value = matrix.at<double>(i,j);
                matrix.at<double>(i,j) = (value > 0.0) ? 
                    std::floor(value + 0.5) : std::ceil(value - 0.5);
            }
        }
    }
}
