#ifndef SCALLER
#define SCALLER

#include <iostream>
#include "util.h"
#include "types.h"

class Scaller 
{
public:
    Scaller();
    virtual ~Scaller();

    Mat upscaleImage(Mat image, int scale);
    ImageList upscaleImages(ImageList inputImages, int scale);
private:
    
};

#endif /* end of include guard: SCALLER */
