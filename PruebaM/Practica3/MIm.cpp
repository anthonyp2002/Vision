#include <iostream>
#include <vector>

using namespace std;

// Función para imprimir la matriz
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

// Función para aplicar la máscara de 5x5 alrededor del punto central
void aplicarMascara(vector<vector<int>>& matriz, int x, int y) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    int inicioFila = max(0, x - 2);
    int finFila = min(filas, x + 3);
    int inicioColumna = max(0, y - 2);
    int finColumna = min(columnas, y + 3);

    for (int i = inicioFila; i < finFila; ++i) {
        for (int j = inicioColumna; j < finColumna; ++j) {
            matriz[i][j] = 1;
        }
    }
}

int main() {
    // Definimos la matriz de 10x10
    vector<vector<int>> matriz(10, vector<int>(10, 0));

    // Colocamos un 1 en el centro de la matriz
    int centroX = 5;
    int centroY = 5;
    matriz[centroX][centroY] = 1;

    cout << "Matriz original:" << endl;
    imprimirMatriz(matriz);

    // Aplicamos la máscara de 5x5 alrededor del punto central
    aplicarMascara(matriz, centroX, centroY);

    cout << "Matriz con máscara aplicada:" << endl;
    imprimirMatriz(matriz);

    return 0;
}
