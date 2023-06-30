#include <iostream>
#include <iomanip>
#include "dbmsLib_v2.h"
using namespace std;
using namespace dbmsLib;
int menu(){
	cout<<"================= МАКЕТ СУБД ===================\n";
	/*cout<<"\t1 - Чтение таблицы из файла\n";
	cout<<"\t2 - Печать таблицы\n";
	cout<<"\t3 - Запись таблицы в файл\n";
	cout<<"\t4 - Добавление записи в таблицу\n";
	cout<<"\t5 - Перевести студента в другую группу\n";
	cout<<"\t6 - Распечатать фамилию студента, StudentID которого равен 3\n";
	cout<<"\t7 - Увеличить на 1 количество экземпляров всех книг в библиотеке \n";*/
	cout<<"\t8 - Тестирование\n";
	//cout<<"\t10 - Выход\n"; 
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


void testing(string dbName,string tabName){
	string path="..\\"+dbName+"\\";
//Для проверки приложения Lab4_1 используем библиотечные функции
	dbmsLib::DBTableSet db(dbName); 
	/*db.PrintDB(80);
	db[tabName]->ReadDBTable(path+tabName+".txt");
	db[tabName]->PrintTable(80);*/
	dbmsLib::DBTableSet tab;
	dbmsLib::ReadDB7(tab);
	dbmsLib::PrintDB7(tab,80);
	dbmsLib::WriteDB7(tab);
}


int main(){
	system("chcp 1251>nul");
	string dbName("LibraryTxt");
	string tabName("Students");	
	string fileName("Students");
	dbmsLib::DBTableTxt tab;
	string path="..\\"+dbName+"\\";
	while(true){
		switch(menu()){
		    case 1: tab.ReadDBTable(path+tabName+".txt");
		
			case 8:testing( dbName, tabName);
				break;
			case 10: return 0;
		}
	}
}