#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    string frst;
    string scnd;
    int n = 0;

    cout << "Введите первую дату: ";
    getline(cin, frst);
    cout << "Введите вторую дату: ";
    getline(cin, scnd);
    cout << "Введите n дней: ";
    cin >> n;
    cout << endl;

    int day1 = stoi(frst.substr(0,2));
    int month1 = stoi(frst.substr(3,2));
    int year1 = stoi(frst.substr(6,4));

    int day2 = stoi(scnd.substr(0,2));
    int month2 = stoi(scnd.substr(3,2));
    int year2 = stoi(scnd.substr(6,4));

    int dayscnt[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int qnt1 = 0;
    int qnt2 = 0;
    for (int i = 0; i < month1 - 2; i++)
        qnt1 += dayscnt[i];
    for (int i = 0; i < month2 - 2; i++)
        qnt2 += dayscnt[i];
    int leaps1 = div(year1,4).quot;
    int leaps2 = div(year2,4).quot;
    //cout << day1 << " " << day2 << endl;
    int range1 = leaps1 + year1*365 + day1 + qnt1;
    int range2 = leaps2 + year2*365 + day2 + qnt2;

    int res = 0;
    res = abs(range1 - range2);
    if (res % 10 == 1){
        cout << res << " " << "день";
    }
    if ((res % 10 == 2) or (res % 10 == 3) or (res % 10 == 4)) {
        cout << res << " " << "дня";
    }
    else {
        cout << res << " " << "дней";
    }
    cout << endl;

    while(n > dayscnt[month1-1]){
        n -= dayscnt[month1-1];
        if (month1 != 12)
            month1 += 1;
        if ((month1 == 1) && (year1 % 4 == 0) && (n > 0))
            n -= 1;
        else {
            year1 += 1;
            month1 = 1;
        }
    }
    if (year1 % 4 == 0)
        dayscnt[1] += 1;
    if (n < (dayscnt[month1-1] - day1))
        day1 += n;
    else{
        n -= (dayscnt[month1-1] - day1);
        month1 += 1;
        day1 = n;
        if (month1 == 13) {
            year1 += 1;
            month1 = 1;
        }
    }
    if (year1 % 4 == 0)
        dayscnt[1] -= 1;
    //вычитание
    while(n > dayscnt[month1-1]){
        n -= dayscnt[month1-1];
        if ((month1 == 3) && (year1 % 4 == 0) && (n > 0))
            n += 1;
        if (month1 != 1)
            month1 -= 1;
        else {
            year1 -= 1;
            month1 = 12;
        }
    }
    if (year1 % 4 == 0)
        dayscnt[1] += 1;
    if (n < day1)
        day1 -= n;
    else{
        n -= day1;
        month1 -= 1;
        day1 = dayscnt[month1-1] - n;
        if (month1 == -1) {
            year1 -= 1;
            month1 = 12;
        }
    }
    if (year1 % 4 == 0)
        dayscnt[1] -= 1;
    cout << "Новая дата: " << day1 << "." << month1 << "." << year1 << endl;
}