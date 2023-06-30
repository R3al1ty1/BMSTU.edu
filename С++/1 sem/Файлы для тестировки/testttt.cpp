#include <iostream>
#include <string>

using namespace std;


int main() {
    string str[] = {"d","e","l","a"};
    string arr[] = {"a", "e", "o", "i", "u"};
    bool prevSoglas = true;
    bool currSoglas = true;
    bool word_flag = true;
    for (int f = 0; f < sizeof(arr) / sizeof(arr[0]); f++) {
        if (str[0] == arr[f]) {
            prevSoglas = false;
        }
    }
    for (int k = 1; k < sizeof(str) / sizeof(str[0]); k++ ) {
        for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
            if (str[k] == arr[i])
                currSoglas = false;
        }
        if (currSoglas == prevSoglas) {
            word_flag = false;
            break;
        }
        else {
            prevSoglas = currSoglas;
            currSoglas = true;
        }
    }
    if (word_flag == 1) {
        cout << "подходит" << endl;
    }
    else {
        cout << "не подходит" << endl;
    }
    return true;
}