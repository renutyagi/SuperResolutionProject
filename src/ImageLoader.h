#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <iostream>
#include <list>
#include <string>
#include <highgui.h>
#include "types.h"

class ImageLoader
{
public:
    ImageLoader();
    ImageLoader(int argc, const char *argv[]);
    
    const std::list<std::string>&   getFileNames();
    ImageList	                    loadImages();

private:
    std::list<std::string>          fileNames;
};

#endif // IMAGELOADER_H
