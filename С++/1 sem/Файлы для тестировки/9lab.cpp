#include <fstream>
#include <iostream>
#include <iomanip>
#include "MatrixPrintHeader.h"

using namespace std;

// �������� ������� ��� �������� � ��� ����
double** CreateMatrix(int& nRow, int& nCol, double *free, int ch) {
    int i, j;
    double** c;

    if (ch == 1) {
        ifstream fin("reverse.txt", ios::in); // ��� �������� �������
        fin >> nRow >> nCol;
        c = new double* [nRow];
        for (i = 0; i < nRow; i++)
            c[i] = new double[nCol];

        for (i = 0; i < nRow; i++)
            for (j = 0; j < nCol; j++)
                fin >> c[i][j];
    }
    else {
        int k = 0; double a;
        ifstream fin("slau.txt", ios::in); // ��� ����
        fin >> nRow;

        c = new double* [nRow];
        for (i = 0; i < nRow; i++)
            c[i] = new double[nRow];

        for (i = 0; i < nRow+1; i++)
            for (j = 0; j < nRow; j++) {
                if (i < nRow) // ������� �������� ������������ ��� x
                    fin >> c[i][j];
                else{
                    fin >> a;
                    free[k] = a; // ����� �������� ��������� ����� (��� ����� �� nRow+1 ������)
                    k++;
                }
            }
    }
    return c;
}

// ������������� ��������� ������� nRow x nCol � �������� (�.�. ���������� nRow x 2nCol)
double** ConnectMatrix(double** mat, int& nRow, int& nCol) {
    nCol *= 2;
    int i, j;

    double** b = new double* [nRow];
    for (i = 0; i < nRow; i++)
        b[i] = new double[nCol];

    for (i = 0; i < nRow; i++)
        for (j = 3; j < nCol; j++) //������ j=3 � �� ����; �������� ���������(??), ������ ���� �� �� �������
            if (i == (j - nRow)) //���������� ��������� (������) �������
                b[i][j] = 1;
            else
                b[i][j] = 0;

    for (i = 0; i < nRow; i++)
        for (j = 0; j < nCol / 2; j++)
            b[i][j] = mat[i][j]; // ������� ��������� �� �������� � ����������� (� ����� �����)
    return b;
}

// ���������� �������� ������� ������� ������, ���������� ����. nRow x 2nCol, �������� �� ����� ���������
double** ReverseMatrix(double** a, int nRow, int nCol) {
    //������ ��� -> (a) ���������� ����������������
    //�� ���� ������ ��� ���� �������� ��� �������� ������, ������� ��� ������ ����� ����������� �����
    int i, j, fl = 0, fl_2 = 0; double F;
    for (i = 0; i < nRow; i++) {

        F = a[i][i]; // ����-� ������� ������� ���������, ������� ��������� � �������

        for (j = 0; j < nCol; j++) {

            if (F == 0 && i != nRow) {
                cout << "\n\n������� �� = 0";
                fl = 1;
                for (int k = i + 1; k < nRow; k++) {
                    if (a[k][j] != 0 && fl_2 == 0) {
                        fl_2 = 1;
                        for (int p = 0; p < nCol; p++) {
                            double t;
                            t = a[i][p];
                            a[i][p] = a[k][p];
                            a[k][p] = t;
                        }
                    }
                }
                if (fl_2 == 0 && fl == 1) { cout << "\n�������� ������� �� ����������\n\n"; exit(0); }
                F = a[i][i];
            }
            if (fl == 1) {
                cout << "\n\n������ �����\n";
                PrintMatrix(a, nRow, nCol, 3);
                for (fl = 0; fl < 90; fl++) { cout << "-"; } cout << "\n";
                fl = 0;
            }

            a[i][j] /= F;
        }

        //�������� ��� -> (a) ���������� ���������
        for (int m = i + 1; m < nRow; m++) {
            double A = a[m][i]; // ����-� ��������, ����������� ��� ��������� ��, ������� ������ ����������
            for (int n = 0; n < nCol; n++) {
                a[m][n] -= a[i][n] * A;
            }
        }
    }
    cout << "\n\n������ ���\n";
    PrintMatrix(a, nRow, nCol, 3);
    for (fl = 0; fl < 90; fl++) { cout << "-"; } cout << "\n";

    for (j = nCol - nRow - 1; j > 0; j--) {
        for (i = j; i > 0; i--) {

            for (int s = nCol - nRow; s < nCol; s++) {
                a[i - 1][s] -= a[j][s] * a[i - 1][j];
            }

            a[i - 1][j] -= a[i - 1][j] * a[j][j]; // ������ � ��� ���
        }
    }
    return a;
}

// ��������� ������������� ������
double** MultiplyMatrix(double** a, double** b, int nRow1, int nCol1, int nRow2, int nCol2) {
    int i, j;
    double** c = new double* [nRow1];
    for (i = 0; i < nCol2; i++)
        c[i] = new double[nCol2];

    for (int i = 0; i < nRow1; i++)
    {
        for (int j = 0; j < nCol2; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < nCol1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }

    return c;
}

// ������� ����
double* SolveSLAU(double** matrix, double* free, short N) {
    double* x, max;
    int k = 0, index;
    const double eps = 0.00001;  // ��������
    x = new double[N];

    while (k < N) {
        // ����� ������ � ������������ a[i][k]
        max = abs(matrix[k][k]);
        index = k;
        for (int i = k + 1; i < N; i++) {
            if (abs(matrix[i][k]) > max) {
                max = abs(matrix[i][k]);
                index = i;
            }
        }
        // ������������ �����
        if (max < eps) {
            // ��� ��������� ������������ ���������
            cout << "������� �������� ���������� ��-�� �������� ������� ";
            cout << index << " ������� A" << endl;
            return 0;
        }
        for (int j = 0; j < N; j++) {
            double temp = matrix[k][j];
            matrix[k][j] = matrix[index][j];
            matrix[index][j] = temp;
        }

        double temp = free[k];
        free[k] = free[index];
        free[index] = temp;

        for (int i = k; i < N; i++) {
            double temp = matrix[i][k];
            if (abs(temp) < eps)
                continue; // ��� �������� ������������ ����������
            for (int j = 0; j < N; j++)
                matrix[i][j] = matrix[i][j] / temp;

            free[i] = free[i] / temp;
            if (i == k)
                continue; // ��������� �� �������� ���� �� ����
            for (int j = 0; j < N; j++)
                matrix[i][j] = matrix[i][j] - matrix[k][j];

            free[i] = free[i] - free[k];
        }
        k++;
    }
    // �������� �����������
    for (k = N - 1; k >= 0; k--)
    {
        x[k] = free[k];
        for (int i = 0; i < k; i++)
            free[i] = free[i] - matrix[i][k] * x[k];
    }
    return x;
}


int menu() {
    int input;
    cout << "\t\t\n\t\t------------------------�� �9-------------------------" << endl;
    cout << "\t\t1 - ���� �������" << endl;
    cout << "\t\t2 - ���������� �������� ������� ������� ������-�������" << endl;
    cout << "\t\t3 - ������ ����, �������� � ��������� ����" << endl;
    cout << "\t\t4 - ����� �� ���������" << endl;
    cout << "\t\t------------------------------------------------------" << endl;
    cin >> input;

    return input;
}

int precision;

int main() {
    setlocale(LC_ALL, "ru");

    int i, j, ch;
    int nRow, nCol, N, k;
    ifstream fin("slau.txt", ios::in); // ����������� ���� �������� �����
    fin >> N;
    double** mat = 0, ** reverse_mat = 0, ** a = 0, ** E = 0;
    double* solutions = new double[N];
    double* free = new double[N];
    double** slau;


    while (true) {
        switch (menu()) {
            case 1:
                system("cls");
                cout << "\n\t\t���� ������� �� �����\n";
                cout << "\t\t---------------------\n";
                cout << "\n������� ��������:\n"; cin >> precision;
                ch = 1;
                mat = CreateMatrix(nRow, nCol, free, ch);
                cout << "\n\n�������� �������\n";
                PrintMatrix(mat, nRow, nCol, precision);

                system("pause");
                break;

            case 2:
                system("cls");
                cout << "\n\t\t���������� �������� ������� ������� ������-�������\n";
                cout << "\t\t--------------------------------------------------\n";
                cout << "\n\n�������� �������\n";
                PrintMatrix(mat, nRow, nCol, precision);
                for (i = 0; i < 90; i++) { cout << "-"; } cout << "\n";

                a = ConnectMatrix(mat, nRow, nCol);
                cout << "\n\n�������������� �������\n";
                PrintMatrix(a, nRow, nCol, precision);
                for (i = 0; i < 90; i++) { cout << "-"; } cout << "\n";

                a = ReverseMatrix(a, nRow, nCol);
                cout << "\n\n\t�������� ���\n";
                PrintMatrix(a, nRow, nCol, precision);
                for (i = 0; i < 90; i++) { cout << "-"; } cout << "\n";

                reverse_mat = new double* [nRow];
                for (i = 0; i < nRow; i++)
                    reverse_mat[i] = new double[nRow];
                cout << "\n\n\t�������� �������\n";
                for (i = 0; i < nRow; i++)
                    for (j = 0; j < nRow; j++)
                        reverse_mat[i][j] = a[i][j + nRow];

                PrintMatrix(reverse_mat, nRow, nRow, precision);
                for (i = 0; i < 90; i++) { cout << "-"; } cout << "\n";

                cout << "\n\n\t�������� (��������� �������� �� ��������)\n";
                E = MultiplyMatrix(mat, reverse_mat, nRow, nRow, nRow, nRow);
                PrintMatrix(E, nRow, nRow, 0);
                for (i = 0; i < 90; i++) { cout << "-"; } cout << "\n";

                system("pause");
                break;

            case 3:
                system("cls");
                cout << "\n\t\t������� ����\n";
                cout << "\t\t------------\n";
                cout << "\n������� ��������:\n"; cin >> precision;
                k = 0;
                ch = 2;
                slau = CreateMatrix(N, N, free, ch);

                cout << "\n������� �������������:\n";
                PrintMatrix(slau, N, N, precision);
                cout << "\n��������� �����:\n";
                for (i = 0; i < N; i++)
                    cout << free[i] << "\n";

                solutions = SolveSLAU(slau, free, N);

                cout << "\n�������:" << endl;
                for (i = 0; i < N; i++)
                    cout << fixed << setprecision(precision) << "x_" << i + 1 << " = " << solutions[i] << endl;

                cout << "\n\n";

                system("pause");
                break;

            case 4:
                delete[] mat;
                delete[] reverse_mat;
                delete[] a;
                delete[] E;
                delete[] solutions;
                delete[] free;
                return 0;
        }
    }
}