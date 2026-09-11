//Codigo basado en geek for geeks

#include <vector>

using namespace std;

void merge(vector<int>& arreglo, int izq, int medio, int der, vector<int>& temp) {
    int i = izq, j = medio + 1, k = izq;

    while (i <= medio && j <= der) {
        if (arreglo[i] <= arreglo[j]) {
            temp[k++] = arreglo[i++];
        } else {
            temp[k++] = arreglo[j++];
        }
    }

    while (i <= medio) temp[k++] = arreglo[i++];
    while (j <= der) temp[k++] = arreglo[j++];

    for (int p = izq; p <= der; p++) {
        arreglo[p] = temp[p];
    }
}

void mergeSort(vector<int>& arreglo, int izq, int der, vector<int>& temp) {
    if (izq >= der) return;

    int medio = izq + (der - izq) / 2;
    mergeSort(arreglo, izq, medio, temp);
    mergeSort(arreglo, medio + 1, der, temp);
    merge(arreglo, izq, medio, der, temp);
}

vector<int> mergeSortArray(vector<int>& arr) {
    if (arr.size() > 1) {
        // Creamos el buffer temporal UNA sola vez
        vector<int> temp(arr.size());
        mergeSort(arr, 0, arr.size() - 1, temp);
    }
    return arr;
}