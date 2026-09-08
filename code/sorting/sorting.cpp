#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <sys/resource.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

vector<int> sortArray(vector<int>& arr);     
vector<int> mergeSortArray(vector<int>& arr);  
vector<int> quickSortArray(vector<int>& arr);  
vector<int> patienceSort(vector<int>& arr);

long getPeakMemoryKB(){

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;

}

vector<int> readArray(const string& filepath){

    vector<int> arr;
    ifstream file(filepath);
    int val;
    while (file >> val) {

        arr.push_back(val);
    
    }
    return arr;
}

void writeArray(const string& filepath, const vector<int>& arr) {
    
    ofstream file(filepath);
    
    for (size_t i = 0; i < arr.size(); ++i) {
    
        file << arr[i] << (i + 1 == arr.size() ? "" : " ");
    
    }
    
    file << "\n";
}

int main() {

    string inputDir = "data/array_input";
    string outputDir = "data/array_output";
    string measurementsDir = "data/measurements";

    fs::create_directories(outputDir);
    fs::create_directories(measurementsDir);

    ofstream csvFile(measurementsDir + "/sorting_measurements.csv");
    csvFile << "algorithm,n,type,domain,sample,time_ms,memory_kb\n";

    vector<int> sizes = {10, 1000, 100000, 10000000};
    vector<string> types = {"ascendente", "descendente", "aleatorio"};
    vector<string> domains = {"D1", "D7"};
    vector<string> samples = {"a", "b", "c"};
    vector<string> algorithms = {"std_sort", "mergesort", "quicksort", "patiencesort"};

    for (int n : sizes) {
        for (const auto& t : types) {
            for (const auto& d : domains) {
                for (const auto& m : samples) {
                    string filename = to_string(n) + "_" + t + "_" + d + "_" + m + ".txt";
                    string inputPath = inputDir + "/" + filename;

                    if (!fs::exists(inputPath)) continue;

                    cout << "Procesando: " << filename << "..." << endl;
                    vector<int> baseArr = readArray(inputPath);

                    for (const auto& algo : algorithms) {
                        vector<int> arrCopy = baseArr;

                        auto start = chrono::high_resolution_clock::now();

                        if (algo == "std_sort") sortArray(arrCopy);
                        else if (algo == "mergesort") mergeSortArray(arrCopy);
                        else if (algo == "quicksort") quickSortArray(arrCopy);
                        else if (algo == "patiencesort") patienceSort(arrCopy);

                        auto end = chrono::high_resolution_clock::now();
                        double time_ms = chrono::duration<double, milli>(end - start).count();
                        long memory_kb = getPeakMemoryKB();

                        csvFile << algo << "," << n << "," << t << "," << d << "," << m << ","
                                << time_ms << "," << memory_kb << "\n";

                        if (algo == "std_sort") {
                            string outPath = outputDir + "/" + to_string(n) + "_" + t + "_" + d + "_" + m + "_out.txt";
                            writeArray(outPath, arrCopy);
                        }
                    }
                }
            }
        }
    }

    csvFile.close();
    cout << "\n¡Mediciones finalizadas! Resultados en sorting_measurements.csv" << endl;
    return 0;
}