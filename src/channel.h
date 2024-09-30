#ifndef CHANNEL_H
#define CHANNEL_H

#include "inference.h"
#include "region_counting.h"


int drawBoxes(cv::Mat frame, int detections, std::vector<Detection> output);
int testImages(Inference inf, char *imagesBasePath, bool runOnGPU);
int testVideos(Inference inf, char *videoPath, bool runOnGPU);

#endif  // CHANNEL_H
