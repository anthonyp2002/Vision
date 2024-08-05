#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat imgo = imread("PULLA_SÁNCHEZ_ANTHONY_DAMIÁN_2016_6_12_2_5_74.png");
    Mat result = Mat::zeros(imgo.size(), imgo.type());
    int valor1 = 2034;
    int valor2 = 74;

    for(int i = 1; i < result.rows - 1; i++) {
        for(int j = 1; j < result.cols - 1; j++) {
            Vec3b diffPixel = imgo.at<Vec3b>(i,j);
            int canal2 = diffPixel[2];
            if(valor1%canal2 == 0){
                for (int r = i-2; r <= i+2; ++r) {
                    for (int c = j-2; c <= j+2; ++c) {
                        if (r >= 0 && c >= 0) {
                            result.at<Vec3b>(r, c) = imgo.at<Vec3b>(r, c);
                        }
                    }
                }
            }else if(canal2<=74){
                for (int r = i-2; r <= i+2; ++r) {
                    for (int c = j-2; c <= j+2; ++c) {
                        if (r >= 0 && c >= 0 ) {
                            result.at<Vec3b>(r, c) = imgo.at<Vec3b>(r, c);
                        }
                    }
                }
            }
        }
    }

    imshow("Imagen Final", result);
    imshow("Imagen Original", imgo);
    
    waitKey(0);
    return 0;
}