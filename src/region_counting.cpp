#include "region_counting.h"

vector<Region> countingRegions = {
    // {"Region 1", {Point(50, 80), Point(250, 20), Point(450, 80), Point(400, 350), Point(100, 350)}, Scalar(255, 42, 4)},
    {"Region 2", {Point(200, 250), Point(440, 250), Point(440, 550), Point(200, 550)}, Scalar(37, 255, 225)}
    // {"Region 2", {Point(200, 200), Point(1000, 200), Point(1000, 600), Point(200, 600)}, Scalar(37, 255, 225)}
};

bool isInsideRegion(Point point, const vector<Point> &polygon)
{
    return pointPolygonTest(polygon, point, false) >= 0;
}

// int drawBoxesAndCount(cv::Mat frame, int detections, std::vector<Detection> output)
// {
//     printf("Detect box num: %ld\n", output.size());

//     for (int i = 0; i < detections; ++i)
//     {
//         Detection detection = output[i];
//         cv::Rect box = detection.box;
//         cv::Scalar color = detection.color;

//         cv::rectangle(frame, box, color, 2);
//         Point bboxCenter = Point((box.x + box.width / 2), (box.y + box.height / 2));

//         std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
//         cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2);

//         for (auto& region : countingRegions) {
//             if (isInsideRegion(bboxCenter, region.polygon)) {
//                 region.count++;
//             }
//         }
//     }

//     for (const auto& region : countingRegions) {
//         cv::polylines(frame, region.polygon, true, region.regionColor, 2);

//         Moments moments = cv::moments(region.polygon);
//         Point centroid(moments.m10 / moments.m00, moments.m01 / moments.m00);

//         std::string countLabel = "Count: " + std::to_string(region.count);
//         cv::putText(frame, countLabel, centroid, cv::FONT_HERSHEY_SIMPLEX, 0.7, region.regionColor, 2);
//     }

//     float scale = 0.8;
//     cv::resize(frame, frame, cv::Size(frame.cols * scale, frame.rows * scale));

//     for (auto& region : countingRegions) {
//         region.count = 0;
//     }

//     return 0;
// }

int drawBoxesAndCount(cv::Mat frame, int detections, std::vector<Detection> output)
{
    // printf("Detect box num: %ld\n", output.size());

    for (int i = 0; i < detections; ++i)
    {
        Detection detection = output[i];
        cv::Rect box = detection.box;
        Point bboxCenter = Point((box.x + box.width / 2), (box.y + box.height / 2));

        if (detection.className == "person")
        {
            bool isInRegion = false;

            for (auto &region : countingRegions)
            {
                if (isInsideRegion(bboxCenter, region.polygon))
                {
                    region.count++;
                    isInRegion = true;
                }
            }
            if (isInRegion)
            {
                cv::Scalar color = detection.color;
                cv::rectangle(frame, box, color, 2);

                std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
                cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2);
            }
        }
    }

    for (const auto &region : countingRegions)
    {
        cv::polylines(frame, region.polygon, true, region.regionColor, 2);

        Moments moments = cv::moments(region.polygon);
        Point centroid(moments.m10 / moments.m00, moments.m01 / moments.m00);

        std::string countLabel = "Count: " + std::to_string(region.count);
        cv::putText(frame, countLabel, centroid, cv::FONT_HERSHEY_SIMPLEX, 0.7, region.regionColor, 2);

        if (region.count == 0)
        {
            cv::Scalar redRegionColor(0, 0, 255);
            std::string Wanring = "Wanring: " + std::to_string(region.count);
            int frameWidth = frame.cols;
            int frameHeight = frame.rows;
            cv::Point bottomLeft(frameWidth - 100, frameHeight - 10); // Adjust (100, 10) as needed
            cv::putText(frame, Wanring, bottomLeft, cv::FONT_HERSHEY_SIMPLEX, 0.7, redRegionColor, 2);
        }
    }

    float scale = 0.8;
    cv::resize(frame, frame, cv::Size(frame.cols * scale, frame.rows * scale));

    for (auto &region : countingRegions)
    {
        region.count = 0;
    }

    return 0;
}
