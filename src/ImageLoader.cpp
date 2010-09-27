#include "ImageLoader.h"

ImageLoader::ImageLoader()
{

}

ImageLoader::ImageLoader(int argc, const char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        fileNames.push_back(argv[i]);
    }
}

const std::list<std::string> & ImageLoader::getFileNames()
{
    return fileNames;
}

ImageList ImageLoader::loadImages()
{
    ImageList inputImages;

    std::list<std::string>::iterator fName;
    for (fName = fileNames.begin(); fName != fileNames.end(); ++fName) {
        Mat image = imread(*fName, 0);

        if (image.data == 0) {
            continue;
        }

        inputImages.push_back(image);
    }

    return inputImages;
}
