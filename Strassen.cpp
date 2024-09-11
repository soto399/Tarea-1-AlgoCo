#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para sumar matrices
vector<vector<int> > Sumar(const vector<vector<int> >& A, const vector<vector<int> >& B, int size) {
    vector<vector<int> > C(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar matrices
vector<vector<int> > Restar(const vector<vector<int> >& A, const vector<vector<int> >& B, int size) {
    vector<vector<int> > C(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Algoritmo de Strassen para multiplicar matrices
vector<vector<int> > Strassen(const vector<vector<int> >& A, const vector<vector<int> >& B, int size) {
    if (size == 1) {
        vector<vector<int> > C(1, vector<int>(1, A[0][0] * B[0][0]));
        return C;
    }

    int newSize = size / 2;
    vector<vector<int> > A11(newSize, vector<int>(newSize));
    vector<vector<int> > A12(newSize, vector<int>(newSize));
    vector<vector<int> > A21(newSize, vector<int>(newSize));
    vector<vector<int> > A22(newSize, vector<int>(newSize));
    
    vector<vector<int> > B11(newSize, vector<int>(newSize));
    vector<vector<int> > B12(newSize, vector<int>(newSize));
    vector<vector<int> > B21(newSize, vector<int>(newSize));
    vector<vector<int> > B22(newSize, vector<int>(newSize));
    
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    vector<vector<int> > M1 = Strassen(Sumar(A11, A22, newSize), Sumar(B11, B22, newSize), newSize);
    vector<vector<int> > M2 = Strassen(Sumar(A21, A22, newSize), B11, newSize);
    vector<vector<int> > M3 = Strassen(A11, Restar(B12, B22, newSize), newSize);
    vector<vector<int> > M4 = Strassen(A22, Restar(B21, B11, newSize), newSize);
    vector<vector<int> > M5 = Strassen(Sumar(A11, A12, newSize), B22, newSize);
    vector<vector<int> > M6 = Strassen(Restar(A21, A11, newSize), Sumar(B11, B12, newSize), newSize);
    vector<vector<int> > M7 = Strassen(Restar(A12, A22, newSize), Sumar(B21, B22, newSize), newSize);

    vector<vector<int> > C11 = Sumar(Restar(Sumar(M1, M4, newSize), M5, newSize), M7, newSize);
    vector<vector<int> > C12 = Sumar(M3, M5, newSize);
    vector<vector<int> > C21 = Sumar(M2, M4, newSize);
    vector<vector<int> > C22 = Sumar(Restar(Sumar(M1, M3, newSize), M2, newSize), M6, newSize);

    vector<vector<int> > C(size, vector<int>(size));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
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

// Función para ajustar el tamaño de la matriz a la potencia de 2 más cercana
vector<vector<int> > AjustarMatriz(const vector<vector<int> >& matrix, int newSize) {
    int originalSize = matrix.size();
    vector<vector<int> > newMatrix(newSize, vector<int>(newSize, 0));
    for (int i = 0; i < originalSize; i++) {
        for (int j = 0; j < originalSize; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    return newMatrix;
}

int main() {
    // Abrir archivo de entrada que contiene las matrices
    ifstream inputFile("MatricesCuadradasCuatrocientos.txt"); // Cambiar si se usan otras matrices
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

    // Asegurarse de que las matrices son de tamaño 2^k x 2^k
    int newSize = 1;
    while (newSize < n || newSize < p || newSize < m) {
        newSize *= 2;
    }

    vector<vector<int> > A_adjusted = AjustarMatriz(A, newSize);
    vector<vector<int> > B_adjusted = AjustarMatriz(B, newSize);

    // Medir el tiempo de ejecución del algoritmo de Strassen
    high_resolution_clock::time_point start = high_resolution_clock::now();

    // Multiplicar matrices usando Strassen
    vector<vector<int> > result_adjusted = Strassen(A_adjusted, B_adjusted, newSize);

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    std::chrono::microseconds duration = duration_cast<std::chrono::microseconds>(stop - start);

    // Ajustar el resultado al tamaño original
    vector<vector<int> > result(n, vector<int>(p));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            result[i][j] = result_adjusted[i][j];
        }
    }

    // Escribir el resultado en un archivo de salida
    ofstream outputFile("resultado_strassen.txt");
    if (!outputFile) {
        cerr << "No se pudo abrir el archivo resultado_strassen.txt" << endl;
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
    cout << "Tiempo de ejecución (Strassen): " << duration.count() << " microsegundos" << endl;

    return 0;
}
