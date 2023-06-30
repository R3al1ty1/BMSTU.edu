#include <iostream>
#include <cmath>
#include <iomanip>
#include "PrintMatrix.h"
using namespace std;
typedef double (*TPF)(double);
void FillMatrix(double** A, int nrows, int ncols);
double fact(double x);
int main() {
    int point;
    int type;
    int n = 0;
    cout << "Какого размера создать матрицу? (пример: 3 3)" << '\n';
    int nrows, ncols;
    cin >> nrows >> ncols;
    cout << "Введите количество знаков после запятой" << '\n';
    cin >> point; //nrows ncols
    cout << "В каком виде вывести матрицу?" << '\n';
    cout << "0 - вывести в обычном виде, 1 - вывести в научном" << '\n';
    do
        cin >> type;
    while ((type != 0) && (type != 1));
    if (type == 1) {
        cout << scientific << setprecision(point);
        n = 10 + point;
    } else {
        cout << fixed << setprecision(point);
        n = 4 + point;
    }
    double **A = new double *[nrows];
    for (int i = 0; i < nrows; i++)
        A[i] = new double[ncols];
    FillMatrix(A, nrows, ncols);
    PrintMatrix(A, nrows, ncols, n, type, point);
    double B[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            B[i][j] = i * 10 + j;
        }
    }
    int rowB = 10, colB = 10, nB = 3, typeB = 0, pointB = 0;
    double **C = new double *[10];
    for (int i = 0; i < 10; i++) {
        C[i] = B[i];
    }
    cout << setprecision(0) << fixed;
    PrintMatrix(C, rowB, colB, nB, typeB, pointB);
    cout << endl;

    cout << B << "  " << B[0] << "  " << B[1] << endl;
    cout << B[0][0] << "  " << **B << "  " << *B[0] << endl;
    cout << *(*(B + 1)) << "  " << *B[1] << endl;
    cout << *(B[0] + 1) << "  " << *(*B + 1) << endl;
    cout << B[0][20] << "  " << *(B[0] + 20) << "  " << *B[2] << endl;
    system("pause");
    return 0;
}
void FillMatrix(double** A, int nrows, int ncols) {
    int k = 0;
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            k++;
            if (i == j) A[i][j] = 1.;
            else if (j > i) {
                if (i == 0)
                    A[i][j] = A[i][j - 1] / (j+1);
                else
                    A[i][j] = A[i - 1][j] * A[0][j];
            }
            else if (i > j) {
                if (i - 1 == j and j != 0) {
                    A[i][j] = A[i - 2][j] * A[0][j] * A[0][j];
                }
                else
                    A[i][j] = abs(A[i - 1][j] * A[0][j]);
                if (i % 2== 0)
                    A[i][j] *= -1;
            }
        }
    }
}
double fact(double x) {
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;

    return x * fact(x - 1);
}