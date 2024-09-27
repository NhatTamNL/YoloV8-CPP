#include <iostream>
#include <vector>
#include <getopt.h>

#include <opencv2/opencv.hpp>
#include "src/inference.h"

using namespace std;
using namespace cv;


#define WIDTH 640
#define HEIGHT 640

void help(char *name)
{
    printf("Run options: \n");
    printf("%s <model.path> <images-dir>\n", name);
    exit(-1);
}

int drawBoxes(cv::Mat frame, int detections, std::vector<Detection> output)
{
    printf("Detect box num: %ld\n", output.size());
    for (int i = 0; i < detections; ++i)
    {
        Detection detection = output[i];

        cv::Rect box = detection.box;
        cv::Scalar color = detection.color;

        cv::rectangle(frame, box, color, 2);

        std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
        cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
        cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

        cv::rectangle(frame, textBox, color, cv::FILLED);
        cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
    }

    float scale = 0.8;
    cv::resize(frame, frame, cv::Size(frame.cols*scale, frame.rows*scale));
    return 0;
} 

int testVideos(Inference inf, char *videoPath, bool runOnGPU)
{
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened())
    {
        std::cerr << "Error opening video file: " << videoPath << std::endl;
        return -1;
    }
    cv::Mat frame;
    while (cap.read(frame))
    {
        if (frame.empty())
        {
            std::cerr << "End of video or error reading frame." << std::endl;
            break;
        }
        std::vector<Detection> output = inf.runInference(frame);
        int detections = output.size();
        std::cout << "Number of detections: " << detections << std::endl;

        drawBoxes(frame, detections, output);
        output.clear();

        cv::imshow("Inference", frame);
        if (cv::waitKey(1) == 'q')
        {
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}


int testImages(Inference inf, char *imagesBasePath, bool runOnGPU)
{
    
    std::vector<std::string> imageNames;
    imageNames.push_back(imagesBasePath);

    for (int i = 0; i < imageNames.size(); ++i)
    {
        cv::Mat frame = cv::imread(imageNames[i]);

        std::vector<Detection> output = inf.runInference(frame);

        int detections = output.size();
        std::cout << "Number of detections:" << detections << std::endl;

        drawBoxes(frame, detections, output);

        output.clear();
        
        cv::imshow("Inference", frame);
        cv::waitKey(-1);
    }
    return 0;
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
    
    if (input.find(".mp4") != std::string::npos || input.find(".avi") != std::string::npos)
    {
        testVideos(inf, inputPath, runOnGPU);
    }
    else
    {
        testImages(inf, inputPath, runOnGPU);
    }

}
