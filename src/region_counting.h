#ifndef REGION_COUNTING_H
#define REGION_COUNTING_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "inference.h"

using namespace std;
using namespace cv;

struct Region {
    string name;
    vector<Point> polygon;
    Scalar regionColor;
    int count = 0;
};

// Declare global vector of counting regions
extern vector<Region> countingRegions;

// Function declarations
bool isInsideRegion(Point point, const vector<Point>& polygon);
int drawBoxesAndCount(cv::Mat frame, int detections, std::vector<Detection> output);

#endif  // REGION_COUNTING_H
