#include <iostream>
#include <opencv2/opencv.hpp>

#include "BestBuddiesSimilarity.h"
int main()
{
    auto bbs = BBS();
    std::cout << bbs.compute() << std::endl;

    return 0;
}