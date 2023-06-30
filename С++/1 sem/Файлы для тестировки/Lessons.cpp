//Урок по проге 3 сентября 2021
/*   >,<, >=, <=, ==, != */
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    float x1,y1,x2,y2,x3,y3;
    float A,B,C,S,P;
    cout << "Введите 1-ю точку " << endl;
    cin >> x1 >> y1;
    cout << "Введите 2-ю точку " << endl;
    cin >> x2 >> y2;
    cout << "Введите 3-ю точку " << endl;
    cin >> x3 >> y3;
    A = sqrt(pow((x1-x2),2) + pow((y1-y2),2));
    B = sqrt(pow((x2-x3),2) + pow((y2-y3),2));
    C = sqrt(pow((x3-x1),2) + pow((y3-y1),2));
    if (((A + B) > C) && ((B + C) > A) && ((A + C) > B)) {
        P = (A + B + C)/2.0;
        S = sqrt(P*(P-A)*(P-B)*(P-C));
        cout << S << P << endl;

    }
}