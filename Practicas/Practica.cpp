#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Cargar la imagen original
    cv::Mat imagen = cv::imread("/home/apulla/Descargas/Lady.png");
    if (imagen.empty()) {
        std::cerr << "Error al cargar la imagen" << std::endl;
        return -1;
    }

    // Convertir a escala de grises
    cv::Mat imagenGris;
    cv::Mat result,masInver;
    cv::cvtColor(imagen, imagenGris, cv::COLOR_BGR2GRAY);
    cv::threshold(imagenGris,result,185,255,cv::THRESH_BINARY);
    cv::bitwise_not(result,masInver);
    // Aplicar un umbral

    // Mostrar la imagen original y la máscara
    cv::imshow("Imagen Original", imagen);
    cv::imshow("Máscara", imagenGris);
    cv::imshow("Máscarasss", masInver);

    // Guardar la máscara
    cv::imwrite("MascaraAnti.jpg", masInver);

    // Esperar hasta que se presione una tecla
    cv::waitKey(0);

    return 0;
}
