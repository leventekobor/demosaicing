#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


void color(cv::Mat &src){
    int green = 0;
    int blue = 0;
    int red = 0;
    for (int i = 1; i < src.rows-1; ++i) {
        for (int j = 1; j < src.cols-1; ++j) {
            cv::Vec3b &pixel = src.at<cv::Vec3b>(i, j);
            if(pixel.val[1] == 0){
                green++;
                cv::Vec3b &leftNeighbour = src.at<cv::Vec3b>(i, j - 1);
                cv::Vec3b &rightNeighbour = src.at<cv::Vec3b>(i, j + 1);
                cv::Vec3b &upperNeighbour = src.at<cv::Vec3b>(i - 1, j);
                cv::Vec3b &lowerNeighbour = src.at<cv::Vec3b>(i + 1, j);
                pixel.val[1] = (
                        leftNeighbour.val[1] +
                        rightNeighbour.val[1] +
                        upperNeighbour.val[1] +
                        lowerNeighbour.val[1]
                        ) / 4;
            }
            if(pixel.val[0] == 0){
                blue++;
                cv::Vec3b &upperLeftNeighbour = src.at<cv::Vec3b>(i - 1, j - 1);
                cv::Vec3b &upperRightNeighbour = src.at<cv::Vec3b>(i - 1, j + 1);
                cv::Vec3b &lowerLeftNeighbour = src.at<cv::Vec3b>(i + 1, j - 1);
                cv::Vec3b &lowerRightNeighbour = src.at<cv::Vec3b>(i + 1, j + 1);
                pixel.val[0] = (
                                       upperLeftNeighbour.val[1] +
                                       upperRightNeighbour.val[1] +
                                       lowerLeftNeighbour.val[1] +
                                       lowerRightNeighbour.val[1]
                               ) / 4;
            }
            if (pixel.val[2] == 0){
                red++;
                cv::Vec3b &upperLeftNeighbour = src.at<cv::Vec3b>(i - 1, j - 1);
                cv::Vec3b &upperRightNeighbour = src.at<cv::Vec3b>(i - 1, j + 1);
                cv::Vec3b &lowerLeftNeighbour = src.at<cv::Vec3b>(i + 1, j - 1);
                cv::Vec3b &lowerRightNeighbour = src.at<cv::Vec3b>(i + 1, j + 1);
                pixel.val[2] = (
                                       upperLeftNeighbour.val[1] +
                                       upperRightNeighbour.val[1] +
                                       lowerLeftNeighbour.val[1] +
                                       lowerRightNeighbour.val[1]
                               ) / 4;
            }
        }
    }

    std::cout << "green: " << green << " blue: " << blue << " red: " << red << std::endl;
}



int main()
{
    cv::Mat src = cv::imread("/Users/mac/Documents/img/lily-raw.png");

    color(src);

    //std::cout << src;
    cv::imshow("src", src);
    //cv::imwrite("/Users/mac/Documents/img/lily-raw-green.png", src);

    cv::waitKey(0);
    return 0;
}

