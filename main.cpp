#include <iostream>
#include <opencv2/opencv.hpp>

#include "src/inference.h"
#include "src/region_counting.h"
#include "src/channel.h"

#define WIDTH 640
#define HEIGHT 640

using namespace std;
using namespace cv;

void help(char *name)
{
    printf("Run options: \n");
    printf("%s <model.path> <images-dir>\n", name);
    exit(-1);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        help(argv[0]);
    }

    char *modelsBasePath = argv[1];
    char *inputPath = argv[2];

    bool runOnGPU = true;
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    Inference inf(modelsBasePath, cv::Size(WIDTH, HEIGHT), "classes.txt");
    
    std::string input(inputPath);

    testVideos(inf, inputPath, runOnGPU);

    return 0;
}
