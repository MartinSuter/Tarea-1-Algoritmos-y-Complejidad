#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <sys/resource.h> 

using namespace std;

vector<vector<int>> naiveMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B);
vector<vector<int>> strassenMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B);

long getPeakMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; 
}

vector<vector<int>> readMatrix(const string& filepath, int n) {
    vector<vector<int>> mat(n, vector<int>(n));
    ifstream file(filepath);
    
    if (!file.is_open()) return {}; 

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> mat[i][j];
        }
    }
    return mat;
}

void writeMatrix(const string& filepath, const vector<vector<int>>& mat) {
    ofstream file(filepath);
    for (const auto& row : mat) {
        for (size_t j = 0; j < row.size(); ++j) {
            file << row[j] << (j + 1 == row.size() ? "" : " ");
        }
        file << "\n";
    }
}

int main() {
    string inputDir = "data/matrix_input";
    string outputDir = "data/matrix_output";
    string measurementsDir = "data/measurements";

    ofstream csvFile(measurementsDir + "/matrix_measurements.csv");
    if (!csvFile.is_open()) {
        cout << "Error: No se pudo crear el archivo CSV. Asegúrate de que exista la carpeta data/measurements/" << endl;
        return 1;
    }
    
    csvFile << "algorithm,n,type,domain,sample,time_ms,memory_kb\n";

    vector<int> sizes = {16, 64, 256, 1024};
    vector<string> types = {"dispersa", "diagonal", "densa"};
    vector<string> domains = {"D0", "D10"};
    vector<string> samples = {"a", "b", "c"};
    vector<string> algorithms = {"naive", "strassen"};

    for (int n : sizes) {
        for (const string& t : types) {
            for (const string& d : domains) {
                for (const string& m : samples) {
                    string baseName = to_string(n) + "_" + t + "_" + d + "_" + m;
                    string path1 = inputDir + "/" + baseName + "_1.txt";
                    string path2 = inputDir + "/" + baseName + "_2.txt";

                    vector<vector<int>> A = readMatrix(path1, n);
                    vector<vector<int>> B = readMatrix(path2, n);

                    if (A.empty()) continue;

                    cout << "Procesando: " << baseName << "..." << endl;

                    for (const string& algo : algorithms) {
                        auto start = chrono::high_resolution_clock::now();
                        
                        vector<vector<int>> C;
                        if (algo == "naive") {
                            C = naiveMultiplication(A, B);
                        } else if (algo == "strassen") {
                            C = strassenMultiplication(A, B);
                        }

                        auto end = chrono::high_resolution_clock::now();
                        double time_ms = chrono::duration<double, milli>(end - start).count();
                        long memory_kb = getPeakMemoryKB();

                        csvFile << algo << "," << n << "," << t << "," << d << "," << m << ","
                                << time_ms << "," << memory_kb << "\n";

                        if (algo == "naive") {
                            string outPath = outputDir + "/" + baseName + "_out.txt";
                            writeMatrix(outPath, C);
                        }
                    }
                }
            }
        }
    }

    csvFile.close();
    cout << "\n¡Mediciones de matrices finalizadas con éxito!" << endl;
    return 0;
}