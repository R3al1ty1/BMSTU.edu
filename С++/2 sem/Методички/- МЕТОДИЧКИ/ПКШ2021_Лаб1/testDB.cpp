#include <iostream>
#include <iomanip>
#include "dbmsLib_v1_1.h"
using namespace std;
int menu(){
	cout<<"================= МАКЕТ СУБД ===================\n";
	cout<<"\t1 - Чтение таблицы из файла\n";
	cout<<"\t2 - Печать таблицы\n";
	cout<<"\t3 - Запись таблицы в файл\n";
	cout<<"\t4 - Добавление записи в таблицу\n";
	cout<<"\t5 - Перевести студента в другую группу\n";
	cout<<"\t6 - Распечатать фамилию студента, StudentID которого равен 3\n";
	cout<<"\t7 - Увеличить на 1 количество экземпляров всех книг в библиотеке \n";
	cout<<"\t8 - Тестирование\n";
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

//-----------------------------------------------------------------

void testing(string dbName, string tabName){
	string intStr("  12.3.2020   ");
	dbmsLib::DBDate dat(intStr);
	cout<<dat<<endl;
	cout <<"dbName="<<dbName<<"  tabName="<<tabName<<endl;
	string path="..\\"+dbName+"\\";
	int screenWidth=40;
	dbmsLib::DBTableTxt tab;
	tab.ReadDBTable(path+tabName+".txt");
	tab.PrintTable(screenWidth);
	string value = tab.valueToString(tab[0],"Author");
	int id;
	cout <<*(string*)dbmsLib:: GetValue(value, "Author",tab.GetHeader())<<endl;
	/*dbmsLib::Strip* strips;
	int nStrip;
	tab.CreateTableMaket(strips, nStrip,screenWidth);
	cout<<"nStrip="<<nStrip<<endl;
	for(int i=0;i<nStrip;i++){
		cout<<"strip="<<i<<endl;
		for(int j=0;j<strips[i].nField;j++)
			cout<<strips[i].fieldWidth[j]<<' ';
		cout<<endl;
	}*/

}

//=================================================
int main(){
	system("chcp 1251>nul");
	//cout<<"Введите имя БД\n"; //"LibraryTxt" 
	//для удобства тестирования при отладке выполняем присваивание
	string dbName("LibraryTxt");
	//cin>>dbName;
	cout<<dbName<<endl;
	//cout<<"Введите имя таблицы БД\n";
	//"Students" "Abonements" "Books"- для LibraryTxt
	//для удобства тестирования при отладке выполняем присваивание
	string tabName("Students");	
	//cin>>tabName;
	dbmsLib::DBTableTxt tab;//создание пустой таблицы класса DBTableTxt,
		//определенного в подключенной к проекту библиотеке dbmsLib
	string path="..\\"+dbName+"\\";
	//	cout<<"Введите текущую дату dd.mm.yyyy\n";
	//для удобства тестирования при отладке выполняем присваивание
	string str("11.02.2020");
	//	cin>>str;
	dbmsLib::DBDate today(str);
	//	cout<<"Введите ширину экрана в символах\n";
	int screenWidth=78;
	//	cin>>screenWidth;
	int ind;
	vector<int> indexes;	
	while(true){
		switch(menu()){
		case 1: tab.ReadDBTable(path+tabName+".txt");//Чтение таблиц БД. 
			//БД хранится в папке "..\\"+dbName+". 
			//Имя БД оканчивается или на Txt, если таблицы БД хранятся в текстовых файлах,
			//Каждая таблица хранится в отдельном файле с именем = <имя таблицы>+".txt"
			//Структура файла:
			//Первая строка файла содержит имя таблицы и имя столбца с первичным ключем
			//Вторая строка файла - заголовок таблицы
			//Все последующие строки - записи таблицы. 
				break;
			case 2: tab.PrintTable(screenWidth);//Печать таблицы БД (screenWidth-ширина экрана)
				break;
			case 3: tab.WriteDBTable(path+tabName+".txt");
				break;
			case 4: tab.AddRow(tab.CreateRow(),tab.GetSize());
				break;
			case 5:*(string*)tab[3]["Group"]="IU5-24b";
				break;
			case 6: ind=3;
				 indexes=tab.IndexOfRecord(&ind,"StudentID");
				cout<<*(string*)tab[indexes[0]]["Name"]<<endl;
				break;
			case 7: tabName="Books";
				tab.ReadDBTable(path+tabName+".txt");
				for(int i=0;i<tab.GetSize();i++)
					(*(int*)tab[i]["Quantity"])++;
				break;
			case 8:testing( dbName, tabName);
				break;
			case 10: return 0;//завершение работы
			default:cout<<"Недопустимое действие. Повторите выбор\n"; 
				break;
		}
	}
		return 0;
}