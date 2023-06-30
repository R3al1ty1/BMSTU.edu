#include "Lab42_8.h";



#include <iostream>
#include <iomanip>
using namespace std;
using namespace dbmsLib8;
//----------menu( )---------------------------------  
int menu() {
    cout << "================= МАКЕТ СУБД ===================\n";
    cout << "\t1 - Add row (Students), добавляем нового студента\n";
    cout << "\t2 - SelfRows (Books), оставляем авторов, чье имя совпадает с первым автором\n";
    cout << "\t3 - IndexOfRecord\n";
    cout << "\t10 - Выход\n";
    int choice;
    cout << "Выберите действие\n";
    cin >> choice;
    while (cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод\n";
        cin.clear();
        cin.ignore(10, '\n');
        cin >> choice;
    }
    return choice;
}



void testing(string dbName, dbmsLib8::DBTableSet8 db) {


    dbmsLib8::Condition static cond = Equal;

    string path = "..\\" + dbName + "\\";
    dbmsLib8::DBTableTxt8 tab;

    tab.ReadDBTable8(path + "Students" + ".txt");

    tab.PrintTable8(80);
    string tabName("Students");
    void* d;
    cin >> d;
    tab.SelfRows8("id", cond, d);
    //tab.PrintTable8(80);
}



int main() {
	system("chcp 1251>nul");
	int printSize = 80;
	string dbNames[2] = { "LibraryTxt", "LibraryBin" };
	string tabNames[3] = { "Abonements", "Books", "Students" };
	dbmsLib8::DBTableTxt8 tab1;
	dbmsLib8::DBTable8* tab2;
	string pathTxt = "..\\" + dbNames[0] + "\\";
	vector <int> Indexes;
    void* vPoint;
	while (true) {
		switch (menu()) {
		case 1:
			tab1.ReadDBTable8(pathTxt + tabNames[2] + ".txt");
			tab1.PrintTable8(printSize);
            tab1.AddRow(tab1.CreateRow(), tab1.GetSize8());
         //   tab1.WriteDBTable8(pathTxt + tabNames[2] + ".txt");
            tab1.PrintTable8(printSize);
            break;
		case 2:
            cout << "Оставляем в таблице только первого автора" << endl;
			tab1.ReadDBTable8(pathTxt + tabNames[1] + ".txt");
			tab1.PrintTable8(printSize);
			tab2 = tab1.SelfRows8("Author", Equal, tab1[0]["Author"]);
			tab2->PrintTable8(printSize);
			break;

        case 3:
            tab1.ReadDBTable8(pathTxt + tabNames[2] + ".txt");
            tab1.PrintTable8(printSize);
            vPoint = tab1[0]["Name"];
            Indexes = tab1.IndexOfRecord(vPoint, "Name");
            cout << "Номера строк, в которых встречается первый студент (отсчет строк начинается с 0)" << endl;
            for (int i = 0; i < Indexes.size(); i++) {
                cout << Indexes[i] << endl;
            }
            break;
		case 10:
			return 0;
		}
	}
}