#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int solveCos(int ) {

}
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

int fivex() {
    string quest = "y";
    do {
        vector<double> roots;
        double xl, xr, x, eps, k = 5, n = 0, h, templ, tempr, eps1 = 0.1;
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
            for (int k = 0; k < roots.size(); k++) {
                cout << roots[k] << endl;
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

int tenx() {
    string quest = "y";
    do {
        vector<double> roots;
        double xl, xr, x, eps, k = 10, n = 0, h, templ, tempr, eps1 = 0.1;
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
            for (int k = 0; k < roots.size(); k++) {
                cout << roots[k] << endl;
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
                fivex();
                break;
            case 2:
                tenx();
                break;
                /*case 3:
                    HalfDiv();
                    break;*/
            case 4:
                return 0;
        }
    }
}