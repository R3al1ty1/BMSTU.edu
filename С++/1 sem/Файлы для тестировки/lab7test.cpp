#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

void cin_matrix(double** matrix, int n, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++){
            cin >> matrix[j][i];
        }
    }
}
void cout_matrix(double** matrix, int n, int k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n, k;
    сin >> n;
    cout << endl;
    сin >> k;
    cout << endl;
    double **matrix = new double *[n];/
    for (int i = 0; i < n; i++) matrix[i] = new double[k];
    cin_matrix(matrix, n, k);
    cout_matrix(matrix, n, k);
    for (int i = 0; i < n; i++) delete[]matrix[i];
    delete[] matrix;
}