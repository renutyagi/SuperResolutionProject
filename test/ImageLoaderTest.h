#ifndef IMAGELOADERTEST
#define IMAGELOADERTEST

#include <cxxtest/TestSuite.h>
#include "../src/ImageLoader.h"

class ImageLoaderTest : public CxxTest::TestSuite
{
public:
     void testLoadingImages() {
        // given
        char fileNames[][7] = {
            "01.jpg", 
            "02.jpg", 
            "03.jpg", 
            "04.jpg", 
            "05.jpg", 
        }
        ImageLoader imageLoader(6, &fileNames);
     }
private: 
};

#endif /* end of include guard: IMAGELOADERTEST */
