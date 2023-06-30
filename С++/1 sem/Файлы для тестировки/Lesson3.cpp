#include <iostream>
//#include <iomanip>
using namespace std;
//(pow(10,-6)) = 10e-6
int main() {
    int a = 7;
    int & b = a;
    cout << a << " " << b << " " << &a << " " << &b << endl;
    /*bool t = true;
    cout << boolalpha << t;*/
    cout << endl;
    //cout << scientific (fixed) << pi << endl;
    return 0;
}
//массив - конечная зависимость одного типа размещенных подярд в памяти элементов