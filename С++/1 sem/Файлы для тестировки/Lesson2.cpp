// Created by user on 10.09.2021. Александр Дмитриевич Козлов
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main() {
    float x,s,an,eps,y,h=0.2;
    int n,i;
    do {
        cout << "Введите x: ";
        cin >> x;
    }
    while (fabs(x) < 1);
    eps = 0.000001;
    s = 0.0;
    y = 1.0;
    an = tan(3.1416/4)*x*x;
    do {
        cout << "Введите n > 0: ";
        cin >> n;
    }
    while (n < 0);
    for (i = 2; i < n; i ++) {
        s += an;
        an = an*-x*x/((2*i-1)*(2*i-2));
        if (i == 3 || i == 5 || i == 10){
            cout << "i = " << i << "s= " << s << endl;
        }
    }
    return 0;
}