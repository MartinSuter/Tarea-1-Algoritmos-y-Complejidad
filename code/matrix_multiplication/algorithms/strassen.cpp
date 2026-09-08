#include <vector>

using namespace std;

vector<vector<int>> addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B){

    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){

            C[i][j] = A[i][j] + B[i][j];

        }
    }

    return C;

}

vector<vector<int>> subMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B){

    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n,0));

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){

            C[i][j] = A[i][j] - B[i][j];

            
        }
    }

    return C;
}

vector<vector<int>> naiveFallback(const vector<vector<int>>& A, const vector<vector<int>>& B){

    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n,0));

    for(int i = 0; i < n; i++){

        for(int k = 0; k < n; ++k){

            for(int j = 0; j < n; ++j){

                C[i][j] += A[i][k] * B[k][j];

            }
        }
    }

    return C;
}

vector<vector<int>> strassenMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B){

    int n = A.size();

    if(n <= 64){

        return naiveFallback(A, B);
    }

    int newSize = n / 2;

    vector<int> inner(newSize);
    vector<vector<int>>
        A11(newSize, inner), A12(newSize, inner), A21(newSize, inner), A22(newSize, inner),
        B11(newSize, inner), B12(newSize, inner), B21(newSize, inner), B22(newSize, inner);

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

    vector<vector<int>> M1 = strassenMultiplication(addMatrix(A11, A22), addMatrix(B11, B22));
    vector<vector<int>> M2 = strassenMultiplication(addMatrix(A21, A22), B11);
    vector<vector<int>> M3 = strassenMultiplication(A11, subMatrix(B12, B22));
    vector<vector<int>> M4 = strassenMultiplication(A22, subMatrix(B21, B11));
    vector<vector<int>> M5 = strassenMultiplication(addMatrix(A11, A12), B22);
    vector<vector<int>> M6 = strassenMultiplication(subMatrix(A21, A11), addMatrix(B11, B12));
    vector<vector<int>> M7 = strassenMultiplication(subMatrix(A12, A22), addMatrix(B21, B22));

    vector<vector<int>> C11 = addMatrix(subMatrix(addMatrix(M1, M4), M5), M7);
    vector<vector<int>> C12 = addMatrix(M3, M5);
    vector<vector<int>> C21 = addMatrix(M2, M4);
    vector<vector<int>> C22 = addMatrix(addMatrix(subMatrix(M1, M2), M3), M6);

    vector<vector<int>> C(n, vector<int>(n, 0));

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