#include <iostream>
#include <conio.h>
#include <iomanip>
#include <sortTemplate.h>
using namespace std;

struct Student {
    string name;
    int year;
    char id[6];
};

bool compare1(Student obj1, Student obj2) {
    return obj1.year > obj2.year;
}
bool compare2(Student obj1, Student obj2) {
    return obj1.name > obj2.name;
}
bool compare3(Student obj1, Student obj2) {
    return strcmp(obj1.id, obj2.id) < 0;
}
bool iCmp1(int n1, int n2) {
    return n1 > n2;
}
bool iCmp2(int n1, int n2) {
    return n1 < n2;
}

