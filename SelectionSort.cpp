#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
}

std::vector<int> leer(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<int> arr;
    int value;
    while (infile >> value) {
        arr.push_back(value);
    }
    return arr;
}

void escribir(const std::vector<int>& arr, const std::string& filename) {
    std::ofstream outfile(filename);
    for (const int& value : arr) {
        outfile << value << " ";
    }
}

int main() {
    std::string inputFilename = "SemiOrdenadoDiezMil.txt"; // Cambiar el nombre del archivo según el caso
    std::string outputFilename = "Output.txt";
    
    std::vector<int> arr = leer(inputFilename);

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    selectionSort(arr);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de Selection Sort: " << elapsed.count() << " segundos" << std::endl;

    escribir(arr, outputFilename);

    return 0;
}

