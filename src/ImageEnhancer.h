#ifndef IMAGE_ENHANCER
#define IMAGE_ENHANCER

#include "util.h"
#include "types.h"

class ImageEnhancer 
{
public:
    ImageEnhancer();
    virtual ~ImageEnhancer();
    
    Mat enhance(Mat image, Mat weights, int scale = 2);
private:
};

#endif /* end of include guard: IMAGE_ENHANCER */
