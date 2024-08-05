// En lugar de usar la sentencia imort en c++/c se usa include
#include <iostream>//las lirberias de sistema van entre simbolos de <>
#include <cstdlib>

#include <cstring>
#include <fstream>


using namespace std;

class Imagen{
    private: 
        int codigo;

    public: 
        Imagen(int);
        void saludo(int = 7);
};