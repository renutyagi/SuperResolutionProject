#include "ImageEnhancer.h"
#include "ImageLoader.h"
#include "ImageRegistrator.h"
#include "Scaller.h"

int main(int argc, const char *argv[])
{
    ImageLoader imageLoader(argc, argv);
    ImageList images = imageLoader.loadImages();

    ImageRegistrator imageReg;
    ImageEnhancer   imageEnh;

    std::pair<Mat, Mat> imageAndWeights = imageReg.registerImages(images, 2, 3000);

    for (int i = 0; i < 1620; i++) {
        cv::bilateralFilter(
                imageAndWeights.first.clone(),
                imageAndWeights.first,
                4,
                4,
                4);
    }

    util::printImage(imageAndWeights.first, std::string("tst"));
    return 0;
}
