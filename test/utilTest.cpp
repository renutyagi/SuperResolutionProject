#include "../src/util.h"

void testPrintVector()
{
    int valI[] = {1, 2, 3, 4};
    float valF[] = {1.231, 2.123, 3.124, 4.234} ;
    double valD[] = {1.231, 2.123, 3.124, 4.234};

    std::vector<int> intVect(valI, valI + 4);
    std::vector<float> floatVect(valF, valF + 4);
    std::vector<double> doubleVect(valD, valD + 4);

    util::printVector<int>(intVect);
    util::printVector<float>(floatVect);
    util::printVector<double>(doubleVect);
}

int main (int argc, char const* argv[])
{
    testPrintVector();

    return 0;
}
