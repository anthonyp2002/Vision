

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <cstring>
#include <fstream>
#include <sstream>

#include <cmath> 
#include <random> 

#include <opencv2/core/core.hpp> // Contiene las definiciones de imagen (Matriz que representa la imagen y su operaciones)
#include <opencv2/video/video.hpp> // Permite reproducir videos de archivos almacenados en disco o en la nube
#include <opencv2/highgui/highgui.hpp> // Permite crear las interfaces gráficas básicas
#include <opencv2/videoio/videoio.hpp> // Permite grabar videos en diferentes formatos
#include <opencv2/imgproc/imgproc.hpp> // Incluye métodos para pre-procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Incluye funciones para leer y trabajar con distintos formatos de imágenes
#include <opencv2/objdetect/objdetect.hpp>

#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;
using namespace ml;



int main(int argc, char *argv[]){

    Mat imagen = imread("PeatonesTwo.jpg");
    
    Mat imgDecimal;
    Mat gx, gy;
    Mat magnitud, angulo;


    imagen.convertTo(imgDecimal, CV_32F, 1.0/255.0);

    Sobel(imgDecimal, gx, CV_32F, 0, 1, 5);
    Sobel(imgDecimal, gy, CV_32F, 1, 0, 5);

    cartToPolar(gx, gy, magnitud, angulo, true);

    HOGDescriptor hog(Size(64,128), Size(16,16), Size(8,8), Size(8,8), 9); 

    Mat deteccion = imagen.clone();
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    vector<Rect> detecciones;

    hog.detectMultiScale(imagen, detecciones, 0, Size(8,8), Size(8,8), 1.05, 2, false);

    cout << "Detecciones: " << detecciones.size() << endl;

    Rect r;

    for(int i=0;i<detecciones.size();i++){
        r = detecciones[i];

        rectangle(deteccion, r.tl(), r.br(), Scalar(7,7,237), 2);
    }

    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("Detecciones", WINDOW_AUTOSIZE);

    imshow("Imagen", imagen);
    imshow("Detecciones", deteccion);

    waitKey(0);

    destroyAllWindows();    

    return 0;
}