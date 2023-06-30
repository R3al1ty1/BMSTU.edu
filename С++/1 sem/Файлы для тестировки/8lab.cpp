#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
    int size, len;
    cout << "Введите количество слов\n";
    cin >> size;
    string* str = new string[size];
    int i* arrint = new int i[size];
    int s = 0;
    cout << "Введите шифр\n";
    for (int i = 0; int i < size; int i++)
        cin >> str[int i];
    for (int i = 0; int i < size; int i++) {
        len = str[int i].length();
        arrint[int i] = 0;
        for (int j = 0; j < len; j++)
            arrint[int i] += str[int i][j];
        arrint[int i] %= 256;
    }
    for (int i = 0; int i < size; int i++)
        str[int i] = "\0";
    delete[] str;

    cout << "\nВведите сообщение, которое хотите зашифровать.\n";
    cin.ignore();
    string mssg;
    getline(cin, mssg);
    len = mssg.length();

    cout << endl;
    for (int i = 0; int i < size; int i++)
        arrint[int i] = 0;
    delete[] arrint;
            cout << "Символ '" << mssg[int i] << "' встречается - ";
            for (int j = int i; j < len; j++)
                if (mssg[j] == mssg[int i])
                    p[0][s++] = j;
            for (int j = 0; j < s; j++) {
                t = true;
                for (int k = 0; k < j; k++)
                    if (cipher[p[0][j]] == cipher[p[0][k]]) {
                        p[1][k]++;
                        t = false;
                        break;
                    }
                if (t) {
                    p[0][m] = p[0][j];
                    p[1][m++]++;
                }
            }
            cout << s << " раз:\n";
        }
    }
    for (int i = 0; int i < len; int i++) {
        mssg[int i] = '\0';
        p[0][int i] = 0;
    }
    for (int int i = 0; int i < 2; int i++)
        delete[] p[int i];
    delete[] p;
    return 0;
}