#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat imgo = imread("/home/apulla/Escritorio/PruebaM/Practica2/photo1716652822.jpeg", IMREAD_UNCHANGED);
    Mat imgM = imread("/home/apulla/Escritorio/PruebaM/Practica2/VICTOR_HUGO.png", IMREAD_UNCHANGED);

    if (imgo.empty() || imgM.empty()) {
        cout << "No se pudo cargar una de las imágenes." << endl;
        return -1;
    }

    Mat imgGray;
    cvtColor(imgM, imgGray, COLOR_BGR2GRAY);

    // Calcular la diferencia absoluta entre las dos imágenes
    Mat imgDiff;
    absdiff(imgo, imgM, imgDiff);
    // Convertir la imagen a escala de grises si es necesario
    if (imgo.channels() > 1) {
        cvtColor(imgo, imgo, COLOR_BGR2GRAY);
    }

    // Buscar el centro del círculo mediante el algoritmo de Hough
    Point center;
    int radius;

    // Supongamos que la imagen es cuadrada para simplificar
    int width = imgDiff.cols;
    int height = imgDiff.rows;
    int min_radius = min(width, height) / 8; // Radio mínimo esperado del círculo
    int max_radius = min(width, height) / 4; // Radio máximo esperado del círculo

    // Iterar sobre todos los píxeles
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Supongamos que el círculo es blanco (255) sobre un fondo oscuro (0)
            if (imgDiff.at<uchar>(y, x) == 255) {
                // Este punto podría estar en el borde del círculo
                for (int r = min_radius; r <= max_radius; ++r) {
                    // Verificar si un círculo de radio r centrado en (x, y) cabe completamente en la imagen
                    if (x - r >= 0 && x + r < width && y - r >= 0 && y + r < height) {
                        // Supongamos que el círculo está completamente dentro de la imagen
                        // Calculamos el promedio de los píxeles dentro del círculo para determinar si pertenece al círculo
                        int sum = 0;
                        int count = 0;
                        for (int dy = -r; dy <= r; ++dy) {
                            for (int dx = -r; dx <= r; ++dx) {
                                if (dx * dx + dy * dy <= r * r) {
                                    sum += imgDiff.at<uchar>(y + dy, x + dx);
                                    ++count;
                                }
                            }
                        }
                        int avg = sum / count;
                        // Si el promedio de los píxeles es mayor que cierto umbral (por ejemplo, 200), consideramos este círculo
                        // Aquí puedes ajustar el umbral según tus necesidades
                        if (avg > 200) {
                            center = Point(x, y);
                            radius = r;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Dibujar el círculo detectado en la imagen original
    circle(imgo, center, radius, Scalar(0, 0, 255), 2); // Dibujar el círculo en rojo

    // Mostrar el resultado
    // Mostrar las imágenes
    imshow("Imagen Resultante", imgo);
    imshow("Imagen Diferencia", imgDiff);
    imshow("Imagen Original", imgM);

    waitKey(0); // Esperar a que se presione una tecla antes de cerrar la ventana

    return 0;
}
