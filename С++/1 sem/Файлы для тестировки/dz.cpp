#include <iostream>
//#include <iomanip>
#include <curses.h>
#include <cstring>
//#include "dzLibrary1.cpp"//модуль с базовыми функциями всех //членов группы, обеспечивающими загрузку вводимого текста в //структуру Text:
//char* InputText();
//Text& GetText(char*);
//Sentence& GetSentence(char*);

//Ян - 22 вариант, Илья - 15 вариант, Костя - 14 вариант.

using namespace std;

const int MaxWords = 40; // максимальное кол-во слов
const int maxSentences = 10; // максимальное кол-во предложений

struct Sentences {
    char *words[MaxWords];
    int CntWords;
    char *&operator[](int index);
    int wordsAttributes[MaxWords];
    Sentences();
};

struct Text {
    Sentences sentences[maxSentences];
    int CntSentences;
    Sentences& operator[](int index);
    int sentenceAttributes[maxSentences];
    Text();
};

// прототипы функций:
char* TextInput();
void GetText(char*, Text&);
void GetSentence(char*, Sentences&);
int menu();
void dz(Text&);
void FindUsedWords(Text&);
void ClearUsedWords(Text&);
void DeletedWord(Sentences&);
char* TextFill();

int menu() {
    cout << "================ДЗ================\n";
    cout << "\t1. Ввод текста с клавиватуры\n";
    cout << "\t2. Заполнение структуры Text\n";
    cout << "\t3. Тестиование\n";
    cout << "\t4. Индивидуальное ДЗ\n";
    cout << "\t5. Выход\n";
    int choice;
    while(cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод\n";
        cin.clear();
        cin.ignore(5, '\n');
        cin >> choice;
    }
    return choice;
}

// :: - расширение области видимости
Sentences::Sentences() {
    CntWords = 0;

    for (int i = 0; i < MaxWords; i++) {
        words[i] = 0;
        wordsAttributes[i] = 0;
    }
}

Text::Text() {
    CntSentences = 0;

    for (int i = 0; i < maxSentences; i++)
        sentenceAttributes[i]=0;
}

Sentences& Text::operator[](int index) {
    return sentences[index];
}

char*& Sentences::operator[](int index) {
    return words[index];
}

// ostream - метод для форматирования
ostream& operator << (ostream& out, Sentences &sentence) {
    for (int i = 0; i < sentence.CntWords; i++)
        out << sentence.words[i] << " ";
    out << '\b';
    return out;
}

ostream& operator << (ostream& out, Text &text) {
    for(int i = 0; i < text.CntSentences; i++)
        out << text.sentences[i] << '.' << endl;
    return out;
}

// ввод текста с клавиатуры с разбиением на предложения
char* TextInput() {
    int n = 100, count = 0;
    char* mas = new char[n]; // массив с символами - это строка
    char CurrentSymb;

    cout << "Введите текст, заканчивающийся символом /:" << endl;
    do {
        CurrentSymb = getch(); // ASKII код символа ch
        if (CurrentSymb != char(26)) {
            if (CurrentSymb >= 'A' && CurrentSymb <= 'Z' ||
            CurrentSymb >= 'a' && CurrentSymb <= 'z' ||
            CurrentSymb == ' ' || CurrentSymb == '.' ||
            CurrentSymb == ',' || CurrentSymb == '?') {
                mas[count++] = CurrentSymb;
                putchar(CurrentSymb);
            }
            else if (CurrentSymb == '\b') {
                cout << "\b \b";
                count--;
            }
            else
                cout << char(7) << "\a";
        }
        else break;
    } while (true);

    //while ((ch = getch()) != char(26)) {

    //}

    mas[count] = '\0';
    int size = strlen(mas) + 1;
    char* arr = new char[size];

    strcpy(arr, mas); // копирование символов
    delete []mas;

    return arr;
}

// получение отдельного предложения
void GetSentence(char* str, Sentences& sent) {
    //Sentence sentence = *new Sentence;
    sent.CntWords = 0;
    // изначально: char* WordSplit = ","; // разделитель слов
    char* WordSplit[] = {(char*)",", (char*)":", (char*)";", (char*)"-"};
    char* CurrentWord, *NextWord = str;
    do {
        for (int i = 0; i < 4; i++) {
            CurrentWord = strtok_r(NextWord, WordSplit[i], &NextWord);
            sent.words[sent.CntWords++] = CurrentWord;
        }
    } while (true);

    //  изначально было так:
    //while(CurrentWord = strtok_r(NextWord, WordSplit, &NextWord))
    //    sent.words[sent.CntWords++] = CurrentWord;
}

// получение набора предложений
void GetText(char* txt, Text& text) {
    // изначально: char* SentenceSplit = ".";
    char* SentenceSplit[3] = {(char*)".", (char*)"!", (char*)"?"}; // возможные разделители предложений
    char* CurrentSymb, *NextSymb = txt;
    do {
        for (int i = 0; i < 3; i++) {
            CurrentSymb = strtok_r(NextSymb, SentenceSplit[i], &NextSymb);
            GetSentence(CurrentSymb, text.sentences[text.CntSentences++]);
        }
    } while (true);

    // изначально было:
    //while(CurrentSymb = strtok_r(NextSymb, SentenceSplit, &NextSymb))
     //   GetSentence(CurrentSymb, text.sentences[text.CntSentences++]);
}

// нахождение ранее использованных слов
void FindUsedWords(Text &text) {
    for (int i = 0; i < text.CntSentences; i++) {
        for (int k = 0 ; k < text[i].CntWords; k++) {
            if (text.sentences[i].wordsAttributes[k]==0) {
                for (int j = k+1; j <text[i].CntWords;j++) {
                    if (strcmp(text[i][k], text[i][j])==0) {
                        text[i].wordsAttributes[j] = 2;
                        text[i].wordsAttributes[k] = 1;
                    }
                }
            }
        }
    }
}

// удаляем ранее использованные слова
void ClearUsedWords(Text &text) {
    for(int i = 0; i < text.CntSentences; i++) {
        for(int k = 0; k < text[i].CntWords; k++) {
            if(text[i].wordsAttributes[k] != 1) {
                for (int j = k; j < text[i].CntWords-1; j++) {
                    text[i][j] = text[i][j+1];
                    text[i].wordsAttributes[j] = text[i].wordsAttributes[j+1];
                }

                --text[i].CntWords;
                --i;
            }
        }

        if(text[i].CntWords == 0) {
            for (int j = i; j < text.CntSentences-1;j++)
                text[j]=text[j+1];

            --text.CntSentences;
            --i;
        }
    }
}

// удаляем слова


// копирование введенного текста в программу
char* TextFill() {
    char* testTxt;
    int size = strlen(testTxt) + 1;
    char* txt = new char[size];
    strcpy(txt,testTxt); // ( куда переносится , откуда переносится )

    return txt;
}

int main() {
    system("chcp 1251 >nul");
    char *txt = 0;
    Text text;
    char ch = 'x';

    while(true) {
        switch (menu()) {
            case 1:
                system("cls");
                cout << "Ввод текста с клавиватуры" << endl;
                cout << "-------------------------\n" << endl;

                txt = TextInput();
                cout << txt << endl;

                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                cout << "Зaполнение структуры Text" << endl;
                cout << "-------------------------\n" << endl;

                GetText(txt, text);
                cout << text << endl;

                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                cout << "Тестирование" << endl;
                cout << "-------------------------\n" << endl;

                cout << text[1][1][1] << endl;
                cout << sizeof(Sentences) << endl;
                cout << sizeof(Text) << endl;

                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                cout << "Индивидуальное ДЗ" << endl;
                cout << "-------------------------\n" << endl;

                dz(text);

                system("pause");
                system("cls");

                break;
            case 5:
                cout << txt << endl;
                delete []txt;
                cout << txt << endl;
                cout << "Программа завершена." << endl;

                return 0;
        }
    }

    return 0;
}

// функции для открытия файла:

/*Text& GetText(char* txt) {
    Text text = *new Text;
    char* sentenceDelim = ".";
    char* token, *nextToken = txt;
    while (token = strtok_s(nextToken, sentenceDelim, &nextToken))
        text.sentences[text.nSentences++] = GetSentence(token);
    return text;
}*/

/*Sentence& GetSentence(char* str) {
    Sentence sentence = *new Sentence;
    sentence.nWords = 0;
    char* wordDelims = " ,";
    char* word, *nextWord = str;
    while(word = strtok_s(nextWord, wordDelims, &nextWord))
        sentence.words[sentence.nWords++] = word;
    return sentence;
}*/

/*void GetSentence(char* str, Sentence& sentence) {
    //Sentence sentence = *new Sentence;
    sentence.nWords = 0;
    char* wordDelims = " ,";
    char* word, *nextWord = str;
    while(word = strtok_s(nextWord, wordDelims, &nextWord))
        sentence.words[sentence.nWords++] = word;
    //return sentence;
}*/

// индивидуальная часть дз
void dz(Text &text) {
    cout << "" << endl;
}