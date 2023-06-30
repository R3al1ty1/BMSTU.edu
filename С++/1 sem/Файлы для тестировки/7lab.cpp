#include <iomanip>
#include <iostream>
#include <cmath>
#include "MatPrintHeader.h"
using namespace std;

double **CreateMatrix(int& nrow, int& ncol) {
    //nrow += 1; ncol += 1;
    double** a = new double* [nrow]; // выделение памяти под вспомогательный массив указателей на строки

    // выделение памяти под строки матрицы
    // и инициализация вспомогательного массива указателей на строки
    for (int i = 0; i < nrow; i++)
        a[i] = new double[ncol];
    return a;
}


double** FillMatrix(double** a, int& nrow, int& ncol) {
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            short choice;

            if (i == j)					// главная диагональ
                choice = 1;

            else if (i == 0 && j == 1)	// первая строка и 2-ой элемент (переворачивается единожды)
                choice = 2;

            else if (i == 0 && j > 1)	// первая строка и элементы после 2-го
                choice = 3;				// (если делать j > 0, то ниче не меняется??)

                // - - - - - - - - i < j = верхний треугольник - - - - - - - - - - - -
            else if (i < j && i > 0)	// верхний треугольник со 2-ой строки
                choice = 4;

                // - - - - - - - - i > j = нижний треугольник - - - - - - - - - - - - -
            else if (i > j && i > 0)    // нижний треугольник со 2-ой строки
                choice = 5;

            else if (i > j && i == 2)	// нижний треугольник и 3-я строка
                choice = 6;

            switch (choice)
            {
                case 1:
                    a[i][j] = 1;
                    break;

                case 2:
                    a[i][j] = 1 / (a[0][j - 1] * (j + 1));
                    break;

                case 3:
                    a[i][j] = a[0][j - 1] / (j + 1);
                    break;

                case 4:
                    if (a[i - 1][j] != 1)	// проверка попадает ли элемент a[i - 1][j] на главную диагональ
                        a[i][j] = a[0][j] * a[i - 1][j];

                    else
                        a[i][j] = a[0][j] * a[0][j] * a[i - 2][j];
                    break;

                case 5:
                    if (a[i - 1][j] != 1 || j == 0) // j == 0 если это первый столбец
                        a[i][j] = pow(-1, i + 1) * abs(a[0][j] * a[i - 1][j]);

                    else
                        a[i][j] = pow(-1, i + 1) * abs(a[0][j] * a[0][j] * a[i - 2][j]);
                    break;

                case 6:
                    a[i][j] = pow(-1, i + 1) * abs(a[0][j] * a[0][j]);
            }
        }
    }
    return a;
}


int main()
{
    setlocale(LC_ALL, "ru");

    int NumRow, NumCol, n; // для 5х5 матрицы оптимально брать n >= 9 (видны все знаки)
    cout << "Введите количество строк и столбцов: ";
    cin >> NumRow >> NumCol;
    cout << "Введите количество знаков после запятой: ";
    cin >> n;

    double** mat = CreateMatrix(NumRow, NumCol);
    mat = FillMatrix(mat, NumRow, NumCol);
    PrintMatrix(mat, NumRow, NumCol, n);

// -------------------------------------------------------------------------------------------------------------------
    cout << "\n\n---------------------------------------------------------------------------------------------\n\n";


    int rowB = 10, colB = 10, nB = 0;
    int** B = new int* [rowB];
    for (int i = 0; i < rowB; i++) {
        B[i] = new int[colB];
    }

    for (int i = 0; i < rowB; i++) {
        for (int j = 0; j < colB; j++) {
            B[i][j] = i * 10 + j;
        }
    }
    PrintMatrix(B, rowB, colB, nB);


    cout << "\n\n---------------------------------------------------------------------------------------------\n\n";

    cout << B << '\t' << B[0] << '\t' << B[2] << "\n\n";
    cout << B[0][0] << '\t' << **B << '\t' << *B[0] << "\n\n";
    cout << *(*(B + 1)) << '\t' << *B[1] << "\n\n";
    cout << *(B[0] + 1) << '\t' << *(*B + 1) << "\n\n";
    cout << B[0][20] << '\t' << *(B[0] + 20) << '\t' << *B[2] << "\n\n";


    cout << "\n\n";
    system("pause");
    return 0;
}