//#include <windows.h>
#include <stdio.h>
//#include <conio.h>
#include <math.h>
#include <clocale>
#include <iostream>
#include <cstdlib>



void ShowVector(int n, double ** vec, double * vec1);
void PryamoiHod(int n, double **a, double *b);
void ObratniHod(int n, double **a, double *b, double *x);

int main()
{
    setlocale(LC_ALL, "Russian");

    int i,j,n;
    double **a, *b, *x;
    do
    {
        printf("Введите размерность матрицы: ");
        scanf("%d",&n);
        //Выделяем память под матрицу А и векторы В и Х
        a = (double **)malloc(n*sizeof(double));
        b = (double *)malloc(n*sizeof(double));
        x = (double *)malloc(n*sizeof(double));

        //Ввод a
        printf("Введите элементы матрицы через пробел построчно\n");
        for(i = 0; i< n; i++)
        {
            a[i] = (double *)malloc(n*sizeof(double));
            for(j = 0; j < n; j++)
            {
                scanf("%lf",&a[i][j]);
            }
        }

        //Ввод b
        printf("Введите свободные элементы через пробел \n");
        for(i = 0; i< n; i++)
        {
            scanf("%lf",&b[i]);
        }

        system("cls");
        printf("\Просмотрданных\r\n");
        printf("Расширенная матрица: \r\n\n");
        ShowVector(n,a,b);

        printf("\Процесс решения методом Гаусса\r\n");
        PryamoiHod(n, a, b);
        printf("Приведение матрицы к диагональному виду\r\n\n");//Прямой ход
        ShowVector(n,a,b);
        printf("\n");

        ObratniHod(n, a, b, x);

        printf("Переменные :\r\n");
        for(i=0;i<n;i++)
        {
            printf(" %2.2f ",x[i]);
        }
        printf("\n\n");

        printf("Нажмите Enter для выхода\r\n");
//Чистимпамять
        free((void *)a);
        free((void *)b);
        free((void *)x);
    }
    while(toupper(getchar()) == 'Y');
    return 0;
}

void ShowVector(int n, double ** vec, double * vec1)
{
    int i,j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n+1;j++)
        {
            if(j==n)
                printf("| %2.2f ",vec1[i]);
            else
                printf(" %2.2f",vec[i][j]);
        }
        printf("\n");
    }
    printf("\r\n");
}

void PryamoiHod(int n, double **a, double *b)
{
    double v;
    for(int k = 0,i,j,im; k < n - 1; k++)
    {
        im = k;
        for(i = k + 1; i< n; i++)
        {
            if(fabs(a[im][k]) <fabs(a[i][k]))
            {
                im = i;
            }
        }
        if(im != k)
        {
            for(j = 0; j < n; j++)
            {
                v   = a[im][j];
                a[im][j] = a[k][j];
                a[k][j]  = v;
            }
            v = b[im];
            b[im] = b[k];
            b[k]  = v;
        }
        for(i = k + 1; i< n; i++)
        {
            v = 1.0*a[i][k]/a[k][k];
            a[i][k] = 0;
            b[i]   = b[i] - v*b[k];
            if(v != 0)
                for(j = k + 1; j < n; j++)
                {
                    a[i][j] = a[i][j] - v*a[k][j];
                }
        }
    }
}

void ObratniHod(int n, double **a, double *b, double *x)
{
    double s = 0;
    x[n - 1] = 1.0*b[n - 1]/a[n - 1][n - 1];
    for(int i = n - 2, j; 0 <= i; i--)
    {
        s = 0;
        for(j = i + 1; j < n; j++)
        {
            s = s+a[i][j]*x[j];
        }
        x[i] = 1.0*(b[i] - s)/a[i][i];
    }
}
