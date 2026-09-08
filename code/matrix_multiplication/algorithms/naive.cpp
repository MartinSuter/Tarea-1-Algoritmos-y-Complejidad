#include <vector>

using namespace std;

vector<vector<int>> naiveMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B){

    int  n = A.size();
    vector<vector<int>> C(n, vector<int>(n,0));

    for(int i = 0; i < n; i++){

        for(int k = 0; k < n; k++){

            for(int j = 0; j < n; ++j){

                C[i][j] += A[i][k] * B[k][j];

            }
        }
    }

    return C;
}