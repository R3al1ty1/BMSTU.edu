#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int FirstTask() {
    string quest = "y";
    do {
        int m,n,sum = 0;
        cout << "Введите количество чисел: ";
        cin >> n;
        cout << "Введите число m: ";
        cin >> m;
        for(int i = 1; i <= n; i++){
            if ((i % 5 == 0) && (i % m != 0)) {
                sum += i;
            }
        }
        cout << sum << endl;
        cout << "Продолжить работу? y/n " << endl;
        cin >> quest;
    }
    while (quest.substr(0,1) != "n");
    cout << endl;
    return 0;
}
int SecondTask() {
    string quest = "y";
    do {
        float a;
        double s = 1.0;
        cout << "Введите переменную a: ";
        cin >> a;
        if (a >= 0) {
            for (int i = 2.0; i <= 8; i += 2) {
                s *= (pow(i,2));
            }
            s -= a;
        }else {
            for (int i = 3; i <= 9; i += 3) {
                s *= (i-2);
            }
        }
        cout << setw(10);
        cout << setprecision(9) << s << endl;
        cout << "Продолжить работу? y/n " << endl;
        cin >> quest;
    }
    while (quest.substr(0,1) != "n");
    cout << endl;
    return 0;
}
int ThirdTask() {
    double x1 = 0,x2 = 0,eps1 = 0.000001, eps2 = 0.00000001;
    cout << "------------------------------" << endl;
    cout << setw(2) << "x" << setw(9) << "Y" << setw(11) << "S" << setw(7) << "N" << endl;
    cout << "------------------------------" << endl;
    for (double h = 0.2; x1 <= 1.0; x1 += h) {
        int i = 1;
        double s = 0,y,a;
        y = pow(M_E, (-(pow(x1, 2))));
        a = 1;
        while (fabs(a) >= eps1) {
            s += a;
            a = a * (-pow(x1, 2) / i);
            if (i <= 12){
            }
            i++;
        }if (x1 == 0){
            cout << x1 << " " << setw(5) << s << " " << setw(10) << y << " " << setw(10) << i-1 << endl;
        }else if (x1 == 1){
            cout << x1 << " " << setw(12) << s << " " << setw(10) << y << " " << setw(4) << i-1 << endl;
        }else {
            cout << x1 << " " << setw(10) << s << " " << setw(10) << y << " " << setw(3) << i - 1 << endl;
        }
    }
    cout << "-----------------------------------" << endl;
    cout << setw(2) << "x" << setw(10) << "Y" << setw(13) << "S" << setw(9) << "N" << endl;
    cout << "-----------------------------------" << endl;
    for (double h = 0.2; x2 <= 1.0; x2 += h) {
        int i = 1;
        double s = 0,y,a;
        y = pow(M_E, (-(pow(x2, 2))));
        a = 1;
        while (fabs(a) >= eps2) {
            s += a;
            a = a * (-pow(x2, 2) / i);
            if (i <= 12){
            }
            i++;
        }if (x2 == 0){
            cout << x2 << " " << setw(5) << setprecision(8) << s << " " << setw(12) << setprecision(8) << y << " " << setw(13) << i-1 << endl;
        }else if (x2 == 1){
            cout << x2 << " " << setw(14) << setprecision(8) << s << " " << setw(12) << setprecision(8) << y << " " << setw(4) << i-1 << endl;
        }else {
            cout << x2 << " " << setw(12) <<  setprecision(8) << s << " " << setw(12) << setprecision(8) << y << " " << setw(4) << i - 1 << endl;
        }
    }
    cout << endl;
    return 0;
}
int FourthTask() {
    string quest = "y";
    do {
        double s = 1.0;
        int x,n;
        cout << "Введите число n: ";
        cin >> n;
        cout << "Введите число x: ";
        cin >> x;
        for (int i = 1; i <= n; i++){
            if (n > 3 && i == 2) {
                cout << "Сумма " << i + 1 << " слагаемых равна " << s << endl;
            }if (n > 5 && i == 4){
                cout << "Сумма " << i + 1 << " слагаемых равна " << s << endl;
            }if (n > 10 && i == 9){
                cout << "Сумма " << i + 1 << " слагаемых равна " << s << endl;
            }if (i % 2 == 1) {
                s += (-(pow(x, i + 1)) / (i * (pow(2, i))));
            }else {
                s += (pow(x, i + 1)) / (i * (pow(2, i)));
            }
        }
        cout << setprecision(2) << s << endl;
        cout << "Продолжить работу? y/n " << endl;
        cin >> quest;
    }
    while (quest.substr(0,1) != "n");
    cout << endl;
    return 0;
}

int main(){
        int program;
        cout << "Введите номер программы: ";
        cin >> program;
        cout << endl;
        switch (program) {
            case 1:
                FirstTask();
                break;
            case 2:
                SecondTask();
                break;
            case 3:
                ThirdTask();
                break;
            case 4:
                FourthTask();
                break;
            default:
                cout << "Проверьте правильность введённых данных" << endl;
        }
        cout << endl;
        return 0;
}