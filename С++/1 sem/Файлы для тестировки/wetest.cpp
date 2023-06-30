#define _CRT_SECURE_NO_WARNINGS
//для отключения оповещения о небезопасности strcpy
//#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string.h>

/*
#include "dzLibrary1.cpp"//модуль с базовыми функциями всех //членов группы, обеспечивающими загрузку вводимого текста в //структуру Text:
char* txt = InputText(); //ввод текста с клавиатуры
char ch = text.sentence[i].words[j][k]; , где
ch - k-й символ j-го слова в i-ом предложении
тогда ch - text[i][j][k]
*/

using namespace std;

const int MaxWords = 50; // максимальное кол-во слов
const int maxSentences = 10; // максимальное кол-во предложений

struct Sentences {
    char* words[MaxWords];  //массив указателей на слова в предл.
    int CntWords;
    char*& operator[](int index);  //перегрузка оператора индексации
    int wordsRepeats[MaxWords]; //массив признаков слов
    Sentences();                   //КОНСТРУКТОР
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
void dz0(Text&);
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
    cin >> choice;
    while (cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод\n";
        cin.clear();
        cin.ignore(10, '\n');
        cin >> choice;
    }
    return choice;
}

// :: - расширение области видимости
Sentences::Sentences() {
    CntWords = 0;

    for (int i = 0; i < MaxWords; i++) {
        words[i] = 0;
        wordsRepeats[i] = 0; //массива повторов (изначально нулевой)
    }
}

Text::Text() {
    CntSentences = 0;

    for (int i = 0; i < maxSentences; i++)
        sentenceAttributes[i] = 0;
}

Sentences& Text::operator[](int index) {
    return sentences[index];
}

char*& Sentences::operator[](int index) {
    return words[index];
}

// ostream - метод для форматирования
ostream& operator << (ostream& out, Sentences& sentence) {
    for (int i = 0; i < sentence.CntWords; i++)
        out << sentence.words[i] << " ";
    out << '\b';
    return out;
}

ostream& operator << (ostream& out, Text& text) {
    for (int i = 0; i < text.CntSentences; i++)
        out << text.sentences[i] << '.' << endl;
    return out;
}

/*
ввод текста с клавиатуры с разбиением на предложения
Вводит текст из латинских букв, пробелов и знаков пунктуации (, .),
заканчивающийся символом 'Ctrl^Z' - код 26.
*/
char* TextInput() {
    int n = 100, count = 0; //n - начальный размер буфера
    char* mas = new char[n]; // массив с символами - это строка
    char CurrentSymb;

    cout << "Введите текст, заканчивающийся символом /:" << endl;
    do {
        CurrentSymb = getchar(); // ASCII код символа ch ввод символов
        if (CurrentSymb != char(26)) {
            if (CurrentSymb >= 'A' && CurrentSymb <= 'Z' ||
                CurrentSymb >= 'a' && CurrentSymb <= 'z' ||
                CurrentSymb == ' ' || CurrentSymb == '.' ||
                CurrentSymb == ',' || CurrentSymb == '?')
            {
                mas[count++] = CurrentSymb;
                putchar(CurrentSymb); //вывод вводимого символа на экран
            }
                //удаление ошибочного введенного ДОПУСТИМОГО символа с экрана и из буфера
            else if (CurrentSymb == '\b') { // \b - перемещение курсора в предыдущую позицию
                cout << "\b \b"; //удаление символа с экрана
                count--; //удаление символа из буфера str.
            }
            else //для недопустимых
                cout << char(7) << "\a"; //звук писка? char(7) = \a
        }
        else break;
    } while (true);

    mas[count] = '\0'; // \0 конец строки (обозначаем конец текста)
    int size = strlen(mas) + 1;
    char* arr = new char[size]; // символьная строка с текстом

    strcpy(arr, mas); // копирование символов
    delete[]mas;

    return arr;
}

void GetSentence(char* str, Sentences& sent) {
    //Sentence sentence = *new Sentence;
    sent.CntWords = 0;
    const char* WordSplit = " ,";
    char* CurrentWord, * NextWord = str;

    while (CurrentWord = strtok_r(NextWord, WordSplit, &NextWord))
        sent.words[sent.CntWords++] = CurrentWord;
}

// получение набора предложений
void GetText(char* txt, Text& text) {
    const char* sentenceDelim = ".";
    char* token, * nextToken = txt;
    while (token = strtok_r(nextToken, sentenceDelim, &nextToken))
        GetSentence(token, text.sentences[text.CntSentences++]);
}

/*
	нахождение ранее использованных слов
	WordsRepeats = 0 - слово не повторялось, = 1 - первое вхождение, = 2 - повторное
*/
void FindUsedWords(Text& text) {
    for (int i = 0; i < text.CntSentences; i++) {
        for (int k = 0; k < text[i].CntWords; k++) {
            if (text.sentences[i].wordsRepeats[k] == 0) {
                for (int j = k + 1; j < text[i].CntWords; j++) {
                    if (strcmp(text[i][k], text[i][j]) == 0) {
                        text[i].wordsRepeats[j] = 2;
                        text[i].wordsRepeats[k] = 1;
                    }
                }
            }
        }
    }
}

// удаляем ранее использованные слова и пустые предложения
void ClearUsedWords(Text& text) {
    for (int i = 0; i < text.CntSentences; i++) {
        for (int k = 0; k < text[i].CntWords; k++) {
            if ((text[i].wordsRepeats[k] != 0)) {
                for (int j = k; j < text[i].CntWords - 1; j++) {
                    text[i][j] = text[i][j + 1];
                    text[i].wordsRepeats[j] = text[i].wordsRepeats[j + 1];
                }

                --text[i].CntWords; //значение параметра уменьшается, а память,
                //выделенная new (массив txt), не изменяется
                --i;
            }
        }

        if (text[i].CntWords == 0) { // удаление предложения, которое стало пустым
            for (int j = i; j < text.CntSentences - 1; j++)
                text[j] = text[j + 1];

            --text.CntSentences;
            --i;
        }
    }
}


void Creating_mas(Text& text)
{
    const int arr_size = 15;
    int masspovt[arr_size];
    const char* razlmass[arr_size];
    for (int t = 0; t < arr_size; t++)
    {
        razlmass[t] = "t";
        masspovt[t] = 0;
    }
    int sch = 0;
    for (int i = 0; i < text.CntSentences; i++)
    {
        for (int k = 0; k < text[i].CntWords; k++)
        {
            bool fl = true;
            for (int j = 0; j < arr_size; j++)
            {
                if (strcmp(text[i][k], razlmass[j]) == 0)
                {
                    fl = false;
                }
            }
            if (fl == true)
            {
                razlmass[sch] = text[i][k];
                sch++;
            }
        }
    }
    for (int i = 0; i < sch; i++)
    {
        for (int j = 0; j < text.CntSentences; j++)
        {
            for (int k = 0; k < text[j].CntWords; k++)
            {
                if (strcmp(text[j][k], razlmass[i]) == 0)
                {
                    masspovt[i] += 1;
                }
            }
        }
    }
    cout << "Вывод количества вхождений в текст" << endl;
    for (int i = 0; i < sch; i++)
    {
        cout << razlmass[i] << " - " << masspovt[i] << endl;
    }

    for (int i = 0; i < text.CntSentences; ++i)
    {
        for (int k = 0; k < text[i].CntWords; ++k)
        {
            for (int j = 0; j < sch; ++j)
            {
                if ((strcmp(text[i][k], razlmass[j]) == 0) && (masspovt[j] > 1))
                {
                    //cout <<;
                    for (int t = k; t < text[i].CntWords - 1; ++t)
                    {
                        text[i][t] = text[i][t+1];
                        //cout << text[i][j] << "\n";
                    }
                    //cout << "\n\nROFL\n";
                    --text[i].CntWords;
                    --i;
                    masspovt[j] -= 1;
                }
            }
        }
    }
}

/*for (int i = text.CntSentences-1; i>=0; i--)
	{
		for (int k = text[i].CntWords-1; k >= 0; k--)
		{
			for (int j = 0; j < sch; j++)
			{
				if (strcmp(text[i][k], razlmass[j]) == 0)
				{
					if (masspovt[j] > 1)
					{
						for (int t = k; t < text[i].CntWords - 1; t++)
						{
							text[i][t] = text[i][t + 1];
						}
						--text[i].CntWords;
						--i;
						masspovt[j] -= 1;
					}
				}
			}
		}
	}*/


void dz(Text& text) {
    dz0(text);
}

// копирование введенного текста в программу - копия для ТЕСТИРОВАНИЯ
char* TextFill() {
    const char* testTxt = "Шла Саша шоссе по по. Саша сосала сушку шоссе.";
    int size = strlen(testTxt) + 1;
    char* txt = new char[size];
    strcpy(txt, testTxt); // ( куда переносится , откуда переносится )

    return txt;
}

int main() {
    system("chcp 1251 >nul");
    char* txt = 0; //динамическая память, которая используется в программе, выделяется только под тхт
    Text text;
    char ch = 'x';

    while (true) {
        switch (menu()) {
            case 1:
                system("cls");
                cout << "Ввод текста с клавиватуры" << endl;
                cout << "-------------------------\n" << endl;

                txt = TextFill(); //txt = TextFill(); txt = TextInput();
                cout << "\n\nProof:" << "\n\n" << txt << endl;

                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                cout << "Зaполнение структуры Text" << endl;
                cout << "-------------------------\n" << endl;

                GetText(txt, text);
                cout << text << endl;
                //cout << text[1] << endl;

                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                cout << "Тестирование" << endl;
                cout << "-------------------------\n" << endl;
                //i  j  k
                cout << text[1][1][1] << endl; //выводит 39 букву - 2 предл; 2 слово; 2 буква
                //i - предложение; j - слово; k - буква

                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                cout << "Индивидуальное ДЗ" << endl;
                cout << "-------------------------\n" << endl;

                //dz(text);
                Creating_mas(text);
                cout << "Final:\n";
                cout << text;
                system("pause");
                system("cls");

                break;
            case 5:
                /*cout << txt << endl;
                delete[]txt;
                cout << txt << endl; */
                cout << "Программа завершена." << endl;

                return 0;
        }
    }

    return 0;
}

void dz0(Text& text) {
    FindUsedWords(text);
    cout << "Repeats:\n";
    for (int k = 0; k < text.CntSentences; k++) {
        for (int i = 0; i < text[k].CntWords; i++)
            cout << text[k].wordsRepeats[i] << " ";
        cout << endl;
    }
    ClearUsedWords(text);
    cout << "Final:\n";
    cout << text;
}