#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat imgo = imread("CHARLES_BRONSON(1).png");
    Mat imgM = imread("CHARLES_BRONSON.png");

    if (imgo.empty() || imgM.empty()) {
        cout << "No se pudo cargar una de las imágenes." << endl;
        return -1;
    }

    // Convertir la imagen original a escala de grises
    Mat imgoGray;
    cvtColor(imgo, imgoGray, COLOR_BGR2GRAY);

    // Calcular la diferencia absoluta entre las dos imágenes
    Mat imgDiff;
    absdiff(imgo, imgM, imgDiff);


    Mat re = Mat::zeros(imgo.size(), imgo.type());

    for(int i = 1; i < re.rows - 1; i++) {
            for(int j = 1; j < re.cols - 1; j++) {
                Vec3b diffPixel = imgDiff.at<Vec3b>(i,j);
                Vec3b diffP = re.at<Vec3b>(i,j);
                Vec3b origImg = imgo.at<Vec3b>(i,j);
                Vec3b imgGris = imgoGray.at<Vec3b>(i,j);
                
                int sumP = diffP[0] + diffP[1] + diffP[2];
                int sumPD = diffPixel[0] + diffPixel[1] + diffPixel[2];

                if(sumP == sumPD) {
                    bool unoIzquierda = false;
                    bool unoDerecha = false;

                    for (int k = 0; k < j; ++k) {
                    Vec3b BP = imgDiff.at<Vec3b>(i,k);
                    int sBP = BP[0] + BP[1] + BP[2];
                    if (sBP != 0) {
                            unoIzquierda = true;
                            break;
                        }
                    }

                    for (int k = j + 1; k < imgDiff.cols; ++k) {
                    Vec3b DP = imgDiff.at<Vec3b>(i,k);
                    int sDP = DP[0] + DP[1] + DP[2];
                        if (sDP != 0) {
                            unoDerecha = true;
                            break;
                        }
                    }

                    if (unoIzquierda && unoDerecha) {
                        uchar grayPixel = imgo.at<uchar>(i, j);
                        re.at<Vec3b>(i,j) = origImg;
                    } else {
                        uchar pix = imgoGray.at<uchar>(i, j);
                        re.at<Vec3b>(i,j) = Vec3b(0, 0, 0);
                    }
                    
                }else {
                    re.at<Vec3b>(i, j) = origImg;
                }
            }
        }


    // Crear una imagen de resultado en color (tres canales)
    Mat result = Mat::zeros(imgo.size(), imgo.type());


    // Iterar sobre los píxeles para reemplazar los píxeles negros
    for (int y = 0; y < re.rows; y++) {
        for (int x = 0; x < re.cols; x++) {
            Vec3b diffPixel = re.at<Vec3b>(y, x);
            Vec3b origPixel = imgo.at<Vec3b>(y, x);
            if (diffPixel[0] == 0 && diffPixel[1] == 0 && diffPixel[2] == 0) {
                uchar grayPixel = imgoGray.at<uchar>(y, x);
                result.at<Vec3b>(y, x) = Vec3b(grayPixel, grayPixel, grayPixel);
            } else {
                // Mantener el píxel original en color
                result.at<Vec3b>(y, x) = origPixel;
            }
        }
    }

    // Mostrar las imágenes
    imshow("Resultado", result);
    imshow("Imagen Original", imgo);
    imshow("Imagen A Modificar", imgM);
    imshow("Imagen Diferencia", imgDiff);
    imshow("Imagen asada", re);




    waitKey(0);
    return 0;
}
