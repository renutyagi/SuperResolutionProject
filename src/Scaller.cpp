#include "Scaller.h"

Scaller::Scaller()
{

}

Scaller::~Scaller()
{

}

Mat Scaller::upscaleImage(Mat image, int scale)
{
    Mat upscaledImage(image.rows * scale, image.cols * scale, image.type(), Scalar(0));

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			upscaledImage.at<uchar>(i * scale, j * scale) = image.at<uchar>(i, j);
		}
	}
	
	return upscaledImage;
}


ImageList Scaller::upscaleImages(ImageList inputImages, int scale) 
{
    ImageList upscaledImages;
    for (ImageList::iterator image = inputImages.begin(); image != inputImages.end(); ++image) {
       upscaledImages.push_back(upscaleImage(*image, scale));
    }

    return upscaledImages;
}
