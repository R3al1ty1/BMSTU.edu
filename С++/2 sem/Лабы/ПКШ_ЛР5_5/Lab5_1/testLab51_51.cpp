#include "dbmsLib_v2.h"

using namespace std;
int menu(){
	cout<<"=============== БИНАРНЫЕ ФАЙЛЫ ===============\n";
	cout<<"\t1 - Запись массива структур в бинарный файл\n";
	cout<<"\t2 - Чтение бинарного файла в массив структур\n";
	cout<<"\t3 - Ручное редактирование бинарного файла\n";
	cout<<"\t4 - Прямой доступ к данным\n";
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
	cout <<"testing()"<<dbName<<endl;
}

struct Date {
	int day;
	int month;
	int year;
};

void WriteDate(fstream& fio, Date*& dates1,int m){
	string path = "..\\date.bin";
	fio.open(path,ios::out|ios::binary);
    fio.write((char*)&m, sizeof(int));
	fio.write((char*)dates1,m*sizeof(Date));
	fio.close();
    }

void ReadDate(fstream& fio, Date*& dates2,int &size2){
	string path = "..\\date.bin";
	fio.open(path,ios::in|ios::binary);
    fio.seekg(0);
    fio.read((char*)&size2,sizeof(int));
	dates2=new Date[size2]; 
	fio.read((char*)dates2, size2*sizeof(Date));
    fio.close();
}

void PrintDate (Date* dates, int n) {
	cout << endl << "dates: " << endl << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "date" << i+1 << ": " << dates[i].day << '.' << dates[i].month << '.' << dates[i].year << endl;
		}
}

void DirectAccess(fstream& fio,Date *&dates,int m)
{
	string path = "..\\date.bin";
	fio.open(path , ios::out | ios::in  |ios::binary);

	cout<<"Перестановка в файле значений месяца в 0-ом и 1-ом элементах массива\n";
	int month1=dates[0].month;
	int pos = sizeof(int)+sizeof(Date)*1+sizeof(dates[1].day);
	fio.seekg(pos);
	fio.read((char*)&dates[0].month,sizeof(int));
	fio.seekp(8);
	fio.write((char*)&dates[1].month,sizeof(int));
	fio.seekp(20);
	fio.write((char*) &month1,sizeof(int));
	fio.seekg(20);
	fio.read((char*) &dates[1].month,sizeof(int));
	fio.close();
	
}


int main(){
	system("chcp 1251>nul");
	
	Date date1 = {28, 2, 2003};
	Date date2 = {12, 10, 2025};
	Date date3 = {2, 9, 1945};
	Date date4 = {25, 5, 2021};
	Date date5 = {31, 12, 2000};
	
	Date dates[] = {date1, date2, date3, date4, date5};
	int n = sizeof(dates)/sizeof(Date);
	Date* dates1 = new Date[n];
	for(int i=0;i<n;i++){ 
		dates1[i]=dates[i]; 
	} 
	Date* dates2;
	fstream fio;
	while(true){
		switch(menu()){
			case 1: 
				WriteDate(fio, dates1, n);
				break;
			case 2: 
				ReadDate(fio,dates2, n);
				PrintDate(dates2, n);
				break;
			case 3: 
				
				cout << endl << "Даты до изменения: " << endl;
				PrintDate(dates2, n);
				system("pause");
				cout << endl << "Даты после изменения: " << endl;
				PrintDate(dates2, n);

				break;
			case 4:
				cout << endl << "Даты до изменения: " << endl;
				PrintDate(dates2, n);
				DirectAccess(fio, dates2, n);
				cout << endl << "Даты после изменения: " << endl;
				ReadDate(fio,dates2, n);
				PrintDate(dates2, n);

				break;
			case 8:
				break;
			case 10: delete[] dates1; delete[] dates2; return 0;//завершение работы
			default:cout<<"Недопустимое действие. Повторите выбор\n"; 
				break;
		}
	}
		return 0;
}	



