#include <iostream>
#include <iomanip>
//#include "dbmsLib5.h"
#include "dbmsLib_v2.h"
using namespace std;
int menu(){
	cout<<"================= МАКЕТ СУБД ===================\n";
	cout<<"\t1 - Чтение БД из файла\n";
	cout<<"\t2 - Печать БД\n";
	cout<<"\t3 - Запись БД в файл\n";
	cout<<"\t8 – Тестирование разрабатываемых функций\n";
	cout<<"\t10 - Выход\n"; 
	int choice;
	cout<<"Выберите действие\n";
	cin>>choice;
	while(cin.fail()){
	cout<<"Ошибка ввода. Повторите ввод\n";	
	cin.clear();
	cin.ignore(10,'\n');
	cin>>choice;
	}
	return choice;
}

void testing(string dbName){	
	cout <<"dbName="<<dbName<<endl;
	dbmsLib::DBTableSet db(dbName);
	/*db.PrintDB(44);
	cout<<"Измените \"в ручную\" одну из таблиц БД"<<endl;
	system("pause");*/

	
	ReadDB5(db);
	
	//db.PrintDB(78);
	WriteDB5(db);
	PrintDB5(db, 44);
	/*dbmsLib::WriteDB5(db);
	dbmsLib::ReadDB5(db);
	dbmsLib::PrintDB5(db,78);	*/
}

int main(){
	system("chcp 1251>nul");
	//cout<<"Введите имя БД\n"; //"LibraryTxt" 
	//для удобства тестирования при отладке выполняем присваивание
	string dbName("LibraryTxt");
	//cin>>dbName;
	cout<<dbName<<endl;
	//string tabName("Students");
	//cin>>tabName;
	//	cout<<"Введите ширину экрана в символах\n";
	int screenWidth=80;
	//	cin>>screenWidth;
	dbmsLib::DBTableSet db(dbName);	
	while(true){
		switch(menu()){
			case 1: db.ReadDB();
				break;
			case 2: db.PrintDB(screenWidth);
				break;
			case 3: db.WriteDB();
				break;
			case 8:testing(dbName);
				break;
			case 10: return 0;//завершение работы
			default:cout<<"Недопустимое действие. Повторите выбор\n"; 
				break;
		}
	}
		return 0;
}	