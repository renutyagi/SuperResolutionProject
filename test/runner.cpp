/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/StdioPrinter.h>
#include <cxxtest/X11Gui.h>

int main( int argc, char *argv[] ) {
 return CxxTest::GuiTuiRunner<CxxTest::X11Gui, CxxTest::StdioPrinter>( argc, argv ).run();
}
#include "ImageLoaderTest.h"

static ImageLoaderTest suite_ImageLoaderTest;

static CxxTest::List Tests_ImageLoaderTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ImageLoaderTest( "ImageLoaderTest.h", 7, "ImageLoaderTest", suite_ImageLoaderTest, Tests_ImageLoaderTest );

static class TestDescription_ImageLoaderTest_testLoadingImages : public CxxTest::RealTestDescription {
public:
 TestDescription_ImageLoaderTest_testLoadingImages() : CxxTest::RealTestDescription( Tests_ImageLoaderTest, suiteDescription_ImageLoaderTest, 10, "testLoadingImages" ) {}
 void runTest() { suite_ImageLoaderTest.testLoadingImages(); }
} testDescription_ImageLoaderTest_testLoadingImages;

#include <cxxtest/Root.cpp>
