#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int Menu(){
    cout<<"================ Меню ===================\n";
    cout<<"\t1 - Вычисление y = x - 5*cos(x)\n";
    cout<<"\t2 - Вычисление y = x - 10*cos(x)\n";
    cout<<"\t3 - Вычисление универсальной функции\n";
    cout<<"\t4 - Выход\n";
    cout<<"=========================================\n";
    int choice;
    cout<<"Выберите действие: ";
    cin>>choice;
    while(cin.fail()){
        cout<<"Ошибка ввода. Повторите ввод\n";
        cin.clear() ;
        cin.ignore(10,'\n');
        cin>>choice;
    }
    return choice;
}

int HalfDiv(int k) {
    string quest = "y";
    do {
        vector<double> roots;
        double xl, xr, x, eps, n = 0, h, templ, tempr, eps1 = 0.1;
        int y = 0;
        cout << "Введите переменные eps: ";
        cin >> eps;
        cout << "Введите левую и правую границы диапазона: ";
        cin >> xl >> xr;
        cout << "Введите шаг: ";
        cin >> h;
        templ = xl;
        tempr = xr;
        while (xl < xr) {
            if (abs(xl - k * cos(xl)) <= eps) {
                cout << "Ответ: " << xl << endl;
            }
            if (abs(xr - k * cos(xr)) <= eps) {
                cout << "Ответ: " << xr << endl;
            }
            while ((xr - xl) > eps) {
                x = xl + (xr - xl) / 2;
                if (((xl - k * cos(xl)) * (x - k * cos(x))) < 0) {
                    xr = x;
                } else {
                    xl = x;
                }
                n++;
            }
            y++;
            xl = templ + h*y;
            xr = tempr;
            bool test = false;
            if (roots.empty()) {
                roots.push_back(x);
            }
            else {
                for (int j = 0; j < roots.size(); j++) {
                    if (abs(roots[j] - x) < eps1) {
                        test = true;
                    }
                }
            }
            if (test == false) {
                roots.push_back(x);
            }
            xl += h;
        }
        auto iter = roots.cbegin();
        roots.erase(iter + 0);
        roots.pop_back();
        if (roots.empty()) {
            cout << "На данном промежутке нет корней" << endl;
        }
        else {
            for (int j = 0; j < roots.size(); j++) {
                cout << roots[j] << endl;
            }
        }
        cout << "Количество итераций: " << n << endl;
        cout << "Продолжить работу? y/n " << endl;
        cin >> quest;
    }
    while (quest.substr(0,1) != "n");
    cout << endl;
    return 0;
}

int RandFunc() {
    string quest = "y";
    do {
        vector<double> roots;
        double xl, xr, x, eps, n = 0, h, templ, tempr, eps1 = 0.1;
        int y = 0;
        cout << "Введите переменные eps: ";
        cin >> eps;
        cout << "Введите левую и правую границы диапазона: ";
        cin >> xl >> xr;
        cout << "Введите шаг: ";
        cin >> h;
        templ = xl;
        tempr = xr;
        while (xl < xr) {
            if (abs(xl - cos(xl)) <= eps) {     //пример: xl - k * cos(xl)
                cout << "Ответ: " << xl << endl;
            }
            if (abs(xr - cos(xr)) <= eps) {      //пример: xr - k * cos(xr)
                cout << "Ответ: " << xr << endl;
            }
            while ((xr - xl) > eps) {
                x = xl + (xr - xl) / 2;
                if (((xl -  cos(xl)) * (x - cos(x))) < 0) {      //пример: ((xl - k * cos(xl)) * (x - k * cos(x))
                    xr = x;
                } else {
                    xl = x;
                }
                n++;
            }
            y++;
            xl = templ + h*y;
            xr = tempr;
            bool test = false;
            if (roots.empty()) {
                roots.push_back(x);
            }
            else {
                for (int j = 0; j < roots.size(); j++) {
                    if (abs(roots[j] - x) < eps1) {
                        test = true;
                    }
                }
            }
            if (test == false) {
                roots.push_back(x);
            }
            xl += h;
        }
        auto iter = roots.cbegin();
        roots.erase(iter + 0);
        roots.pop_back();
        if (roots.empty()) {
            cout << "На данном промежутке нет корней" << endl;
        }
        else {
            for (int j = 0; j < roots.size(); j++) {
                cout << roots[j] << endl;
            }
        }
        cout << "Количество итераций: " << n << endl;
        cout << "Продолжить работу? y/n " << endl;
        cin >> quest;
    }
    while (quest.substr(0,1) != "n");
    cout << endl;
    return 0;
}

int main() {
    while(true) {
        switch (Menu()) {
            case 1:
                HalfDiv(5);
                break;
            case 2:
                HalfDiv(10);
                break;
            case 3:
                RandFunc();
                break;
            case 4:
                return 0;
        }
    }
}