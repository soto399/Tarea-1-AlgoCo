#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>    // Para medir el tiempo de ejecución

using namespace std;
using namespace std::chrono;

// Función para multiplicar dos matrices de forma iterativa
vector<vector<int> > Multiplicacion(const vector<vector<int> >& A, const vector<vector<int> >& B, int n, int m, int p) {
    vector<vector<int> > result(n, vector<int>(p, 0));

    // Algoritmo iterativo cúbico tradicional O(n * m * p)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Función para leer una matriz desde un archivo
vector<vector<int> > Leer(ifstream& file, int rows, int cols) {
    vector<vector<int> > matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }
    return matrix;
}

int main() {
    // Abrir archivo de entrada que contiene las matrices
    ifstream inputFile("MatricesCuadradasSetecientos.txt"); // Cambiar si se usan otras matrices
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo matrices.txt" << endl;
        return 1;
    }

    // Leer dimensiones de las dos matrices
    int n, m, p;
    inputFile >> n >> m >> p;

    // Leer las dos matrices
    vector<vector<int> > A = Leer(inputFile, n, m); 
    vector<vector<int> > B = Leer(inputFile, m, p);
    inputFile.close();

    // Medir el tiempo de ejecución de la multiplicación de matrices
    high_resolution_clock::time_point start = high_resolution_clock::now();

    // Multiplicar matrices
    vector<vector<int> > result = Multiplicacion(A, B, n, m, p);

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    std::chrono::microseconds duration = duration_cast<std::chrono::microseconds>(stop - start);

    // Escribir el resultado en un archivo de salida
    ofstream outputFile("resultado.txt");
    if (!outputFile) {
        cerr << "No se pudo abrir el archivo resultado.txt" << endl;
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            outputFile << result[i][j] << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    
    // Mostrar el tiempo de ejecución
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    return 0;
}
