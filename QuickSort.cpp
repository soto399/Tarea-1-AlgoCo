#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para hacer el intercambio de dos elementos
void cambio(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Función de partición para Quick Sort
int particion(vector<int>& arreglo, int menor, int mayor) {
    int pivot = arreglo[mayor]; // Tomamos el último elemento como pivote
    int i = menor - 1;

    for (int j = menor; j <= mayor - 1; j++) {
        if (arreglo[j] < pivot) {
            i++;
            cambio(arreglo[i], arreglo[j]);
        }
    }
    cambio(arreglo[i + 1], arreglo[mayor]);
    return i + 1;
}

// Función principal de Quick Sort
void quickSort(vector<int>& arreglo, int menor, int mayor) {
    if (menor < mayor) {
        int pi = particion(arreglo, menor, mayor);

        // Ordenar los elementos antes y después de la partición
        quickSort(arreglo, menor, pi - 1);
        quickSort(arreglo, pi + 1, mayor);
    }
}

int main() {
    // Abrir archivo de entrada
    ifstream inputFile("SemiOrdenadoCienMil.txt");
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo input.txt" << endl;
        return 1;
    }

    // Leer los números del archivo
    vector<int> arreglo;
    int num;
    while (inputFile >> num) {
        arreglo.push_back(num);
    }
    inputFile.close();

    int tamaño = arreglo.size();

    // Medición del tiempo de ejecución
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort(arreglo, 0, tamaño - 1);
    high_resolution_clock::time_point stop = high_resolution_clock::now();

    std::chrono::microseconds duration = duration_cast<std::chrono::microseconds>(stop - start);

    // Escribir el arreglo ordenado en el archivo de salida
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "No se pudo abrir el archivo output.txt" << endl;
        return 1;
    }

    for (int i = 0; i < tamaño; i++) {
        outputFile << arreglo[i] << " ";
    }
    outputFile.close();

    cout << "Tiempo de Quick Sort: " << duration.count() << " microsegundos" << endl;

    return 0;
}
