#include <iostream>
#include <cmath>
#include<iomanip>

using namespace std;
typedef double(*TPF)(double);
double f1(double x) {
    return x;
}
double f2(double x) {
    return sin(22 * x);
}
double f3(double x) {
    double d = x * x;
    return d * d;
}
double f4(double x) {
    return atan(x);
}

double IntTrap(TPF f, double a, double b, int n) {
    double x, h;
    double sum = 0;
    double S;
    h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        x = a + i * h;
        S = f(x);
        sum += S;
    }
    sum += (f(a)+f(b))/2;
    return (sum * h);
}


double IntRect(TPF f, double a, double b, int n) {
    double sum = 0.0, step;

    if (0 == n) return sum;

    step = (b - a) / (n);
    for (int i = 0 ; i < n ; i++ ) {
        sum += f (a + step*(i+0.5));
    }
    sum *= step;
    return sum;
}

struct print {
    const char* name;
    double i_sum, i_toch;
    int n;
};

    // вывод результатов на экран
    void PrintRes(print i_prn[], int k) {
        cout << "-----------------------------------------------------------------" << endl;
        cout << "| Функция          | Интеграл        | IntSum          | N[i]   |" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        for (int i = 0; i < k; i++) {
            cout << setiosflags(ios::left);
            cout << "| " << setw(16) << i_prn[i].name << " | " << setw(15) << fixed << setprecision(10) << i_prn[i].i_toch << " | " << setw(15) << i_prn[i].i_sum << " | " << setw(5) << i_prn[i].n << "  |" << endl;
        }
        cout << "-----------------------------------------------------------------" << endl;
    }


int main() {
    double a, b;
    double S1, S;
    print arr[4];
    int n = 1, c = 0;
    double toch[4] = {0.01, 0.001, 0.0001, 0.00001};
    double (*fun[4])(double) = {f1, f2, f3, f4};
    const char *name[] = {"y=x ", "y=sin(22x)", "y=x^4 ", "y=atan(x) "};
    cout << "Левая граница интегрирования a = ";
    cin >> a;
    cout << "Правая граница интегрирования b = ";
    cin >> b;
    double d = b * b, g = d * d, e = a * a, u = e * e;
    double O[4] = {(d - e) / 2, (cos(22 * a) - cos(22 * b)) / 22, (g * b - u * a) / 5,
                   b * atan(b) - a * atan(a) - (log(d + 1) - log(e + 1)) / 2};
    cout << "\tМетод прямуогольников\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int n = 1;
            arr[j].name = name[j];
            arr[j].n = toch[i];
            S1 = IntRect(*fun[j], a, b, n);
            int k = 0;
            do {
                S = S1;
                n = 2 * n;
                S1 = IntRect(*fun[j], a, b, n);
                k++;
            } while (fabs((S1 - S)/3) > toch[i]);
            arr[j].i_sum = S1;
            arr[j].i_toch = O[j];
            arr[j].n = n;
        }
        PrintRes(arr, 4);
    }
    cout << "\tМетод трапеций\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int n = 1;
            arr[j].name = name[j];
            arr[j].n = toch[i];
            S1 = IntTrap(*fun[j], a, b, n);
            int k = 0;
            do {
                S = S1;
                n = 2 * n;
                S1 = IntTrap(*fun[j], a, b, n);
              //  k++;
            } while (fabs((S1 - S)/3) > toch[i]);
            arr[j].i_sum = S1;
            arr[j].i_toch = O[j];
            arr[j].n = n;
        }
        PrintRes(arr, 4);
    }
}