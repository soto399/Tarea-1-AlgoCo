#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función de mezcla de dos subarreglos
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    // Copiando los datos a los subarrays temporales
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Mezclando los subarrays temporales en arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiando los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiando los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función principal de Merge Sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main() {
    // Abrir archivo de entrada
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo input.txt" << endl;
        return 1;
    }

    // Leer los números del archivo
    vector<int> arr;
    int num;
    while (inputFile >> num) {
        arr.push_back(num);
    }
    inputFile.close();

    int arr_size = arr.size();

    // Medición del tiempo de ejecución
    std::chrono::high_resolution_clock::time_point start = high_resolution_clock::now();
    mergeSort(arr, 0, arr_size - 1);
    high_resolution_clock::time_point stop = high_resolution_clock::now();

    std::chrono::microseconds duration = duration_cast<std::chrono::microseconds>(stop - start);

    // Escribir el arreglo ordenado en el archivo de salida
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "No se pudo abrir el archivo output.txt" << endl;
        return 1;
    }

    for (int i = 0; i < arr_size; i++) {
        outputFile << arr[i] << " ";
    }
    outputFile.close();

    cout << "Tiempo de Merge Sort: " << duration.count() << " microsegundos" << endl;

    return 0;
}
