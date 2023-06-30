#include <iostream>
#include <string>
using namespace std;
//Эта программа выдает разницу между датами, не включая последнюю дату.
//Чтобы получить разницу с последней датой, необходимо к переменной res
//прибавить 1 (res++)
int main() {

    string frst; //первая дата
    string scnd; //вторая дата

    cout << "Введите первую дату: ";
    getline(cin, frst);
    cout << "Введите вторую дату: ";
    getline(cin, scnd);

    string year1 = frst.substr(6,10); //здесь и далее выбор года, месяца и дня из общей строки
    string month1 = frst.substr(3,5);
    string day1 = frst.substr(0,2);
    string year2 = scnd.substr(6,10);
    string month2 = scnd.substr(3,5);
    string day2 = scnd.substr(0,2);

    int month1f,day1f,month2f,day2f,res;
    int vis_add1 = 0;
    int vis_add2 = 0;

    //здесь и далее перевод строки в инт + если месяц меньше 10, то выбираю одну цифру (не 01, а 1)
    if (day1.substr(0,1) == "0"){
        day1f = stoi(day1.substr(1,2));
    }
    else {
        day1f = stoi(day1.substr(0,2));
    }

    if (day2.substr(0,1) == "0"){
        day2f = stoi(day2.substr(1,2));
    }
    else {
        day2f = stoi(day2.substr(0,2));
    }

    if (month1.substr(0,1) == "0"){
        month1f = stoi(month1.substr(1,2));
    }
    else {
        month1f = stoi(month1.substr(0,2));
    }

    if (month2.substr(0,1) == "0"){
        month2f = stoi(month2.substr(1,2));
    }
    else {
        month2f = stoi(month2.substr(0,2));
    }
    int year1f = stoi(year1);
    int year2f = stoi(year2);
    month1f--;
    month2f--;

    int qnt1 = 0; //первая разность между нулем и конкретной датой в днях
    int qnt2 = 0; //вторая разность между нулем и конкретной датой в днях
    switch (month1f) {
    case 1:
        qnt1 = 31;
        break;
    case 2:
        qnt1 = 59;
        break;
    case 3:
        qnt1 = 90;
        break;
    case 4:
        qnt1 = 120;
        break;
    case 5:
        qnt1 = 151;
        break;
    case 6:
        qnt1 = 181;
        break;
    case 7:
        qnt1 = 212;
        break;
    case 8:
        qnt1 = 243;
        break;
    case 9:
        qnt1 = 273;
        break;
    case 10:
        qnt1 = 304;
        break;
    case 11:
        qnt1 = 334;
        break;
        case 0:
            qnt1 = 0;
            break;
    default:
        cout << "Проверьте правильность ввода месяца" << endl;
} //кейсы для месяца (ввод 1,2,3 и т.д.)
    switch (month2f) {
    case 1:
        qnt2 = 31;
        break;
    case 2:
        qnt2 = 59;
        break;
    case 3:
        qnt2 = 90;
        break;
    case 4:
        qnt2 = 120;
        break;
    case 5:
        qnt2 = 151;
        break;
    case 6:
        qnt2 = 181;
        break;
    case 7:
        qnt2 = 212;
        break;
    case 8:
        qnt2 = 243;
        break;
    case 9:
        qnt2 = 273;
        break;
    case 10:
        qnt2 = 304;
        break;
    case 11:
        qnt2 = 334;
        break;
        case 0:
            qnt2 = 0;
            break;
        default:
        cout << "Проверьте правильность ввода месяца" << endl;
}

    for (int i = 0; i < year1f+1;i++ ) {
        if (i % 4 == 0) {
            vis_add1 += 1;
        }
    }
    for (int i = 0; i < year2f+1;i++ ) {
        if (i % 4 == 0) {
            vis_add2 += 1;
        }
    }

    int range1 = (year1f*365 + day1f + qnt1 + vis_add1); //подсчёт разности между нулем и первой датой в днях
    int range2 = (year2f*365 + day2f + qnt2 + vis_add2); //подсчёт разности между нулем и второй датой в днях

    if (range1 > range2) {
        res = range1 - range2;
        if (res % 10 == 1){
            cout << res << " " << "день";
        }
        if ((res % 10 == 2) or (res % 10 == 3) or (res % 10 == 4)) {
            cout << res << " " << "дня";
        }
        if ((res % 10 == 5) or (res % 10 == 6) or (res % 10 == 7) or (res % 10 == 8) or (res % 10 == 9) or (res % 10 == 0)) {
            cout << res << " " << "дней";
        }
    }
    if (range1 <= range2) {
        res = range2 - range1;
        if (res % 10 == 1){
            cout << res << " " << "день";
        }
        if ((res % 10 == 2) or (res % 10 == 3) or (res % 10 == 4)) {
            cout << res << " " << "дня";
        }
        if ((res % 10 == 5) or (res % 10 == 6) or (res % 10 == 7) or (res % 10 == 8) or (res % 10 == 9) or (res % 10 == 0)) {
            cout << res << " " << "дней";
        }
    }

    cout << endl;
    return 0;

}