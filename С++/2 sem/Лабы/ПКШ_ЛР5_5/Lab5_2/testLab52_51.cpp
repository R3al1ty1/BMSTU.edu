#include <iomanip>
#include <iostream>

#include "dbmsLib5.h"
#include "dbmsLib_v2.h"

using namespace std;
int menu (){
	cout<<"============ СОЗДАНИЕ БИНАРНОЙ БД ============\n";
	cout<<"\t1 - Чтение текстовой БД\n";
	cout<<"\t2 - Печать БД\n";
	cout<<"\t3 - Запись текстовой БД\n";
	cout<<"\t4 - Создание бинарной версии текстовой БД\n";
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


void testing(string dbName) {
  cout << "dbName=" << dbName;
  string path = "..\\" + dbName + "\\";
  dbmsLib5::DBTableSet5 db1(dbName);
  db1.PrintDB5(78);
  db1.WriteDB5();
  db1.ReadDB5(dbName);
  db1.PrintDB5(78);
}

void CreateBinaryDB() {
	vector<string> strArray;
	ifstream in;
	ifstream in1;
	string path="..\\LibraryBin\\";
	in.open(path+"DBTables.txt");
	if (in.is_open()) {
		
		// Заполнение вектора имен таблиц
		strArray.clear();
		string str;
		getline(in,str);
		string res;
		while (str.find('|') != string::npos) {
			res = str.substr(0, str.find_first_of('|'));
			strArray.push_back(res);
			str = str.substr(str.find_first_of('|') + 1);
		}
		strArray.push_back(str);

		dbmsLib5::DBTableTxt5 tab;
		for (auto i = 0; i < strArray.size(); ++i) {
			tab.ReadDBTable5("..\\LibraryTxt\\"+strArray[i]+".txt");
			tab.WriteTableBin5(path+strArray[i]+".bin"); 
		}
}

}

int main() {
  system("chcp 1251>nul");

	string dbName("LibraryTxt");

	cout<<dbName<<endl;

	string tabName("Abonements");	

	dbmsLib5::DBTableTxt5 tab;
	dbmsLib5::DBTableTxt5 tab2;
	string path="..\\"+dbName+"\\";

	string str("11.02.2020");

	dbmsLib::DBDate today(str);

	int screenWidth=78;

	int ind;
	vector<int> indexes;	
	while(true){
		switch(menu()){
		case 1: tab.ReadDBTable5(path+tabName+".txt");

				break;
			case 2: tab.PrintTable5(screenWidth);
				break;
			case 3: tab.WriteDBTable5(path+tabName+".txt");
				break;
			case 4: 
				CreateBinaryDB();
				break;
      case 8:
        testing(dbName);
        break;
      case 10:
        return 0;  //завершение работы
      default:
        cout << "Недопустимое действие. Повторите выбор\n";
        break;
    }
  }
  return 0;
}