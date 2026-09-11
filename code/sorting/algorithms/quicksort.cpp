//Codigo basado en geek for geeks

#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

void quickSort(vector<int>& arr, int menor, int mayor) {

    if (menor >= mayor) return;

    int pivot = arr[menor + rand() % (mayor - menor + 1)];
    int i = menor;
    int j = mayor;

    while (i <= j) {

        while (arr[i] < pivot) i++;

        while (arr[j] > pivot) j--;
        
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    quickSort(arr, menor, j);
    quickSort(arr, i, mayor);
}

vector<int> quickSortArray(vector<int>& arr) {
    if (arr.size() > 1) {
        quickSort(arr, 0, arr.size() - 1);
    }
    return arr;
}