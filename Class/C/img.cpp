#include "imagen.hpp"

Imagen::Imagen(int codigo){
    this->codigo = codigo;
}

void Imagen::saludo(int conteo){
    for(int i = 0; i<conteo;i++){
        cout << "Hola desde C++!" << endl;
    }
}