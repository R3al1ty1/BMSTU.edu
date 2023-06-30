#include <iostream>
#include "Sort.h"
#include <string>
#include <random>
#include <iomanip>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};
struct Student {
    string name;
    Date birthDay;
    char id[8];
};

int Menu() {
    cout << "\n================СОРТИРОВКА МАССИВОВ===================\n";
    cout << "\t1 - Список группы студентов\n";
    cout << "\t2 - miniMax: Сортировка по убыванию даты рождения\n";
    cout << "\t3 - bubbleEnd: Сортировка по убыванию даты рождения\n";
    cout << "\t4 - miniMax: Сортировка по возрастанию id студента\n";
    cout << "\t5 - bubbleEnd: Сортировка по возрастанию id студента\n";
    cout << "\t6 - miniMax: Сортировка по возрастанию имени студента\n";
    cout << "\t7 - bubbleEnd: Сортировка по возрастанию имени студента\n";
    cout << "\t8 - Создание и инициализация динамического массива из cnt целых чисел\n";
    cout << "\t9 - Изменение значения элемента динамического массива\n";
    cout << "\t10 - miniMax: Сортировка целочисленного динамического массива по убыванию\n";
    cout << "\t11 - bubbleEnd: Сортировка целочисленного динамического массива по возрастанию\n";
    cout << "\t0 - Выход\n";
    cout << "======================================================\n";
    int choice;
    cout << "Выберите действие: ";
    cin >> choice;
    while (cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод\n";
        cin.clear();
        cin.ignore(10, '\n');
        cin >> choice;
    }
    return choice;
}

bool cmpDate(Student cmp1, Student cmp2) {
    if (cmp1.birthDay.year != cmp2.birthDay.year) {
        return cmp1.birthDay.year > cmp2.birthDay.year;
    }
    else {
        if (cmp1.birthDay.month != cmp2.birthDay.month)
            return cmp1.birthDay.month > cmp2.birthDay.month;
        else {
            if (cmp1.birthDay.day != cmp2.birthDay.day)
                return cmp1.birthDay.day > cmp2.birthDay.day;
        }
    }
}

bool cmpName(Student cmp1, Student cmp2) {
    return cmp1.name < cmp2.name;
}

bool cmpID(Student cmp1, Student cmp2) {
    return strcmp(cmp1.id, cmp2.id) < 0;
}

bool cmpMore(int n1, int n2) {
    return n1 > n2;
}

bool cmpLess(int n1, int n2) {
    return n1 < n2;
}

int printDate(int& frst, int& scnd, int& thrd, string& d, char e[]) {
    cout << "\n" << d << "\t";
    if (frst < 10 && scnd < 10) {
        cout << "0" << frst << ".0" << scnd << "." << thrd << "\t";
    }
    else {
        if (frst < 10 && scnd >= 10) {
            cout << "0" << frst << "." << scnd << "." << thrd << "\t";
        }
        else {
            if (scnd < 10 && frst >= 10) {
                cout << frst << ".0" << scnd << "." << thrd << "\t";
            }
            else {
                if (scnd >= 10 && frst >= 10) {
                    cout << frst << "." << scnd << "." << thrd << "\t";
                }
            }
        }
    }
    cout << e << "\n";
    return 0;
}

int iRandom(int frst, int scnd) {
    return frst + ((scnd - frst + 1) * rand());
}

void randomArr(int*& arr, int& arsz) {
    cout << "Введите размер массива\n";
    cin >> arsz;
    arr = new int[arsz];
    srand((unsigned int)time(0));
    rand();
    for (int i = 0; i < arsz; i++) {
        arr[i] = iRandom(0, arsz);
    }
}

int main()
{

    int* arr = 0;
    int arrsize = 0, indx = 0;

    int nCmp = 0, nSwp = 0;
    Student group[] = {
            {"Андрей", {9, 9, 2003}, "1234569"},
            {"Иван", {9, 10, 2003}, "1234567"},
            {"Ольга", {1, 1, 2004}, "1234560"},
            {"Игорь", {1, 10, 2003}, "0123456"},
            {"Мария", {30, 1, 2003}, "0034567"},
    };
    int cnt = sizeof(group) / sizeof(Student);
    Student* orig = new Student[cnt];
    for (int i = 0; i < cnt; i++) {
        orig[i] = group[i];
    }

    while (true) {
        switch (Menu()) {
            case 1:
                cout << "Исходный список группы студентов:\n";
                for (int i = 0; i < cnt; i++) {
                    printDate(orig[i].birthDay.day, orig[i].birthDay.month, orig[i].birthDay.year,
                              orig[i].name, orig[i].id);
                }
                cout << "\n\n";
                break;
                system("cls");
            case 2:
                cout << "miniMax: Сортировка по убыванию даты рождения студента\n";
                for (int i = 0; i < cnt; i++) {
                    group[i] = orig[i];
                }
                MinMax(group, cnt, cmpDate, nCmp, nSwp);
                for (int i = 0; i < cnt; i++) {
                    printDate(group[i].birthDay.day, group[i].birthDay.month, group[i].birthDay.year,
                              group[i].name, group[i].id);
                }
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                cout << "\n\n";
                break;

            case 3:
                cout << "bubbleEnd: Сортировка по убыванию даты рождения студента\n";
                for (int i = 0; i < cnt; i++) {
                    group[i] = orig[i];
                }
                Bubble(group, cnt, cmpDate, nCmp, nSwp);
                for (int i = 0; i < cnt; i++) {
                    printDate(group[i].birthDay.day, group[i].birthDay.month, group[i].birthDay.year,
                              group[i].name, group[i].id);
                }
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                cout << "\n\n";
                break;

            case 4:
                cout << "miniMax: Сортировка по возрастанию id студента\n";
                for (int i = 0; i < cnt; i++) {
                    group[i] = orig[i];
                }
                MinMax(group, cnt, cmpID, nCmp, nSwp);
                for (int i = 0; i < cnt; i++) {
                    printDate(group[i].birthDay.day, group[i].birthDay.month, group[i].birthDay.year,
                              group[i].name, group[i].id);
                }
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                break;

            case 5:
                cout << "bubbleEnd: Сортировка по возрастанию id студента\n";
                for (int i = 0; i < cnt; i++) {
                    group[i] = orig[i];
                }
                Bubble(group, cnt, cmpID, nCmp, nSwp);
                for (int i = 0; i < cnt; i++) {
                    printDate(group[i].birthDay.day, group[i].birthDay.month, group[i].birthDay.year,
                              group[i].name, group[i].id);
                }
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                cout << "\n\n";
                break;

            case 6:
                MinMax(group, cnt, cmpName, nCmp, nSwp);
                for (int i = 0; i < cnt; i++) {
                    group[i] = orig[i];
                }
                for (int i = 0; i < cnt; i++) {
                    printDate(group[i].birthDay.day, group[i].birthDay.month, group[i].birthDay.year,
                              group[i].name, group[i].id);
                }
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                cout << "\n\n";
                break;

            case 7:
                Bubble(group, cnt, cmpName, nCmp, nSwp);
                for (int i = 0; i < cnt; i++) {
                    group[i] = orig[i];
                }
                for (int i = 0; i < cnt; i++) {
                    printDate(group[i].birthDay.day, group[i].birthDay.month, group[i].birthDay.year,
                              group[i].name, group[i].id);
                }
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                cout << "\n\n";
                break;

            case 8:
                system("cls");
                delete[] arr;
                randomArr(arr, arrsize);
                cout << "\n\n";
                break;

            case 9:
                cout << "Введите индекс изменяемого элемента массива\n";
                cin >> indx;
                cout << "Введите новое значение элемента\n";
                cin >> arr[indx - 1];
                cout << "\n\n";
                break;

            case 10:
                MinMax(arr, arrsize, cmpMore, nCmp, nSwp);
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                cout << "\n\n";
                break;

            case 11:
                Bubble(arr, arrsize, cmpLess, nCmp, nSwp);
                cout << "\n\nSwaps = " << nSwp << "\nCompares = " << nCmp;
                cout << "\n\n";
                break;

            case 0:
                return 0;
                break;
        }
    }
    system("pause");
    return 0;
}