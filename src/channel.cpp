#include "channel.h"


int drawBoxes(cv::Mat frame, int detections, std::vector<Detection> output)
{
    printf("Detect box num: %ld\n", output.size());
    for (int i = 0; i < detections; ++i)
    {
        Detection detection = output[i];

        cv::Rect box = detection.box;
        
        printf("BBox: %d-%d-%d-%d\n",box.x, box.y, box.width, box.height);
        
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
        std::vector<Detection> output = inf.runInference(frame);

        drawBoxesAndCount(frame, output.size(), output);

        cv::imshow("Frame", frame);
        if (cv::waitKey(30) >= 0) break;
    }

    cap.release();
    return 0;
}