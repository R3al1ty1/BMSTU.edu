#include <iostream>
using namespace std;

int main() {
    string quest = "y";
    do {
        int hours, minutes;
        string vrs; //определе0ние времени суток
        bool ex_m = false; //переменная, которая указывает на то, когда выводить "ровно" (минуты), ex_m - exact minutes (точные минуты, подразумевается "ровно").
        cout << "Введите, который час: ";
        cin >> hours >> minutes;

        if (hours > 23 || minutes > 60 || hours < 0 || minutes < 0) { //проверка правильности введения значений времени
            cout << "Проверьте правильность введенных данных.";
        }
        else {
            if (hours == 12 && minutes == 0) {
                cout << "Полдень";
            }
            else if (hours == 0 && minutes == 0){
                cout << "Полночь";
            }
            else if (hours != 0 || minutes != 0){
                if (hours >= 5 && hours < 12){
                    vrs = " утра";
                }
                else if (hours >= 12 && hours < 18) {
                    vrs = " дня";
                }
                else if (hours >= 18 && hours <= 23) {
                    vrs = " вечера";
                }
                else if (hours >= 0 && hours < 5) {
                    vrs = " ночи";
                }
                if (hours > 12){ //переход из 24-часового формата вывода в 12-часовой с сохранением понимания времени суток (день, ночь и т.п.) благодаря vrs
                    hours -= 12;
                }
                cout << hours << " час";
                if (hours > 1 && hours < 5) { //добавление падежного окончания (часы)
                    cout << "a";
                }
                if (hours > 4 || hours == 0 || hours == 12) {
                    cout << "ов";
                }
                if (minutes == 0) {
                    ex_m = true;
                }
                else {
                    cout << " " << minutes << " минут"; //вывод минут
                    if (minutes % 10 > 1 && minutes % 10 < 5 && (minutes < 11 || minutes > 20)) { //добавление падежного окончания (минуты)
                        cout << "ы";
                    }
                    else if (minutes % 10 == 1 && minutes != 11) {
                        cout << "а";
                    }
                }
                cout << vrs;
                }
                if (ex_m){
                    cout << " ровно";
                    }
                }
            cout << endl;
            cout << "Продолжить работу? y/n " << endl;
            cin >> quest;
            }
        while(quest.substr(0,1) != "n");
        cout << endl;
        return 0;
    }